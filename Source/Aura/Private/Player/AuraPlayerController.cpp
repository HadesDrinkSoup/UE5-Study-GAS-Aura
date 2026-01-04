// This is the GAS project that I'm studying.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/InterfaceBase.h"

AAuraPlayerController::AAuraPlayerController()
{
    // 启用网络复制（如果项目支持多人游戏）
    // 这允许控制器在网络游戏中被复制到客户端
    bReplicates = true;
    
    Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    CursorTrace();
    
    //AutoRun();
}

/*
void AAuraPlayerController::AutoRun()
{
    if(!bAutoRunning) return;
    if(APawn* ControlledPawn = GetPawn())
    {
        //找到距离样条最近的位置
        const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
        //获取这个位置在样条上的方向
        const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
        ControlledPawn->AddMovementInput(Direction);

        const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
        if(DistanceToDestination <= AutoRunAcceptanceRadius)
        {
            bAutoRunning = false;
        }
    }
}
*/

void AAuraPlayerController::CursorTrace()
{
    // 用于存储光线命中结果的结构体
    
    // 从当前鼠标光标位置向场景中发射一条不可见的射线（使用可见性通道）
    // 检测鼠标下方是否存在任何物体（命中结果存入CursorHit）
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
    
    // 如果没有命中任何阻挡物体，则直接返回，不执行后续高亮逻辑
    if (!CursorHit.bBlockingHit) return;
    
    // 更新追踪记录：将上一帧的“当前Actor”变为“上一帧的Actor”
    LastActor = ThisActor;
    // 尝试将当前命中的Actor转换为可交互接口（IInterfaceBase）
    ThisActor = Cast<IInterfaceBase>(CursorHit.GetActor());
    
    if (LastActor != ThisActor)
    {
        if (LastActor)
        {
            LastActor->UnHighlightActor();
        }
        if (ThisActor)
        {
            ThisActor->HighlightActor();
        }
    }
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    // 安全检查：确保AuraContext已正确设置
    check(AuraContext);

    // 获取增强输入本地玩家子系统
    UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    
    // 安全检查：确保子系统有效
    if (SubSystem)
    {
        // 将Aura输入映射上下文添加到子系统
        // 参数0表示映射优先级（数字越小优先级越高）
        SubSystem->AddMappingContext(AuraContext, 0);
    }
    
    // 显示鼠标光标
    bShowMouseCursor = true;
    
    // 设置默认鼠标光标样式
    DefaultMouseCursor = EMouseCursor::Default;

    // 创建"游戏+UI"输入模式数据
    // 这种模式允许同时处理游戏输入和UI输入
    FInputModeGameAndUI InputModeData;
    
    // 设置鼠标锁定行为：不将鼠标锁定到视口
    // 玩家可以自由移动鼠标到其他窗口
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    
    // 设置在捕获输入时不隐藏光标
    // 这可以确保光标在游戏中始终可见
    InputModeData.SetHideCursorDuringCapture(false);
    
    // 应用输入模式设置
    SetInputMode(InputModeData);
}


void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(EnhancedInputComponent);
    AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
    AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
    AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
    
    AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    // 从输入动作值中获取二维向量
    // 通常X轴对应水平输入（A/D），Y轴对应垂直输入（W/S）
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    
    // 获取控制器的当前旋转
    const FRotator Rotation = GetControlRotation();
    
    // 创建一个只包含偏航角（Yaw，水平旋转）的旋转量
    // Pitch（俯仰）和Roll（翻滚）被置零，确保移动只在水平面上进行
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    
    // 使用旋转矩阵计算前进方向（X轴）
    // 这是控制器正对的方向
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    
    // 使用旋转矩阵计算右方向（Y轴）
    // 这是控制器右侧的方向
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    
    // 获取当前控制的pawn（玩家控制的角色）
    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        // 应用前进/后退移动
        // InputAxisVector.Y: 正值向前，负值向后
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        
        // 应用左右移动
        // InputAxisVector.X: 正值向右，负值向左
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
    }
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
    if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
    {
        bTargeting = ThisActor ? true : false;
    }
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
    
    /*
    if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) // 不是鼠标左键，尝试激活能力
    {
        if (GetASC())
        {
            GetASC()->AbilityInputTagReleased(InputTag);
        }
        return;
    }*/
    if (GetASC())
    {
        GetASC()->AbilityInputTagReleased(InputTag);
    }
    /** 鼠标左键点击移动**/
    /*
    if (!bTargeting && !bShiftKeyDown)	//非施放技能的逻辑变为“不是敌人 && 没有点Shift”
    {
        APawn* ControlledPawn = GetPawn();
        if (FollowTime <= ShortPressThreshold && ControlledPawn) // 跟随时间小于短按阈值则点击移动
        {
            if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
            {
                FVector PreviousPoint = ControlledPawn->GetActorLocation() - FVector(0, 0,  Cast<ACharacter>(ControlledPawn)->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
                Spline->ClearSplinePoints();
                for (const FVector& PointLocation : NavPath->PathPoints)
                {
                    Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
                    DrawDebugLine(GetWorld(), PreviousPoint, PointLocation, FColor::Red, false, 5.0f, 0, 1.0f);
                    PreviousPoint = PointLocation;
                }
                if (!NavPath->PathPoints.IsEmpty())
                {
                    CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
                }
                bAutoRunning = true;
            }
        }
        FollowTime = 0.0f;
    }
    */
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
    if (GetASC())
    {
        GetASC()->AbilityInputTagHeld(InputTag);
    }
    /*
    if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) // 不是鼠标左键，尝试激活能力
    {
        if (GetASC())
        {
            GetASC()->AbilityInputTagHeld(InputTag);
        }
        return;
    }*/
    /*
    if (bTargeting || bShiftKeyDown) // 是敌人，施放技能
    {
        if (GetASC())
        {
            GetASC()->AbilityInputTagHeld(InputTag);
        }
    }*/
    /** 鼠标左键长按移动 **/
    /*
    else // 不是敌人，添加移动
    {
        FollowTime += GetWorld()->GetDeltaSeconds();
        if (CursorHit.bBlockingHit)
        {
            CachedDestination = CursorHit.ImpactPoint;
        }
        if (APawn* ControlledPawn = GetPawn<APawn>())
        {
            const FVector WordDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
            ControlledPawn->AddMovementInput(WordDirection);
        }
    }
    */
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
    if (AuraAbilitySystemComponent == nullptr)
    {
        AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
    }
    return AuraAbilitySystemComponent;
}