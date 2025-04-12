// Copyright Fireteam Interactive

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
    GENERATED_BODY()

public:
    AAuraCharacter();

    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;

    /**<CombatInterface> */
    virtual int32 GetPlayerLevel() override;
    /**</CombatInterface> */

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> FollowCamera;

    virtual void InitAbilityActorInfo() override;
};