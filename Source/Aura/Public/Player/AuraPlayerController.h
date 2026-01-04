// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class USplineComponent;
class UAuraInputConfig;
struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IInterfaceBase;
class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AAuraPlayerController();

    bool GetTargeting() const {return bTargeting;};
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
    
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> ShiftAction;
    bool bShiftKeyDown = false;
    
    //移动输入处理函数
    void Move(const FInputActionValue& InputActionValue);
    void ShiftPressed() {bShiftKeyDown = true;}
    void ShiftReleased() {bShiftKeyDown = false;}
    
    
    void AbilityInputTagPressed(FGameplayTag InputTag);
    void AbilityInputTagReleased(FGameplayTag InputTag);
    void AbilityInputTagHeld(FGameplayTag InputTag);
    
    void CursorTrace();
    
    
    FHitResult CursorHit;
    IInterfaceBase* LastActor;
    IInterfaceBase* ThisActor;
    
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UAuraInputConfig> InputConfig;

    UPROPERTY()
    TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
    
    UAuraAbilitySystemComponent* GetASC();
    
    /** 鼠标左键移动 **/
    /*
    FVector CachedDestination = FVector::ZeroVector; 
    float FollowTime = 0.0f;
    float ShortPressThreshold = 0.5f;
    bool bAutoRunning = false;
    void AutoRun();
    */
    bool bTargeting = false;
    
    UPROPERTY(EditDefaultsOnly)
    float AutoRunAcceptanceRadius = 50.0f;
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USplineComponent> Spline;
    
};
