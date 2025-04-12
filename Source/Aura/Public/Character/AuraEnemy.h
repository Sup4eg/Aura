// Copyright Fireteam Interactive

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
    GENERATED_BODY()

public:
    AAuraEnemy();

    /**<EnemyInterface> */
    virtual void HighlightActor() override;
    virtual void UnHighlightActor() override;
    /**</EnemyInterface> */

    /**<CombatInterface> */
    virtual int32 GetPlayerLevel() override;
    /**</CombatInterface> */

    
protected:
    virtual void BeginPlay() override;
    virtual void InitAbilityActorInfo() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
    int32 Level = 1;
};