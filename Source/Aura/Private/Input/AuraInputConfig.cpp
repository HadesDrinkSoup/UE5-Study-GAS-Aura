// This is the GAS project that I'm studying.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
    for (const FAuraInputAction& Action : AbilityInputActions)
    {
        if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
        {
            return Action.InputAction;
        }
    }
    if (bLogNotFound)
    {
        UE_LOG(LogTemp, Error, TEXT("没有在输入配置[%s]中发现标签[%s]"),*GetNameSafe(this), *InputTag.ToString())
    }
    return nullptr;
}