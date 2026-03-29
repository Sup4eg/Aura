// Copyright Fireteam Interactive

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CombatInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
    
    virtual UAnimMontage* GetHitReactMontage_Implementation() override;
    virtual void Die() override;
    
    UFUNCTION(NetMulticast, Reliable)
    virtual void MulticastHandleDeath();
protected:
	virtual void BeginPlay() override;

    virtual void InitAbilityActorInfo();
    
    void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
    virtual void InitializeDefaultAttributes() const;
    void AddCharacterAbilities() const;

    // ICombatInterface
    virtual FVector GetCombatSocketLocation() const override;
    //ICombatInterface
    
    void Dissolve();
    
    UFUNCTION(BlueprintImplementableEvent)
    void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

    UFUNCTION(BlueprintImplementableEvent)
    void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
    
protected:
    UPROPERTY(EditAnywhere, Category="Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon;

    UPROPERTY(EditAnywhere, Category="Combat")
    FName WeaponTipSocketName;
    
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
    
    /*Dissolve Effects */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
private:
    UPROPERTY(EditAnywhere, Category="Attributes")
    TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
    
    UPROPERTY(EditAnywhere, Category = "Combat")
    UAnimMontage* HitReactMontage;
};
