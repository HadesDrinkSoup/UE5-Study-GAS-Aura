// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Character/AuraCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
    AAuraCharacter();
    
protected:
    
    //弹簧臂组件
    UPROPERTY(EditAnywhere, Category = "Camera")
    TObjectPtr<USpringArmComponent> SpringArm;
    
    //相机组件
    UPROPERTY(EditAnywhere, Category = "Camera")
    TObjectPtr<UCameraComponent> Camera;
};
