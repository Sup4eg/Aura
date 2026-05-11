#pragma once
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()
public:
    bool IsCriticalHit() const { return bIsCriticalHit; }
    bool IsBlocked() const { return bIsBlockedHit; }
    
    void SetIsCriticalHit(const bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
    void SetIsBlockedHit(const bool bInIsBlocked) { bIsBlockedHit = bInIsBlocked; }
    
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return FGameplayEffectContext::StaticStruct();
    }

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
    
protected:
    UPROPERTY()
    bool bIsBlockedHit = false;
    
    UPROPERTY()
    bool bIsCriticalHit = false;
};