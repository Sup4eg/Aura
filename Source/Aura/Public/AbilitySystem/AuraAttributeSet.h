// Copyright Fireteam Interactive

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
    GENERATED_BODY()

    FEffectProperties() {}

    FGameplayEffectContextHandle EffectContextHandle;
    
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> SourceAsc;

    UPROPERTY()
    TObjectPtr<AActor> SourceAvatarActor;

    UPROPERTY()
    TObjectPtr<AController> SourceController;
    
    UPROPERTY()
    TObjectPtr<ACharacter> SourceCharacter;

    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> TargetAsc;
    
    UPROPERTY()
    TObjectPtr<AActor> TargetAvatarActor;

    UPROPERTY()
    TObjectPtr<AController> TargetController = nullptr;
    
    UPROPERTY()
    TObjectPtr<ACharacter> TargetCharacter;
};

template<class T>
using TStaticFuncPtr = TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UAuraAttributeSet();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
    
    /*
     * Primary Attributes
     */

    //Increase physical damage
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category="Primary Attributes")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(ThisClass, Strength)

    //Increase magical damage, increases mana
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category="Primary Attributes")
    FGameplayAttributeData Intelligence;
    ATTRIBUTE_ACCESSORS(ThisClass, Intelligence)

    //Increases armor and armor penetration
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category="Primary Attributes")
    FGameplayAttributeData Resilience;
    ATTRIBUTE_ACCESSORS(ThisClass, Resilience)

    //Increase health 
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category="Primary Attributes")
    FGameplayAttributeData Vigor;
    ATTRIBUTE_ACCESSORS(ThisClass, Vigor)
    
    /*
     * Vital Attributes
     */
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Vital Attributes")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(ThisClass, Health)
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category="Vital Attributes")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(ThisClass, Mana)

    /*
     * Secondary Attributes
    */

    //Depends on resilience. Reduces damage taken, improves block chance
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category="Secondary Attributes")
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(ThisClass, Armor)

    //Depends on resilience. Ignores percentage of enemy Armor, increases Crit Hit Chance
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category="Secondary Attributes")
    FGameplayAttributeData ArmorPenetration;
    ATTRIBUTE_ACCESSORS(ThisClass, ArmorPenetration)   

    //Depends on Armor. Chance to cut incoming damage in half
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category="Secondary Attributes")
    FGameplayAttributeData BlockChance;
    ATTRIBUTE_ACCESSORS(ThisClass, BlockChance)

    //Depends on ArmorPenetration. Chance to double damage plus critical hit bonus.
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category="Secondary Attributes")
    FGameplayAttributeData CriticalHitChance;
    ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitChance)

    //Depends on ArmorPenetration. Bonus damage added when a critical hit is scored
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category="Secondary Attributes")
    FGameplayAttributeData CriticalHitDamage;
    ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitDamage)

    //Depends on Armor. Reduces critical hit chance of attacking enemies
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category="Secondary Attributes")
    FGameplayAttributeData CriticalHitResistance;
    ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitResistance)   

    //Depends on Vigor. Amount of health regenerated every 1 second
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category="Secondary Attributes")
    FGameplayAttributeData HealthRegeneration;
    ATTRIBUTE_ACCESSORS(ThisClass, HealthRegeneration)

    //Depends on Intelligence. Amount of mana regenerated every 1 second
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category="Secondary Attributes")
    FGameplayAttributeData ManaRegeneration;
    ATTRIBUTE_ACCESSORS(ThisClass, ManaRegeneration)   

    //Depends on Vigor. Maximum amount of Health obtainable
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Secondary Attributes")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth)

    //Depends on Intelligence. Maximum amount of Mana obtainable
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category="Secondary Attributes")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxMana)

    /*
     * Meta Attributes
    */
    UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
    FGameplayAttributeData IncomingDamage;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage)
    
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

    UFUNCTION()
    void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

    UFUNCTION()
    void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

    UFUNCTION()
    void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
    
    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

    UFUNCTION()
    void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
    
    UFUNCTION()
    void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

    UFUNCTION()
    void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

    UFUNCTION()
    void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

    UFUNCTION()
    void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

    UFUNCTION()
    void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

    UFUNCTION()
    void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
    
private:
    void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};