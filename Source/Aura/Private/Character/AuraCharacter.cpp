// This is the GAS project that I'm studying.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
    // 创建弹簧臂组件
    // CreateDefaultSubobject: 标准方法，在构造函数中创建组件
    // "SpringArm": 组件实例名称
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    
    // 将弹簧臂附加到根组件（角色的根组件通常是胶囊体）
    SpringArm->SetupAttachment(RootComponent);
    
    // 创建相机组件
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    
    // 将相机附加到弹簧臂，形成层次结构：角色->弹簧臂->相机
    Camera->SetupAttachment(SpringArm);
    
    // 设置弹簧臂长度：相机与角色的距离
    // 750单位距离提供适当的第三人称视角
    SpringArm->TargetArmLength = 750.0f;
    
    // 设置弹簧臂相对于角色的旋转
    // FRotator(Pitch, Yaw, Roll): (-45°, 0°, 0°)让相机从角色上方俯视
    // SetRelativeRotationExact: 设置精确旋转，不使用插值
    SpringArm->SetRelativeRotationExact(FRotator(-45.0f, 0.0f, 0.0f));
    
    // 禁用弹簧臂碰撞检测：防止物体阻挡
    SpringArm->bDoCollisionTest = false;
    // 启用相机延迟效果：相机移动会有轻微的延迟，提供更自然的跟随感
    SpringArm->bEnableCameraLag = true;
    
    // 设置相机延迟速度：值越小延迟越明显，值越大跟随越紧密
    SpringArm->CameraLagSpeed = 10.0f;
    
    // 禁用弹簧臂使用pawn控制器的旋转
    // 这意味着弹簧臂不会跟随鼠标或手柄的输入旋转
    SpringArm->bUsePawnControlRotation = false;
    
    // 禁用弹簧臂继承控制器的偏航旋转
    SpringArm->bInheritYaw = false;
    
    // 禁用弹簧臂继承控制器的俯仰旋转
    SpringArm->bInheritPitch = false;
    
    // 禁用弹簧臂继承控制器的翻滚旋转
    SpringArm->bInheritRoll = false;
    
    // 获取角色的移动组件
    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    
    // 启用角色朝向移动方向旋转
    MoveComp->bOrientRotationToMovement = true;
    
    // 设置旋转速率：角色转向的速度
    // FRotator(Pitch, Yaw, Roll): 只设置偏航(Yaw)旋转速率为400度/秒
    MoveComp->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
    
    // 将角色运动约束到平面：限制角色在水平面上移动
    // 这对于固定视角的游戏很有用，防止角色在斜坡上倾斜
    MoveComp->bConstrainToPlane = true;
    
    // 在游戏开始时将角色吸附到平面
    // 确保角色正确放置在游戏平面上
    MoveComp->bSnapToPlaneAtStart = true;
    
    // 禁用角色使用控制器的偏航旋转
    // 角色不会直接跟随控制器的左右输入旋转
    bUseControllerRotationYaw = false;
    
    // 禁用角色使用控制器的俯仰旋转
    // 角色不会直接跟随控制器的上下输入旋转
    bUseControllerRotationPitch = false;
    
    // 禁用角色使用控制器的翻滚旋转
    // 角色不会直接跟随控制器的倾斜输入旋转
    bUseControllerRotationRoll = false;
}

/**
 * 当角色被控制器占用时调用（服务器端）
 */
void AAuraCharacter::PossessedBy(AController* NewController)
{
    // 调用父类实现，处理基础占用逻辑
    Super::PossessedBy(NewController);
    
    // 初始化GAS系统：建立AbilitySystemComponent与角色的关联
    InitAbilityActorInfo();
    AddCharacterAbilities();
}

/**
 * 当PlayerState被复制到客户端时调用（客户端）
 */
void AAuraCharacter::OnRep_PlayerState()
{
    // 调用父类实现，处理基础PlayerState复制逻辑
    Super::OnRep_PlayerState();
    
    // 初始化GAS系统：建立AbilitySystemComponent与角色的关联
    InitAbilityActorInfo();
}

int32 AAuraCharacter::GetLevel()
{
    const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetPlayerLevel();
}

/**
 * 初始化能力Actor信息
 * 关键步骤：将PlayerState中的AbilitySystemComponent与角色关联
 * 这是GAS系统工作的核心，确保能力系统知道哪个Actor拥有并使用能力
 */
void AAuraCharacter::InitAbilityActorInfo()
{
    // 获取玩家状态
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    
    // 初始化能力Actor信息
    // InitAbilityActorInfo建立两个关键引用：
    // 1. OwnerActor: PlayerState（能力的拥有者）
    // 2. AvatarActor: 角色自身（能力的执行者）
    // 这是GAS的标准模式：分离拥有者和执行者
    AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
    // 调用自定义AbilitySystemComponent的额外初始化
    Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
    // 将本地的AbilitySystemComponent引用指向PlayerState中的组件
    // 这样角色就可以直接访问能力系统，而无需每次都通过PlayerState
    AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
    
    // 将本地的AttributeSet引用指向PlayerState中的属性集
    AttributeSet = AuraPlayerState->GetAttributeSet();
    
    InitializeDefaultAttributes();
    if(AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
    {
        if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
        {
            AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
        }
    }
}
