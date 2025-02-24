// Copyright Fireteam Interactive

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaSeconds)
{
    Super::PlayerTick(DeltaSeconds);

    CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false,  CursorHit);
    if (!CursorHit.bBlockingHit) return;
    LastActor = ThisActor;
    ThisActor = CursorHit.GetActor();

    /**
     *Line trace from cursor. There are several scenaries
     * a) LastActor is null && ThisActor is null
     *  - Do nothing
     * b) LastActor is null && ThisActor is valid
     *  - Highlight ThisActor
     * c) LastActor is valid && ThisActor is null
     *  - Unhighlight LastActor
     * d) Both actors are valid, but LastActor != ThisActor
     *  - Unhilight LastActor
     *  - Highliht ThisActor
     * e) Both actors are valid, and are the same actors
     *  - Do nothing
     */

    if (!LastActor && ThisActor)
    {   //Case B
        ThisActor->HighlightActor();
    } else if (LastActor && !ThisActor)
    {
        //Case C
        LastActor->UnHighlightActor();
    } else if (LastActor && ThisActor && LastActor != ThisActor)
    {
        //Case D
        LastActor->UnHighlightActor();
        ThisActor->HighlightActor();
    }
    
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    check(AuraContext);
    
    UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);
    Subsystem->AddMappingContext(AuraContext, 0);

    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;

    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
    
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
    }
}
