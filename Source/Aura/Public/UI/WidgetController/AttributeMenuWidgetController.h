// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributesChangedDelegate, const FAuraAttributeInfo&, Info);
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
    
    UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
    FOnAttributesChangedDelegate OnAttributeChangedDelegate;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category="AttributeInfo")
    TObjectPtr<UAttributeInfo> AttributeInfo;
    
private:
    UFUNCTION()
    void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute, const UAuraAttributeSet* AS) const;
};
