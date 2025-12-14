// This is the GAS project that I'm studying.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
    
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(StaticMeshComponent);
    
    ShapeComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Shape"));
    ShapeComponent->SetupAttachment(StaticMeshComponent);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (const IAbilitySystemInterface* AscInterface = Cast<IAbilitySystemInterface>(OtherActor))
    {
        const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
        UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
        MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.0f);
        Destroy();
    }
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
    ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
}

