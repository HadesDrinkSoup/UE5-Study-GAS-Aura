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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedDelegate, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedDelegate, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedDelegate, float, NewMaxMana);

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
    FOnHealthChangedDelegate OnHealthChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnMaxHealthChangedDelegate OnMaxHealthChanged;
    
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnManaChangedDelegate OnManaChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnMaxManaChangedDelegate OnMaxManaChanged;
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FMessageWidgetRowDataDelegate MessageWidgetRowData;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category="WidgetData")
    TObjectPtr<UDataTable> MessageWidgetDataTable;
    
    void HealthChanged(const FOnAttributeChangeData& Data) const;
    void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
    void ManaChanged(const FOnAttributeChangeData& Data) const;
    void MaxManaChanged(const FOnAttributeChangeData& Data) const;
    
    template<typename T>
    T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
    return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
