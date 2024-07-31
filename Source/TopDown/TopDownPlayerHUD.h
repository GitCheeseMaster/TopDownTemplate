// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopDownPlayerHUD.generated.h"

/**
 *	HUD class for the TopDownPlayer
 *	Hold the ProgressBar that represents the fuel bar
 */
UCLASS()
class TOPDOWN_API UTopDownPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Update HUD with current fuel */
	void SetFuel(float CurrentFuel, float MaxFuel);

	/** Widget to display current fuel */
	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UProgressBar* FuelBar;

	
};
