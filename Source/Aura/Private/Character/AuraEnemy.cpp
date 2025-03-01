﻿// Copyright Fireteam Interactive


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    if (Weapon)
    {
        Weapon->SetRenderCustomDepth(true);
        Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    }
}

void AAuraEnemy::UnHighlightActor()
{
    GetMesh()->SetRenderCustomDepth(false);
    if (Weapon)
    {
        Weapon->SetRenderCustomDepth(false);
    }
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();

    check(AbilitySystemComponent);
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}