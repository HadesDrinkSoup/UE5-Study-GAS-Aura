// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag MessageTag = FGameplayTag();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Message = FText();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<class UAuraUserWidget> MessageWidget;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDelegate, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowDataDelegate, FUIWidgetRow, Row);
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
    FOnAttributeChangedDelegate OnHealthChangedDelegate;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnMaxHealthChangedDelegate;
    
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnManaChangedDelegate;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnMaxManaChangedDelegate;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FMessageWidgetRowDataDelegate MessageWidgetRowDataDelegate;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category="WidgetData")
    TObjectPtr<UDataTable> MessageWidgetDataTable;
    
    template<typename T>
    T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
    return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
