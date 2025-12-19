// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

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
    // 构造函数
    UAuraAttributeSet();
    
    // 重写函数：处理属性复制（网络同步）
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
    
    // 重写函数：属性值改变前的预处理（用于限制数值范围等）
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    
    // 重写函数：游戏效果执行后的处理（应用实际效果）
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    
    // --- 属性定义 ---
    
    // 当前生命值属性
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Health, Category="Health")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);  // 为Health生成访问函数
    
    // 最大生命值属性
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, Category="Health")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);  // 为MaxHealth生成访问函数
    
    // 当前法力值属性
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Mana, Category="Mana")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);  // 为Mana生成访问函数
    
    // 最大法力值属性
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxMana, Category="Mana")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);  // 为MaxMana生成访问函数
    
    // --- 属性复制回调函数（在服务器同步属性到客户端时调用） ---
    
    // 生命值复制回调
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
    
    // 最大生命值复制回调
    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
    
    // 法力值复制回调
    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
    
    // 最大法力值复制回调
    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
    
private:
    // 静态辅助函数：从游戏效果回调数据中提取并设置效果属性信息
    // Data: 游戏效果的回调数据
    // Properties: 要填充的效果属性结构体
    static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties);
};