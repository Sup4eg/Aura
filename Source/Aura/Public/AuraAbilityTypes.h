#pragma once
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : FGameplayEffectContext 
{
    GENERATED_BODY()
public:
    bool IsCriticalHit() const { return bIsCriticalHit; }
    bool IsBlocked() const { return bIsBlocked; }
    
    void SetIsCriticalHit(const bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
    void SetIsBlocked(const bool bInIsBlocked) { bIsBlocked = bInIsBlocked; }
    
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return FGameplayEffectContext::StaticStruct();
    }

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
    
protected:
    UPROPERTY()
    bool bIsBlocked = false;
    
    UPROPERTY()
    bool bIsCriticalHit = false;
};