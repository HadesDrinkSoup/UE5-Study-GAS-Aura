// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType )
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:
    virtual int32 GetLevel();
    virtual FVector GetCombatSocketLocation();
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void GetFacingTarget(const FVector& FacingTarget);
};
