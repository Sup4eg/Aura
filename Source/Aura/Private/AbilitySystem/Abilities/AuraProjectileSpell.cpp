// Copyright Fireteam Interactive


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AuraProjectile.h"
#include "CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    const bool bIsServer = HasAuthority(&ActivationInfo);
    if (!bIsServer)
    {
        return;
    }

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
    if (CombatInterface != nullptr)
    {
        const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
        FTransform SpawnTransform;
        SpawnTransform.SetLocation(SocketLocation);
        //TODO: Set the Projectile Rotation
        
        AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, //
            SpawnTransform, //
            GetOwningActorFromActorInfo(), //
            Cast<APawn>(GetOwningActorFromActorInfo()), //
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

        //TODO: Give the projectile a Gameplay Effect spec for causing Damage
        Projectile->FinishSpawning(SpawnTransform);
    }
}