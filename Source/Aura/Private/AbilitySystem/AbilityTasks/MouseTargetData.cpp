// This is the GAS project that I'm studying.


#include "AbilitySystem/AbilityTasks/MouseTargetData.h"

#include "AbilitySystemComponent.h"

UMouseTargetData* UMouseTargetData::GetTMouseTargetData(UGameplayAbility* OwningAbility)
{
    UMouseTargetData* MyObj = NewAbilityTask<UMouseTargetData>(OwningAbility);
    return MyObj;
}

void UMouseTargetData::Activate()
{
    if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
    {
        SendMouseCursorData();
    }
    else
    {
        const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
        const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this,  &UMouseTargetData::OnTargetDataReplicatedCallback);
        if (!AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey))
        {
            SetWaitingOnRemotePlayerData();
        }
    }
}

void UMouseTargetData::SendMouseCursorData() const
{
    APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
    FHitResult CursorHit;
    
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Visibility));
    
    PC->GetHitResultUnderCursorForObjects(ObjectTypes, false, CursorHit);
    
    FGameplayAbilityTargetDataHandle TargetDataHandle;
    FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
    Data->HitResult = CursorHit;
    TargetDataHandle.Add(Data);
    
    AbilitySystemComponent->ServerSetReplicatedTargetData(
        GetAbilitySpecHandle(), 
        GetActivationPredictionKey(), 
        TargetDataHandle, 
        FGameplayTag(), 
        AbilitySystemComponent->ScopedPredictionKey);
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(TargetDataHandle);
    }
}

void UMouseTargetData::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) const
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(DataHandle);
    }
}