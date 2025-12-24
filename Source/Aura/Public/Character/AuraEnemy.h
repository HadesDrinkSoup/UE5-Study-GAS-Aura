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
    
    /** Base InterFace*/
	virtual void HighlightActor() override;
    virtual void UnHighlightActor() override;
    /** end Base InterFace*/
    
    /** Combat InterFace*/
    virtual int32 GetLevel() override;
    /** end Combat InterFace*/
protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
    int32 Level = 1;
};
