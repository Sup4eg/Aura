// Copyright Fireteam Interactive


#include "Character/AuraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AAuraCharacter::AAuraCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
    FollowCamera->SetupAttachment(CameraBoom);
}

void AAuraCharacter::BeginPlay()
{
    Super::BeginPlay();
    
}

