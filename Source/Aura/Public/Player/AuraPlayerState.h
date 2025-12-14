// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
    AAuraPlayerState();
    /**
    * 实现IAbilitySystemInterface接口
    * 获取角色的能力系统组件
    */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //获取属性集
    UAttributeSet* GetAttributeSet() const {return AttributeSet;}
    
protected:
    //能力系统组件
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
    //属性集
    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;
};
