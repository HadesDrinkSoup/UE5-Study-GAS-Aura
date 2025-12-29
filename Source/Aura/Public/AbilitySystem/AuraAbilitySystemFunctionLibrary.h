// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraAbilitySystemFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category= "AuraAbilitySystemLibrary | Widget")
    static UOverlayWidgetController* GetOverlayWidgetController(const UObject* Object);
    UFUNCTION(BlueprintPure, Category= "AuraAbilitySystemLibrary | Widget")
    static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* Object);
};
