// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"
DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeDelegate);

// 宏定义：为属性生成便捷的Getter/Setter/Initter函数
// ClassName: 类名，PropertyName: 属性名
// 这个宏会为属性生成标准的GAS访问函数
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// 结构体：用于存储游戏效果执行时的上下文信息
// 包含了来源（Source）和目标（Target）的各种相关信息
USTRUCT(BlueprintType)
struct FEffectProperties
{
    GENERATED_BODY()
    
    // 游戏效果上下文句柄，包含效果的详细执行信息
    FGameplayEffectContextHandle EffectContextHandle;
    
    // 来源方的相关信息
    UPROPERTY()
    UAbilitySystemComponent* SourceASC = nullptr;  // 来源能力系统组件
    UPROPERTY()
    AActor* SourceAvatarActor = nullptr;           // 来源角色Actor
    UPROPERTY()
    AController* SourceController = nullptr;       // 来源控制器
    UPROPERTY()
    ACharacter* SourceCharacter = nullptr;         // 来源角色
    
    // 目标方的相关信息
    UPROPERTY()
    UAbilitySystemComponent* TargetASC = nullptr;  // 目标能力系统组件
    UPROPERTY()
    AActor* TargetAvatarActor = nullptr;           // 目标角色Actor
    UPROPERTY()
    AController* TargetController = nullptr;       // 目标控制器
    UPROPERTY()
    ACharacter* TargetCharacter = nullptr;         // 目标角色
};


template<class T>
using TStaticFuncPtr = TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * AuraAttributeSet类
 * 继承自UAttributeSet，负责管理角色的属性（生命值、法力值等）
 * 这是GAS中的核心类之一，用于定义和操作游戏属性
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    UAuraAttributeSet();
    
    // 重写函数：处理属性复制（网络同步）
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
    
    // 重写函数：属性值改变前的预处理（用于限制数值范围等）
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    
    // 重写函数：游戏效果执行后的处理（应用实际效果）
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    /**
     *  使用Map数组创建映射，在蓝图中实现能力属性在属性控件蓝图中显示
     *  方案一 创建标签和委托的映射
     *      1. 创建委托DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeInitializeDelegate)
     *      2. 创建映射TMap<FGameplay, FAttributeInitializeDelegate> TagsToAttributes
     *      3. 添加到Map映射中
     *          const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();  // 获取的是游戏中自定义的整个Tag，包含所有属性
     *          FAttributeInitializeDelegate StrengthDelegate;	// 临时声明1个对应力量属性的专用委托
     *          StrengthDelegate.BindStatic(GetStrengthAttribute);	// 绑定静态函数
     *          TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength,StrengthDelegate);
     *  方案二 利用创建委托绑定静态函数本质创建映射
     *      1. 委托绑定函数的本质是静态委托实例的函数指针类型TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FunctionPointer;
     *          //函数指针语法
     *          //FunctionPointer = GetStrengthAttribute; //函数指针指向GetStrengthAttribute函数
     *          //FGameplayAttribute Attribute = FunctionPointer(); //接收函数返回的参数
     *
     *      2. 利用上述特性创建映射TMap<FGameplayTag, TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr> TagsToAttributes;
     *          BaseStaticDelegateInstance - 委托系统的基类模板 
     *          FGameplayAttribute() - 委托的函数签名
     *          FDefaultDelegateUserPolicy - 委托的策略类
     *          ::FFuncPtr指向匹配委托签名的函数指针
     *      3. 可使用函数指针进一步简化TMap<FGameplayTag, FGameplayAttribute(*)()> TagsToAttributes;
     *      3. 映添加到Map映射中
     *          const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
     *          TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
     *  方案三 利用委托绑定是函数指针类型， 使用模板简化函数指针进一步改进创建映射
     *      1. 创建模板
     *          template<class T>
     *          using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;
     *      2. 创建映射
     *          TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
     */
    
    TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;  
    
    /** 重要属性 **/
    
    // 当前生命值属性
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Health, Category="Health")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);  // 为Health生成访问函数
    
    // 当前法力值属性
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Mana, Category="Mana")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);  // 为Mana生成访问函数
    
    /** 主要属性 **/
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Strength, Category="Strength")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);  // 为Strength生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Intelligence, Category="Intelligence")
    FGameplayAttributeData Intelligence;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);  // 为Intelligence生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Resilience, Category="Resilience")
    FGameplayAttributeData Resilience;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);  // 为Resilience生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Vigor, Category="Vigor")
    FGameplayAttributeData Vigor;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);  // 为Vigor生成访问函数
    
    /** 次要属性 **/
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Armor, Category="Armor")
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);  // 为Armor生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_ArmorPenetration, Category="ArmorPenetration")
    FGameplayAttributeData ArmorPenetration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);  // 为ArmorPenetration生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_BlockChance, Category="BlockChance")
    FGameplayAttributeData BlockChance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);  // 为BlockChance生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_CriticalHitChance, Category="CriticalHitChance")
    FGameplayAttributeData CriticalHitChance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);  // 为CriticalHitChance生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_CriticalHitDamage, Category="CriticalHitDamage")
    FGameplayAttributeData CriticalHitDamage;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);  // 为CriticalHitDamage生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_CriticalHitResistance, Category="CriticalHitResistance")
    FGameplayAttributeData CriticalHitResistance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);  // 为CriticalHitResistance生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_HealthRegeneration, Category="HealthRegeneration")
    FGameplayAttributeData HealthRegeneration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);  // 为HealthRegeneration生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_ManaRegeneration, Category="ManaRegeneration")
    FGameplayAttributeData ManaRegeneration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);  // 为ManaRegeneration生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, Category="Health")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);  // 为MaxHealth生成访问函数
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxMana, Category="Mana")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);  // 为MaxMana生成访问函数
    
    // --- 属性复制回调函数（在服务器同步属性到客户端时调用） ---
    
    // 生命值复制回调
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
    // 法力值复制回调
    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
    
    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
    UFUNCTION()
    void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
    UFUNCTION()
    void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
    UFUNCTION()
    void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
    
    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
    UFUNCTION()
    void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
    UFUNCTION()
    void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
    UFUNCTION()
    void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
    UFUNCTION()
    void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
    UFUNCTION()
    void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
    UFUNCTION()
    void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
    UFUNCTION()
    void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
    
private:
    // 静态辅助函数：从游戏效果回调数据中提取并设置效果属性信息
    // Data: 游戏效果的回调数据
    // Properties: 要填充的效果属性结构体
    static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties);
};