// Copyright Fireteam Interactive


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
    
}