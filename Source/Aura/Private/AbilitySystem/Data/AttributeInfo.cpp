// This is the GAS project that I'm studying.


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFind) const
{
    for (const FAuraAttributeInfo& AttributeInfo : AttributeInfos)
    {
        if (AttributeInfo.AttributeTag.MatchesTagExact(AttributeTag))
        {
            return AttributeInfo;
        }   
    }
    if (bLogNotFind)
    {
        UE_LOG(LogTemp, Error, TEXT("没有在属性[%s]中发现标签[%s]"),*GetNameSafe(this), *AttributeTag.ToString())
    }
    return FAuraAttributeInfo();
}
