// This is the GAS project that I'm studying.


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
    //将传入的控制器引用保存到成员变量
    WidgetController = InWidgetController;
    // 触发蓝图可实现事件
    WidgetControllerSet();
}