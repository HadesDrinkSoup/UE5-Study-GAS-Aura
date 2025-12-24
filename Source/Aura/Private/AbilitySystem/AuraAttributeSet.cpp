// This is the GAS project that I'm studying.


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Character/AuraCharacter.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

// 重写函数：定义需要网络复制的属性
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    // 调用父类实现，确保基础功能正常
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    /** 重要属性 **/
    // 注册生命值属性进行网络复制
    // COND_None: 无条件复制（总是复制）
    // REPNOTIFY_Always: 总是发送通知，即使值没有改变
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
    
    /** 主要属性 **/
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
    
    /** 次要属性 **/
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

// 重写函数：属性值改变前的预处理
// 用于限制属性值的有效范围
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    // 调用父类实现，确保基础功能正常
    Super::PreAttributeChange(Attribute, NewValue);
    
    // 如果是生命值属性，将其限制在0到最大生命值之间
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
    
    // 如果是法力值属性，将其限制在0到最大法力值之间
    if (Attribute == GetManaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
    }
}

// 重写函数：游戏效果执行后的处理
// 在游戏效果（如伤害、治疗、法力消耗等）应用后调用
void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    // 调用父类实现，确保基础功能正常
    Super::PostGameplayEffectExecute(Data);
    
    // 创建效果属性结构体实例
    FEffectProperties Properties;
    
    // 从游戏效果回调数据中提取相关信息并填充到Properties结构体
    SetEffectProperties(Data, Properties);
    
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
    }
    
    if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
        SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
    }
    // 注意：这里可以添加额外的效果处理逻辑，如：
    // 1. 处理伤害效果并触发死亡逻辑
    // 2. 处理治疗效果并显示UI反馈
    // 3. 触发属性变化相关的事件等
}

// 属性复制回调函数：当生命值在客户端从服务器复制时调用
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    // 使用GAS宏处理属性复制通知，确保属性系统正确更新
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

// 属性复制回调函数：当法力值在客户端从服务器复制时调用
void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
    // 使用GAS宏处理属性复制通知
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

// 静态辅助函数：从游戏效果回调数据中提取并设置效果属性信息
void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties)
{
    // 1. 获取效果上下文句柄
    Properties.EffectContextHandle = Data.EffectSpec.GetContext();
    
    // 2. 设置来源方（Source）信息
    // 获取来源方的能力系统组件
    Properties.SourceASC = Properties.EffectContextHandle.GetInstigatorAbilitySystemComponent();
    
    // 检查来源ASC是否有效且包含有效的Actor信息
    if (IsValid(Properties.SourceASC) && 
        Properties.SourceASC->AbilityActorInfo.IsValid() && 
        Properties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
    {
        // 获取来源方的Avatar Actor（通常是角色本身）
        Properties.SourceAvatarActor = Properties.SourceASC->AbilityActorInfo->AvatarActor.Get();
        // 获取来源方的控制器
        Properties.SourceController = Properties.SourceASC->AbilityActorInfo->PlayerController.Get();
        
        // 如果已有Avatar Actor但没有控制器，尝试从Avatar Actor获取控制器
        if (Properties.SourceAvatarActor != nullptr && Properties.SourceController == nullptr)
        {
            // 如果Avatar Actor是Pawn，尝试获取其控制器
            if (const APawn* Pawn = Cast<APawn>(Properties.SourceAvatarActor))
            {
                Properties.SourceController = Pawn->GetController();
            }
        }
        
        // 如果已获取到控制器，获取其控制的角色
        if (Properties.SourceController)
        {
            Properties.SourceCharacter = Cast<ACharacter>(Properties.SourceController->GetPawn());
        }
    }
    
    // 3. 设置目标方（Target）信息
    // 检查目标方的AbilityActorInfo是否有效
    if (Data.Target.AbilityActorInfo.IsValid() && 
        Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        // 获取目标方的Avatar Actor
        Properties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        // 获取目标方的控制器
        Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
        // 获取目标方的角色（将Avatar Actor转换为Character）
        Properties.TargetCharacter = Cast<ACharacter>(Properties.TargetAvatarActor);
        // 使用辅助函数获取目标方的能力系统组件
        Properties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetCharacter);
    }
    
    // 注意：这个函数现在只是提取和设置属性信息，为后续的效果处理做准备
    // 在实际项目中，这里提取的信息可以用于：
    // 1. 计算基于属性的伤害（如攻击力、防御力）
    // 2. 触发视觉效果（如命中特效）
    // 3. 播放音效
    // 4. 更新UI显示
    // 5. 发送游戏事件等
}