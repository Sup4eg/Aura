// Copyright Fireteam Interactive


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
    const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
    OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
    OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
    OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
    check(AbilitySystemComponent);

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
                          .AddLambda([this](const FOnAttributeChangeData& Data)
                          {
                              OnHealthChanged.Broadcast(Data.NewValue);
                          });

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
                          .AddLambda([this](const FOnAttributeChangeData& Data)
                          {
                              OnMaxHealthChanged.Broadcast(Data.NewValue);
                          });

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
                          .AddLambda([this](const FOnAttributeChangeData& Data)
                          {
                              OnManaChanged.Broadcast(Data.NewValue);
                          });

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
                          .AddLambda([this](const FOnAttributeChangeData& Data)
                          {
                              OnMaxManaChanged.Broadcast(Data.NewValue);
                          });

    Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
        [this](const FGameplayTagContainer& AssetTags)
        {
            for (const auto& Tag : AssetTags)
            {
                FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");
                if (Tag.MatchesTag(MessageTag))
                {
                    const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
                    const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
                    MessageWidgetRowDelegate.Broadcast(*Row);
                }
            }
        }
        );
}