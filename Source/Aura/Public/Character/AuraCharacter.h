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
    
    // 用于初始化服务器端的能力系统组件
    virtual void PossessedBy(AController* NewController) override;
    
    //用于初始化客户端的能力系统组件 
    virtual void OnRep_PlayerState() override;
    
protected:
    
    //弹簧臂组件
    UPROPERTY(EditAnywhere, Category = "Camera")
    TObjectPtr<USpringArmComponent> SpringArm;
    
    //相机组件
    UPROPERTY(EditAnywhere, Category = "Camera")
    TObjectPtr<UCameraComponent> Camera;
    
private:
    //初始化角色能力信息
    virtual void InitAbilityActorInfo() override;
};
