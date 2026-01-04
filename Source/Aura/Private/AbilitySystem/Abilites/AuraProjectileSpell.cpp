// This is the GAS project that I'm studying.


#include "AbilitySystem/Abilites/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Player/AuraPlayerController.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    
   
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileLocation)
{
    const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
    if (!bIsServer) return;
    ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
    if (!CombatInterface) return;
    const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
    FRotator Rotation = (ProjectileLocation - SocketLocation).Rotation();
    
    const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
    if (!ActorInfo) return;
    AAuraPlayerController* PC = Cast<AAuraPlayerController>(ActorInfo->PlayerController.Get());
    if (!PC->GetTargeting())
    {
        Rotation.Pitch = 0.0f;
    }
    
    FTransform SpawnTransform;
    SpawnTransform.SetLocation(SocketLocation);
    SpawnTransform.SetRotation(Rotation.Quaternion());  //创建了1个四元数
    
    AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
        ProjectileClass, 
        SpawnTransform, 
        GetOwningActorFromActorInfo(), 
        Cast<APawn>(GetOwningActorFromActorInfo()), 
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    
    Projectile->FinishSpawning(SpawnTransform);
}
