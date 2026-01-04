// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Interaction/CombatInterface.h"
#include "MouseTargetData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataDelegate, const FGameplayAbilityTargetDataHandle, TargetData);
/**
 * 
 */
UCLASS()
class AURA_API UMouseTargetData : public UAbilityTask, public ICombatInterface
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Ability | Tasks", meta=(DisplayName = "MouseTargetData", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
    static UMouseTargetData* GetTMouseTargetData(UGameplayAbility* OwningAbility);
    
    UPROPERTY(BlueprintAssignable)
    FMouseTargetDataDelegate ValidData;
    
    virtual void Activate() override;
    void SendMouseCursorData() const;
    void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) const;
};
