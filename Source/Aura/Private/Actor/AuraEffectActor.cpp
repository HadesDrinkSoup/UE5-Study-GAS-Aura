// This is the GAS project that I'm studying.

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
    PrimaryActorTick.bCanEverTick = false;
    
    // 创建并设置场景根组件
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneComponent);
}

void AAuraEffectActor::BeginPlay()
{
    Super::BeginPlay();
}

/**
 * 应用游戏效果到目标Actor
 * @param TargetActor 目标Actor，效果将应用到此Actor上
 * @param GameplayEffect 要应用的GameplayEffect类
 */
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffect)
{
    // 获取目标Actor的AbilitySystemComponent
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
    if (TargetASC == nullptr) return;
    
    // 检查GameplayEffect类是否有效
    checkf(GameplayEffect, TEXT("ApplyEffectToTarget函数中的GameplayEffect蓝图类未设置"))
    
    // 创建效果上下文并设置源对象
    FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
    EffectContextHandle.AddSourceObject(this);
    
    // 创建效果规格并应用到目标自身
    const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffect, ActorLevel, EffectContextHandle);
    const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
    
    // 检查是否为无限持续时间的效果
    const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
    
    // 如果是无限效果且移除策略为"离开时移除"，则保存效果句柄
    if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
    {
        ActiveGameplayEffectHandles.Add(ActiveEffectHandle, TargetASC);
    }
}

/**
 * 当有Actor进入重叠区域时调用
 * @param TargetActor 进入重叠区域的目标Actor
 */
void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
    // 根据策略应用瞬时效果
    if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
    {
        ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
    }
    
    // 根据策略应用持续效果
    if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
    {
        ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
    }
    
    // 根据策略应用无限效果
    if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
    {
        ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
    }
}

/**
 * 当有Actor离开重叠区域时调用
 * @param TargetActor 离开重叠区域的目标Actor
 */
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
    // 根据策略应用瞬时效果
    if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
    }
    
    // 根据策略应用持续效果
    if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
    }
    
    // 根据策略应用无限效果
    if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
    }
    
    // 根据策略移除无限效果
    if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
    {
        // 获取目标Actor的AbilitySystemComponent
        UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
        if (!IsValid(TargetASC)) return;
        
        // 收集需要移除的效果句柄
        TArray<FActiveGameplayEffectHandle> HandlesToRemove;
        
        // 遍历所有保存的无限效果句柄
        for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandPair : ActiveGameplayEffectHandles)
        {
            // 如果此效果属于当前目标Actor
            if (HandPair.Value == TargetASC)
            {
                // 从目标ASC中移除效果
                TargetASC->RemoveActiveGameplayEffect(HandPair.Key, 1);
                // 记录需要从映射中移除的句柄
                HandlesToRemove.Add(HandPair.Key);
            }
        }
        
        // 从映射中移除已处理的效果句柄
        for (FActiveGameplayEffectHandle Handle : HandlesToRemove)
        {
            ActiveGameplayEffectHandles.Remove(Handle);
        }
    }
}