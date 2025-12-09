// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/InterfaceBase.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IInterfaceBase
{
	GENERATED_BODY()
    
public:
    AAuraEnemy();
    
    /** Begin Enemy InterFace*/
	virtual void HighlightActor() override;
    virtual void UnHighlightActor() override;
    /** End Enemy InterFace*/
    
protected:
    virtual void BeginPlay() override;
};
