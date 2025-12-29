// This is the GAS project that I'm studying.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
    for (auto [InputAction, InputTag] : AuraInputActions)
    {
        if (InputTag.MatchesTagExact(InputTag))
        {
            return InputAction;
        }
    }
    if (bLogNotFound)
    {
        UE_LOG(LogTemp, Error, TEXT("没有在输入配置[%s]中发现标签[%s]"),*GetNameSafe(this), *InputTag.ToString())
    }
    return nullptr;
}