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
	
	/** Input handlers action. */
	
	// Look
	void OnLookActionTriggered();
	// Move
	void OnMoveActionStarted();
	void OnMoveActionTriggered();
	void OnMoveActionReleased();
	// Jump
	void OnJumpActionStarted();
	void OnJumpActionTriggered();
	void OnJumpActionReleased();

	

private:
	FEnhancedInputActionValueBinding* pLookActionBinding = nullptr;
	FEnhancedInputActionValueBinding* pMoveActionBinding = nullptr;


};


