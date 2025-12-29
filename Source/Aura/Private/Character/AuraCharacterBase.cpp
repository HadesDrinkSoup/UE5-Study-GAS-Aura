// This is the GAS project that I'm studying.


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

    // 创建武器骨架网格体组件实例
    // CreateDefaultSubobject: 在构造函数中创建组件实例的UE标准方法
    // "Weapon": 组件实例的名称，在蓝图中可识别
    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
    
    // 将武器组件附加到角色的网格体上
    // GetMesh(): 获取角色自带的骨架网格体组件（来自ACharacter父类）
    // "WeaponHandSocket": 骨骼插槽名称，表示武器附着点（需要在骨骼中定义）
    Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
    
    // 配置武器的碰撞设置
    // NoCollision: 禁用所有碰撞，避免武器与其他物体发生不必要的交互
    Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}


void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float& Level) const
{
    check(IsValid(GetAbilitySystemComponent()));
    check(GameplayEffectClass);
    FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
    ContextHandle.AddSourceObject(this);
    const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
    GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
    ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
    ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
    ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);
}

void AAuraCharacterBase::AddCharacterAbilities() const
{
    if (!HasAuthority()) return;
    UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
    if (!AuraASC) return;
    AuraASC->AddCharacterAbilities(StartupAbilities);
}

