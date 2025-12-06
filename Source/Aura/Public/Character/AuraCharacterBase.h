// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

// Abstract标记：表示这是一个抽象类，不能被直接实例化
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

    //武器骨架网格体组件 
    UPROPERTY(EditAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon;
};
