// AuraHUD.h
// Aura游戏的HUD类，负责管理游戏界面和UI组件
// 该类继承自Unreal Engine的AHUD基类，并集成了Gameplay Ability System (GAS)

#pragma once

// 包含必要的头文件
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AuraHUD.generated.h"

// 前向声明相关类，减少编译依赖
class UOverlayWidgetController;
struct FWidgetControllerParams;

/**
 * AAuraHUD类 - 游戏的主要HUD类
 * 负责管理游戏界面的创建、初始化和更新
 * 特别集成了GAS系统，用于显示角色属性和能力信息
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
    GENERATED_BODY()

public:
    
    // 叠加层Widget实例指针
    UPROPERTY()
    TObjectPtr<UAuraUserWidget> OverlayWidget;
    
    //获取叠加层Widget控制器
    UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
    
    UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
    
    // 初始化叠加层UI
    void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
    
private:
    
    //叠加层Widget类引用（在编辑器中可配置
    UPROPERTY(EditAnywhere)
    TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
    
    // 叠加层Widget控制器实例指针
    UPROPERTY()
    TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
    
    // 叠加层Widget控制器类引用（在编辑器中可配置）
    UPROPERTY(EditAnywhere)
    TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
    
    UPROPERTY(EditAnywhere)
    TSubclassOf<UAuraUserWidget> AttributeMenuWidgetClass;
    UPROPERTY()
    TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
    UPROPERTY(EditAnywhere)
    TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};