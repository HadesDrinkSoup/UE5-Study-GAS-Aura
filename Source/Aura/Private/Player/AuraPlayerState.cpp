// This is the GAS project that I'm studying.


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
    // 创建能力系统组件
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    // 启用网络复制
    AbilitySystemComponent->SetIsReplicated(true);
    // 设置GAS网络复制模式为Mixed（混合模式）
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
    
    // 创建属性集
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
    
    // 设置网络更新频率为100Hz
    SetNetUpdateFrequency(100.0f);
    // 对比不同更新频率的影响：
    // - 10Hz (默认): 延迟高，适合变化缓慢的状态
    // - 30Hz (推荐): 平衡延迟和带宽，适合大多数游戏
    // - 60Hz (动作游戏): 响应性好，但带宽消耗大
    // - 100Hz (此处设置): 极高频率，适合：
    //   a) 竞技游戏
    //   b) 需要实时同步的GAS状态
    //   c) 对延迟敏感的游戏机制
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
    //return AbilitySystemComponent;
    return AbilitySystemComponent.Get();
}


