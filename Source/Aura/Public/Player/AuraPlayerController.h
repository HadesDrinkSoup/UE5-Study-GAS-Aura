// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class IInterfaceBase;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AAuraPlayerController();
    
    
protected:
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
    
    //设置输入组件，在此处绑定输入动作和回调函数
    virtual void SetupInputComponent() override;

private:
    //输入映射上下文
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> AuraContext;
    
    //移动输入动作
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;
    
    //移动输入处理函数
    void Move(const FInputActionValue& InputActionValue);
    
    void CursorTrace();
    IInterfaceBase* LastActor;
    IInterfaceBase* ThisActor;
    
};
