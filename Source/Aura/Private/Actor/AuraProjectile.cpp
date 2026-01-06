// This is the GAS project that I'm studying.


#include "Actor/AuraProjectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AAuraProjectile::AAuraProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    
    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
    SetRootComponent(Sphere);
    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");;
    ProjectileMovement->InitialSpeed = 600.0f;
    ProjectileMovement->MaxSpeed = 600.0f;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
    
    Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
    Arrow->SetupAttachment(Sphere);
    
    LoopingSoundComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
}

void AAuraProjectile::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(LifeSpan);
    LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AAuraProjectile::Destroyed()
{
    if (!bHit && !HasAuthority())
    {
        UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
        LoopingSoundComponent->Stop();
    }
    Super::Destroyed();
}