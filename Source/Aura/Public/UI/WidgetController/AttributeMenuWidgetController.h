// Copyright Fireteam Interactive

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;
struct FGameplayTag;
class UAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

UCLASS(Blueprintable, BlueprintType)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
    GENERATED_BODY()


public:
    virtual void BroadcastInitialValues() override;
    virtual void BindCallbacksToDependencies() override;

    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FAttributeInfoSignature AttributeInfoDelegate;

private:
    void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UAttributeInfo> AttributeInfo;
    
};
