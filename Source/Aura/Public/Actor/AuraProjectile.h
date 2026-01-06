// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UNiagaraSystem;
class UArrowComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
    GENERATED_BODY()
	
public:	
    AAuraProjectile();

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
    
    
protected:
    virtual void BeginPlay() override;
    
    virtual void Destroyed() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool bHit = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UAudioComponent> LoopingSoundComponent;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<USoundBase> LoopingSound;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<USoundBase> ImpactSound;
    
    UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
    TObjectPtr<UNiagaraSystem> ImpactEffect;
private:
    UPROPERTY(EditDefaultsOnly)
    float LifeSpan = 10.f;
    
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USphereComponent> Sphere;
    
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UArrowComponent> Arrow;
};