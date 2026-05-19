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
        return StaticStruct();
    }

    virtual FAuraGameplayEffectContext* Duplicate() const
    {
        FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
        *NewContext = *this;
        if (GetHitResult())
        {
            // Does a deep copy of the hit result
            NewContext->AddHitResult(*GetHitResult(), true);
        }
        return NewContext;
    }
    
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
    
protected:
    UPROPERTY()
    bool bIsBlockedHit = false;
    
    UPROPERTY()
    bool bIsCriticalHit = false;
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
    enum
    {
        WithNetSerialize = true,
        WithCopy = true
    };
};