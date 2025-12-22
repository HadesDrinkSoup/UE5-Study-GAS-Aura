// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAttributeSet;
class UGameplayEffect;

// Abstract标记：表示这是一个抽象类，不能被直接实例化
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
    
    /**
     * 实现IAbilitySystemInterface接口
     * 获取角色的能力系统组件
     */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    
    // 获取属性集 
    UAttributeSet* GetAttributeSet() const { return AttributeSet; }
    
protected:
	virtual void BeginPlay() override;
    
    virtual void InitAbilityActorInfo();
    
    //武器骨架网格体组件 
    UPROPERTY(EditAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon;
    
    //能力系统组件
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
    //属性集
    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;
    
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="AttributeSet")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="AttributeSet")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
    
    void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float& Level) const;
    void InitializeDefaultAttributes() const;
};
