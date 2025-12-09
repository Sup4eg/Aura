// Copyright Fireteam Interactive


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AuraProjectile.h"
#include "CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
    const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
    if (!bIsServer)
    {
        return;
    }

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
    if (CombatInterface != nullptr)
    {
        const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
        FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
        Rotation.Pitch = 0.f;
        
        FTransform SpawnTransform;
        SpawnTransform.SetLocation(SocketLocation);
        SpawnTransform.SetRotation(Rotation.Quaternion());
        
        AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, //
            SpawnTransform, //
            GetOwningActorFromActorInfo(), //
            Cast<APawn>(GetOwningActorFromActorInfo()), //
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

        //TODO: Give the projectile a Gameplay Effect spec for causing Damage
        Projectile->FinishSpawning(SpawnTransform);
    }
}