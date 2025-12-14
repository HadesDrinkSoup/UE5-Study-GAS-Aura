// This is the GAS project that I'm studying.


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
    WidgetController = InWidgetController;
    WidgetControllerSet();
}

void UAuraUserWidget::WidgetControllerSet()
{
}
