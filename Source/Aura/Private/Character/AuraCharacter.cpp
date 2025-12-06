// This is the GAS project that I'm studying.


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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