// This is the GAS project that I'm studying.


#include "UI/WidgetController/AuraWidgetController.h"

/**
 * 设置Widget控制器参数
 * 
 * 这是Widget控制器初始化的核心方法，将外部传入的系统引用存储到成员变量中
 * 这些引用为后续的数据绑定和事件监听提供基础
 * 
 * @param WCParams - Widget控制器参数结构体
 *                 包含以下四个核心系统引用：
 *                 1. PlayerController: 玩家控制器，处理输入和UI交互
 *                 2. PlayerState: 玩家状态，存储玩家相关游戏数据
 *                 3. AbilitySystemComponent: GAS能力系统组件，管理技能和效果
 *                 4. AttributeSet: 属性集，存储角色的具体属性值
 * 
 * 功能流程：
 * 1. 从参数结构体中提取各个系统引用
 * 2. 将引用分别存储到对应的成员变量中
 * 3. 为后续的委托绑定和事件监听做准备
 */
void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
    // 玩家控制器赋值
    PlayerController = WCParams.PlayerController;
    
    // 玩家状态赋值
    PlayerState = WCParams.PlayerState;
    
    // 能力系统组件赋值
    AbilitySystemComponent = WCParams.AbilitySystemComponent;
    
    // 属性集赋值
    AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindCallBacksToDependencies()
{
}
