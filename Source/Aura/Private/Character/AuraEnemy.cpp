// This is the GAS project that I'm studying.

#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
    // 配置敌人网格体对“可见性”通道的碰撞响应
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    
    // 创建并配置能力系统组件
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    
    // 启用网络复制
    // 确保能力系统状态在服务器和客户端间同步
    AbilitySystemComponent->SetIsReplicated(true);
    
    // 设置最小复制模式
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
    
    // 创建自定义属性集
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
    // 启用敌人自身网格体的自定义深度渲染
    // 这是UE中实现轮廓高亮的标准方法：将网格体渲染到一张特殊缓冲区。
    GetMesh()->SetRenderCustomDepth(true);
    
    // 设置自定义深度渲染的模板值
    // CUSTOM_DEPTH_RED 应是一个在项目头文件（Aura.h）中定义的常量。
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    
    // 同样启用武器网格体的自定义深度渲染
    // 注意：Weapon 指针继承自父类 AAuraCharacterBase。
    // 武器作为独立组件，需要单独设置才能与角色一同被高亮。
    Weapon->SetRenderCustomDepth(true);
    
    // 为武器设置相同的高亮颜色（模板值）
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
    // 关闭敌人自身网格体的自定义深度渲染
    GetMesh()->SetRenderCustomDepth(false);
    
    // 关闭武器网格体的自定义深度渲染
    Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();
    check(AbilitySystemComponent);
    // 初始化能力Actor信息
    // 将敌人自身设置为AbilitySystemComponent的OwnerActor和AvatarActor
    // 这是GAS系统工作的关键步骤，建立Actor与能力系统的关联
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

