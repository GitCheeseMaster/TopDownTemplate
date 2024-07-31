// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

/**
 *	TopDownCharacter class
 *  The class for out player character
 *  Check if any of it's attached actors hold a Jet Pack component, and caches it
 *  Updates the HUD
 */
UCLASS(Blueprintable)
class ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownCharacter();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

public:
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns Jetpack subobject **/
	FORCEINLINE class UJetPackComponent* GetJetPackComponent() const { return AttachedJetPackComponent; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** HUD Class */
	UPROPERTY(EditAnywhere)
	TSubclassOf< class UTopDownPlayerHUD >TopDownPlayerHUDClass;
	/** HUD */
	UPROPERTY();
	class UTopDownPlayerHUD* TopDownPlayerHUD;

private:
	/** Child Actor's Jetpack Component */
	class UJetPackComponent* AttachedJetPackComponent;

};

