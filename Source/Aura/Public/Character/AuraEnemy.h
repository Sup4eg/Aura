// Copyright Fireteam Interactive

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "OverlayWidgetController.h"
#include "Data/CharacterClassInfo.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

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
    virtual void Die() override;
    /**</CombatInterface> */

    void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
public:
    UPROPERTY(BlueprintAssignable)
    FOnAttributeChangedSignature OnHealthChanged;
    
    UPROPERTY(BlueprintAssignable)
    FOnAttributeChangedSignature OnMaxHealthChanged;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bHitReacting = false;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    float BaseWalkSpeed = 200.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float LifeSpan = 5.f;
protected:
    virtual void BeginPlay() override;
    virtual void InitAbilityActorInfo() override;
    virtual void InitializeDefaultAttributes() const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
    int32 Level = 1;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
    ECharacterClass CharacterClass = ECharacterClass::Warrior;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UWidgetComponent> HealthBar;
};