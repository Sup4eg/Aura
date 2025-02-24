// Copyright Fireteam Interactive


#include "Character/AuraEnemy.h"


AAuraEnemy::AAuraEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAuraEnemy::HighlightActor()
{
    bHighlighted = true;
}

void AAuraEnemy::UnHighlightActor()
{
    bHighlighted = false;
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();
    
}