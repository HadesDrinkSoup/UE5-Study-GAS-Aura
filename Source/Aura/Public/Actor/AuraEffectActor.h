// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
    
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent> SceneComponent;
protected:
	virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintCallable)
    void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffect) const;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffects")
    TSubclassOf<UGameplayEffect> GameplayEffectClass;
};
