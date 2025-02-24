// Copyright Fireteam Interactive


#include "Character/AuraCharacter.h"


AAuraCharacter::AAuraCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AAuraCharacter::BeginPlay()
{
    Super::BeginPlay();
    
}

void AAuraCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AAuraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

