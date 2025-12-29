// This is the GAS project that I'm studying.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
    const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
    OnHealthChangedDelegate.Broadcast(AuraAttributeSet->GetHealth());
    OnMaxHealthChangedDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
    
    OnManaChangedDelegate.Broadcast(AuraAttributeSet->GetMana());
    OnMaxManaChangedDelegate.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
    const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnHealthChangedDelegate.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnManaChangedDelegate.Broadcast(Data.NewValue);
        });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnMaxManaChangedDelegate.Broadcast(Data.NewValue);
        });
    
    Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagsDelegate.AddLambda(
        [this](const FGameplayTagContainer& AssetTags)
        {
            for (const FGameplayTag& Tag : AssetTags)
            {
                if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
                {
                    const FUIWidgetRow* RowData = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
                    MessageWidgetRowDataDelegate.Broadcast(*RowData);   
                }
            }
        }
    );
}