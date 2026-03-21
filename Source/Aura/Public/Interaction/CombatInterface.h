// Copyright Fireteam Interactive

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UMotionWarpingComponent;

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:
    virtual int32 GetPlayerLevel();
    virtual FVector GetCombatSocketLocation() const;
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="MotionWarping")
    void SetFacingTarget(const FVector& TargetLocation);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    UAnimMontage* GetHitReactMontage();
    
    virtual void Die() = 0;
};
