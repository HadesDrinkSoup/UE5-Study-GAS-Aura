// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "AuraWidgetController.generated.h"

/**
 * FWidgetControllerParams - Widget控制器参数结构体
 * 
 * 这个结构体封装了Widget控制器所需的所有核心系统引用
 * 使用UE的反射系统（USTRUCT, GENERATED_BODY, UPROPERTY）使其在蓝图和C++中都可访问
 * 
 * 设计目的：
 * 1. 集中管理Widget控制器需要的所有依赖
 * 2. 简化参数传递，避免多个独立的参数
 * 3. 支持蓝图访问，便于在蓝图中配置和使用
 */
USTRUCT(BlueprintType)  // BlueprintType使该结构体可在蓝图中使用
struct FWidgetControllerParams
{
    GENERATED_BODY()  // UE反射系统必需，生成反射代码
    
    // 默认构造函数
    FWidgetControllerParams(){}
    
    // 带参数的构造函数，便于快速初始化
    FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
        : PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS){}
    
    // 玩家控制器 - 处理玩家输入和UI交互
    UPROPERTY(EditAnywhere, BlueprintReadWrite)  // 可在蓝图中读写，在编辑器中可编辑
    TObjectPtr<APlayerController> PlayerController = nullptr;
    
    // 玩家状态 - 包含玩家相关的游戏数据（如分数、等级等
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<APlayerState> PlayerState = nullptr;
    
    // 能力系统组件 - GAS核心，管理技能、效果和属性
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
    
    // 属性集 - 定义和存储角色的所有属性（生命值、法力值等）
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * UAuraWidgetController类 - 所有Widget控制器的基类
 * 
 * 作用：
 * 1. 作为UI和GAS系统之间的桥梁
 * 2. 管理UI需要的数据绑定和更新逻辑
 * 3. 提供统一的接口给不同类型的Widget控制器
 * 
 * 继承自UObject，可以独立于Actor存在
 * 这种设计使得控制器可以轻松地在不同UI组件间共享和重用
 */
UCLASS(Blueprintable, BlueprintType)//Blueprintable可创建派生的蓝图
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
    //设置Widget控制器参数 
    UFUNCTION(BlueprintCallable)
    void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
    
    UFUNCTION(BlueprintCallable)
    virtual void BroadcastInitialValues();
    virtual void BindCallBacksToDependencies();
    
protected:
    
    // 玩家控制器引用 - 用于处理输入和UI交互逻辑
    UPROPERTY(BlueprintReadOnly, Category="WidgetController")
    TObjectPtr<APlayerController> PlayerController;
    
    // 玩家状态引用 - 包含玩家特定的游戏数据
    UPROPERTY(BlueprintReadOnly, Category="WidgetController")
    TObjectPtr<APlayerState> PlayerState;
    
    // 能力系统组件引用 - GAS核心，用于监听属性变化和技能事件
    UPROPERTY(BlueprintReadOnly, Category="WidgetController")
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
    
    //属性集引用 - 存储角色属性的实际数据
    UPROPERTY(BlueprintReadOnly, Category="WidgetController")
    TObjectPtr<UAttributeSet> AttributeSet;
};

// 架构设计说明：
// 1. 数据流: GAS系统 -> UAuraWidgetController -> UAuraUserWidget
// 2. 职责分离: 
//    - UI (View): 只负责显示，不包含业务逻辑
//    - Widget控制器 (ViewModel): 处理数据和UI更新逻辑
//    - GAS系统 (Model): 管理游戏数据和逻辑
// 3. 扩展性: 可以创建多个WidgetController子类，分别处理不同的UI模块
//           例如: UOverlayWidgetController, UInventoryWidgetController等
