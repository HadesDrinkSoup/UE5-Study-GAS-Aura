// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilites/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility, public ICombatInterface
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    
    UFUNCTION(BlueprintCallable, Category="Combat")
    void SpawnProjectile(const FVector& ProjectileLocation);
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<AAuraProjectile> ProjectileClass;
};
