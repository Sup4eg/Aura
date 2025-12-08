// Copyright Fireteam Interactive

#include "AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
    UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
    return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
    if (const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled())
    {
        SendMouseCourserData();
    }
    else
    {
        const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
        const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), ActivationPredictionKey).AddUObject(this,
            &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
        const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
        if (!bCalledDelegate)
        {
            SetWaitingOnRemotePlayerData();
        }
    }

    Super::Activate();
}

void UTargetDataUnderMouse::SendMouseCourserData()
{
    FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
    if (const APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get(); IsValid(PlayerController))
    {
        FHitResult CursorHit;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
        FGameplayAbilityTargetDataHandle DataHandle;
        FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
        Data->HitResult = CursorHit;
        DataHandle.Add(Data);

        AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle,
            FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

        if (ShouldBroadcastAbilityTaskDelegates())
        {
            ValidData.Broadcast(DataHandle);
        }
    }
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(DataHandle);
    }
}