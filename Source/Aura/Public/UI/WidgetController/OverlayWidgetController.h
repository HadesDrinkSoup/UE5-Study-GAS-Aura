// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedDelegate, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedDelegate, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedDelegate, float, NewMaxMana);
/**
 * 
 */
UCLASS()
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
    virtual void BroadcastInitialValues() override;
    virtual void BindCallBacksToDependencies() override;
    
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnHealthChangedDelegate OnHealthChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnMaxHealthChangedDelegate OnMaxHealthChanged;
    
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnManaChangedDelegate OnManaChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnMaxManaChangedDelegate OnMaxManaChanged;
    
protected:
    void HealthChanged(const FOnAttributeChangeData& Data) const;
    void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
    void ManaChanged(const FOnAttributeChangeData& Data) const;
    void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
