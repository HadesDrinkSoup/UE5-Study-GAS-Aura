// This is the GAS project that I'm studying.

#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"

//获取叠加层Widget控制器
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
    // 检查是否已存在控制器实例，如果不存在则创建新实例
    if (OverlayWidgetController == nullptr)
    {
        // 使用NewObject动态创建Widget控制器实例
        // this: 外部对象，指定控制器所属的HUD实例
        // OverlayWidgetControllerClass: 在编辑器中配置的控制器类
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        // 设置Widget控制器的参数，这些参数用于数据绑定和初始化
        OverlayWidgetController->SetWidgetControllerParams(WCParams);
        // 绑定监听属性回调函数
        OverlayWidgetController->BindCallBacksToDependencies();
        return OverlayWidgetController;
    }
    
    // 返回Widget控制器指针（可能是新创建的或已存在的）
    return OverlayWidgetController;
}

// 将UI组件与GAS系统（能力系统组件和属性集）连接起来 
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    // 安全检查：确保在编辑器中正确设置了Widget类引用
    // checkf会在开发版本中检查条件，如果失败则输出错误信息并停止执行
    checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass未设置，请在BP_AuraHUD设置OverlayWidgetClass"));
    checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass未设置，请在BP_AuraHUD设置OverlayWidgetControllerClass"));
    
    // 创建Widget实例
    // GetWorld(): 获取当前游戏世界上下文
    // OverlayWidgetClass: 在编辑器中配置的Widget蓝图类
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    
    // 将创建的Widget转换为具体的AuraUserWidget类型
    // 这允许我们访问AuraUserWidget特有的功能和方法
    OverlayWidget = Cast<UAuraUserWidget>(Widget);
    
    // 创建Widget控制器参数结构体
    // 这个结构体封装了所有需要传递给Widget控制器的数据
    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
    
    // 获取或创建Widget控制器实例
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
    
    // 将Widget控制器设置为Widget的控制器
    // 这使得Widget可以访问控制器中的数据和方法
    OverlayWidget->SetWidgetController(WidgetController);
    WidgetController->BroadcastInitialValues();
    
    // 将Widget添加到视口，使其在屏幕上可见
    // AddToViewport()是UE4/UE5中显示UI的标准方法
    Widget->AddToViewport();
}

// 实现说明：
// 1. 这个实现使用了延迟初始化模式：Widget控制器在首次需要时才被创建
// 2. 方法间有清晰的职责分离：GetOverlayWidgetController负责控制器管理，InitOverlay负责整体UI初始化
// 3. 通过参数传递确保数据一致性：所有必需的GAS组件都通过参数显式传递
// 4. 类型安全：使用TSubclassOf确保只能分配有效的类引用
// 5. 错误处理：使用checkf在开发时捕获配置错误，避免运行时崩溃