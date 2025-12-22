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
    FOnAttributeChangedDelegate OnHealthChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnMaxHealthChanged;
    
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnManaChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnAttributeChangedDelegate OnMaxManaChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FMessageWidgetRowDataDelegate MessageWidgetRowData;
    
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
