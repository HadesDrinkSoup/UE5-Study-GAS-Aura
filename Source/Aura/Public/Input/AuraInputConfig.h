// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FAuraInputAction
{
    GENERATED_BODY()
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> InputAction = nullptr;
    
    UPROPERTY(EditDefaultsOnly)
    FGameplayTag InputTag = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
    const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false);
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<FAuraInputAction> AuraInputActions;
};
