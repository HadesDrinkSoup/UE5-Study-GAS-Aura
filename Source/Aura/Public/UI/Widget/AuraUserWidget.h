// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetWidgetController(UObject* InWidgetController);
    
    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<UObject> WidgetController;
    
protected:
    void WidgetControllerSet();
};
