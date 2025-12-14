// This is the GAS project that I'm studying.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/InterfaceBase.h"

AAuraPlayerController::AAuraPlayerController()
{
    // 启用网络复制（如果项目支持多人游戏）
    // 这允许控制器在网络游戏中被复制到客户端
    bReplicates = true;
}

void AAuraPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
    // 用于存储光线命中结果的结构体
    FHitResult CursorHit;
    // 从当前鼠标光标位置向场景中发射一条不可见的射线（使用可见性通道）
    // 检测鼠标下方是否存在任何物体（命中结果存入CursorHit）
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
    
    // 如果没有命中任何阻挡物体，则直接返回，不执行后续高亮逻辑
    if (!CursorHit.bBlockingHit) return;
    
    // 更新追踪记录：将上一帧的“当前Actor”变为“上一帧的Actor”
    LastActor = ThisActor;
    // 尝试将当前命中的Actor转换为可交互接口（IInterfaceBase）
    ThisActor = Cast<IInterfaceBase>(CursorHit.GetActor());
    
    /**
     * 鼠标射线检测后，处理Actor高亮状态的逻辑分支（共5种情况）:
     * 1. LastActor == null && ThisActor == null
     *    - 鼠标从空地移到空地：什么也不做。
     * 2. LastActor == null && ThisActor有效
     *    - 鼠标从空地移到新Actor上：高亮这个新Actor。
     * 3. LastActor有效 && ThisActor == null
     *    - 鼠标从Actor上移开，移到空地：取消上一个Actor的高亮。
     * 4. LastActor和ThisActor有效 && LastActor != ThisActor
     *    - 鼠标从一个Actor移到另一个Actor：取消旧的高亮，应用新的高亮。
     * 5. LastActor和ThisActor有效 && LastActor == ThisActor
     *    - 鼠标持续停留在同一个Actor上：什么也不做（避免每帧重复操作）。
     ***/
    
    if (LastActor == nullptr)
    {
        if (ThisActor == nullptr)
        {
            // 情况1：什么也不做
        }
        else
        {
            // 情况2：高亮新Actor（例如，敌人变红，友军变蓝）
            ThisActor->HighlightActor();
        }
    }
    else
    {
        if (ThisActor == nullptr)
        {
            // 情况3：取消上一帧Actor的高亮
            LastActor->UnHighlightActor();
        }
        else
        {
            if (LastActor != ThisActor)
            {
                // 情况4：切换高亮对象
                LastActor->UnHighlightActor();
                ThisActor->HighlightActor();
            }
            else
            {
                // 情况5：停留在同一对象上，什么也不做
            }
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
    check(SubSystem);
    
    // 将Aura输入映射上下文添加到子系统
    // 参数0表示映射优先级（数字越小优先级越高）
    SubSystem->AddMappingContext(AuraContext, 0);

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
    
    // 将输入组件转换为增强输入组件
    // CastChecked是安全的类型转换，失败时会断言
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    
    // 绑定移动输入动作MoveAction到Move函数
    // ETriggerEvent::Triggered 表示当输入动作持续触发时调用
    // 这通常用于移动这种需要持续响应的输入
    EnhancedInputComponent->BindAction(
        MoveAction,                    // 要绑定的输入动作
        ETriggerEvent::Triggered,      // 触发事件类型
        this,                          // 处理对象（当前控制器）
        &AAuraPlayerController::Move   // 处理函数
    );
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
    // 注意：如果当前没有控制pawn，移动输入会被忽略
}
