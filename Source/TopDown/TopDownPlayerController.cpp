// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TopDownCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "JetPackComponent.h"
#include "MathUtility.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATopDownPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ATopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup moveaction input events/bindings

		// Look Action
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnLookActionTriggered);
		pLookActionBinding = &EnhancedInputComponent->BindActionValue(LookAction);

		// Move Action
		EnhancedInputComponent->BindAction(MoveButtonAction, ETriggerEvent::Started, this, &ATopDownPlayerController::OnMoveActionStarted);
		EnhancedInputComponent->BindAction(MoveButtonAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnMoveActionTriggered);
		EnhancedInputComponent->BindAction(MoveButtonAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::OnMoveActionReleased);
		EnhancedInputComponent->BindAction(MoveButtonAction, ETriggerEvent::Canceled, this, &ATopDownPlayerController::OnMoveActionReleased);
		pMoveActionBinding = &EnhancedInputComponent->BindActionValue(MoveButtonAction);


		// Jump Action
		EnhancedInputComponent->BindAction(JumpButtonAction, ETriggerEvent::Started, this, &ATopDownPlayerController::OnJumpActionStarted);
		EnhancedInputComponent->BindAction(JumpButtonAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnJumpActionTriggered);
		EnhancedInputComponent->BindAction(JumpButtonAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::OnJumpActionReleased);
		EnhancedInputComponent->BindAction(JumpButtonAction, ETriggerEvent::Canceled, this, &ATopDownPlayerController::OnJumpActionReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATopDownPlayerController::OnMoveActionStarted()
{

}

void ATopDownPlayerController::OnMoveActionTriggered()
{
	if (pMoveActionBinding == nullptr)
	{
		return;
	}

	ATopDownCharacter* ControlledCharacter = CastChecked< ATopDownCharacter >(GetCharacter());

	if (ControlledCharacter == nullptr)
	{
		return;
	}

	// Move
	FVector2D Input = pMoveActionBinding->GetValue().Get<FVector2D>();
	FVector MoveDirection(Input.Y, Input.X, 0.0);
	ControlledCharacter->AddMovementInput(MoveDirection, 1.0, false);

	// Update the JetPack inputs
	UJetPackComponent* JetPackComponent = ControlledCharacter->GetJetPackComponent();
	JetPackComponent->UpdateHorizontalInput(MoveDirection);
}
void ATopDownPlayerController::OnMoveActionReleased()
{


}

void ATopDownPlayerController::OnJumpActionStarted()
{
	ACharacter* ControlledCharacter = GetCharacter();
	if (ControlledCharacter == nullptr)
	{
		return;
	}
	ControlledCharacter->Jump();
}

void ATopDownPlayerController::OnJumpActionTriggered()
{
	ATopDownCharacter* ControlledCharacter = CastChecked< ATopDownCharacter >(GetCharacter());
	if (ControlledCharacter == nullptr)
	{
		return;
	}

	// Activate the JetPack if possible
	UJetPackComponent* JetPackComponent = ControlledCharacter->GetJetPackComponent();
	if (!JetPackComponent->IsJetPackActive())
	{
		if (JetPackComponent->ActivateJetPack())
		{
			ControlledCharacter->StopJumping();
		}
	}
}

void ATopDownPlayerController::OnJumpActionReleased()
{
	ATopDownCharacter* ControlledCharacter = CastChecked< ATopDownCharacter >(GetCharacter());
	if (ControlledCharacter == nullptr)
	{
		return;
	}

	UJetPackComponent* JetPackComponent = ControlledCharacter->GetJetPackComponent();
	JetPackComponent->DeactivateJetPack();
}

void ATopDownPlayerController::OnLookActionTriggered()
{
	if (pLookActionBinding == nullptr)
	{
		return;
	}

	// Check the input, if not significant keep previous rotation
	auto InputRaw = pLookActionBinding->GetValue().Get<FVector2D>();
	auto Input = InputRaw.GetSafeNormal(0.1);
	if (Input.IsZero())
	{
		return;
	}

	// Make the pawn look toward input direction
	// @todo The Camera is fixed currently, but if it were to change angle we would need to account for that in these calculation
	float LerpAmount = 0.1;
	auto TargetAngle = FMath::RadiansToDegrees(FMath::Atan2(Input.X, Input.Y));
	ControlRotation.Yaw = IMathUtility::LerpAngle(ControlRotation.Yaw, TargetAngle, 0.1);
}
