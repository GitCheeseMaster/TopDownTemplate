// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
struct FEnhancedInputActionValueBinding;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *	TopDownPlayerController class
 *  The class to control our player character
 *  Tries to activate the players Jet Pack if one exists during jumping
 *  Otherwise a normal jump will be exectued
 */
UCLASS()
class ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

	/** Blueprint Data */
public:

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;

	/** Look Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction = nullptr;

	/** Move Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveButtonAction = nullptr;

	/** Jump Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpButtonAction = nullptr;

public:
	ATopDownPlayerController();

protected:

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();
	
	// Look
	void OnLookActionTriggered();
	// Move
	void OnMoveActionTriggered();
	// Jump
	void OnJumpActionStarted();
	void OnJumpActionTriggered();
	void OnJumpActionReleased();

private:
	FEnhancedInputActionValueBinding* pLookActionBinding = nullptr;
	FEnhancedInputActionValueBinding* pMoveActionBinding = nullptr;


};


