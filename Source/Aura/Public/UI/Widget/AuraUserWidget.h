// This is the GAS project that I'm studying.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * UAuraUserWidget类 - Aura游戏中所有用户Widget的基类
 * 
 * 该类为所有UI Widget提供了一个通用的框架：
 * 1. 支持Widget控制器模式，分离UI逻辑和数据逻辑
 * 2. 提供蓝图可实现的接口，便于设计师在蓝图中扩展功能
 * 3. 与GAS系统集成，支持动态属性更新
 * 
 * 设计模式：使用类似MVVM的模式，WidgetController作为ViewModel
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /**
     * 设置Widget控制器
     * 这个方法将Widget与控制器绑定，允许Widget访问控制器中的数据和方法
     * 
     * @param InWidgetController - 要设置的控制器对象，通常是UOverlayWidgetController或其子类
     * 
     * 注意：使用UObject*类型是为了保持通用性，实际使用时需要转换为具体的控制器类型
     */
    UFUNCTION(BlueprintCallable)
    void SetWidgetController(UObject* InWidgetController);
	
    // Widget控制器引用
    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<UObject> WidgetController;
	
protected:
    /**
     * Widget控制器设置事件
     * 注意：这是一个蓝图可实现的纯虚函数，没有C++实现
     */
    UFUNCTION(BlueprintImplementableEvent, Category = "Widget")
    void WidgetControllerSet();
};

// 设计说明：
// 1. 分离关注点: Widget只负责显示，WidgetController负责数据和逻辑
// 2. 扩展性: 通过蓝图可实现事件，设计师可以在不修改C++代码的情况下添加UI逻辑
// 3. 类型安全: 使用TObjectPtr确保引用的对象不会被垃圾回收器意外清理
// 4. 通用性: 使用UObject*作为控制器类型，支持多种不同的控制器类