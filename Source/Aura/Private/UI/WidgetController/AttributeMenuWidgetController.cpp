// This is the GAS project that I'm studying.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    /*
    const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
    OnStrengthChanged.Broadcast(AuraAttributeSet->GetStrength());
    OnResilienceChanged.Broadcast(AuraAttributeSet->GetResilience());
    OnIntelligenceChanged.Broadcast(AuraAttributeSet->GetIntelligence());
    OnVigorChanged.Broadcast(AuraAttributeSet->GetVigor());
    
    OnArmorChanged.Broadcast(AuraAttributeSet->GetArmor());
    OnArmorPenetrationChanged.Broadcast(AuraAttributeSet->GetArmorPenetration());
    OnBlockChanceChanged.Broadcast(AuraAttributeSet->GetBlockChance());
    OnCriticalHitChanceChanged.Broadcast(AuraAttributeSet->GetCriticalHitChance());
    OnCriticalHitDamageChanged.Broadcast(AuraAttributeSet->GetCriticalHitDamage());
    OnCriticalHitResistanceChanged.Broadcast(AuraAttributeSet->GetCriticalHitResistance());
    OnHealthRegenerationChanged.Broadcast(AuraAttributeSet->GetHealthRegeneration());
    OnManaRegenerationChanged.Broadcast(AuraAttributeSet->GetManaRegeneration());
    OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
    OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
    */
}

void UAttributeMenuWidgetController::BindCallBacksToDependencies()
{
    /*
    const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetStrengthAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnStrengthChanged.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetResilienceAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnResilienceChanged.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetIntelligenceAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnIntelligenceChanged.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetVigorAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnVigorChanged.Broadcast(Data.NewValue);
        });
    
    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetArmorAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnArmorChanged.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetArmorPenetrationAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnArmorPenetrationChanged.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetBlockChanceAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnBlockChanceChanged.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetCriticalHitChanceAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnCriticalHitChanceChanged.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetCriticalHitDamageAttribute()).AddLambda(
       [this](const FOnAttributeChangeData& Data)
       {
           OnCriticalHitDamageChanged.Broadcast(Data.NewValue);
       });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetCriticalHitResistanceAttribute()).AddLambda(
       [this](const FOnAttributeChangeData& Data)
       {
           OnCriticalHitResistanceChanged.Broadcast(Data.NewValue);
       });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthRegenerationAttribute()).AddLambda(
       [this](const FOnAttributeChangeData& Data)
       {
           OnHealthRegenerationChanged.Broadcast(Data.NewValue);
       });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaRegenerationAttribute()).AddLambda(
       [this](const FOnAttributeChangeData& Data)
       {
           OnManaRegenerationChanged.Broadcast(Data.NewValue);
       });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
       [this](const FOnAttributeChangeData& Data)
       {
           OnMaxHealthChanged.Broadcast(Data.NewValue);
       });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
       [this](const FOnAttributeChangeData& Data)
       {
           OnMaxManaChanged.Broadcast(Data.NewValue);
       });
       */
}
