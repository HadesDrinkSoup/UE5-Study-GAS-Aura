// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDelegate, float, NewValue);
/**
 * 
 */
UCLASS()
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
    virtual void BroadcastInitialValues() override;
    virtual void BindCallBacksToDependencies() override;
    /*
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnStrengthChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnResilienceChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnIntelligenceChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnVigorChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnArmorChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnArmorPenetrationChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnBlockChanceChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnCriticalHitChanceChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnCriticalHitDamageChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnCriticalHitResistanceChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnHealthRegenerationChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnManaRegenerationChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnMaxHealthChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnMaxManaChanged;
    */
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category="AttributeInfo")
    TObjectPtr<UDataAsset> AttributeInfoAsset;
};
