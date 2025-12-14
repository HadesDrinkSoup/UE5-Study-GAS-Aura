// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceBase.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceBase : public UInterface
{
	GENERATED_BODY()
};


class AURA_API IInterfaceBase
{
	GENERATED_BODY()
    
public: 
    /**
    * HighlightActor - 高亮显示角色/物体
    * 纯虚函数（= 0）：表示此函数必须在派生类中提供具体实现。
    * @see AAuraEnemy::HighlightActor() - 此接口的一个具体实现
    */
    virtual void HighlightActor() = 0;

    // UnHighlightActor - 取消角色/物体的高亮
    virtual void UnHighlightActor() = 0;
    
};
