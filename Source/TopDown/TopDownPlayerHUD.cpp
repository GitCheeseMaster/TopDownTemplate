// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPlayerHUD.h"
#include "Components/ProgressBar.h"

void UTopDownPlayerHUD::SetFuel(float CurrentFuel, float MaxFuel)
{
	if (FuelBar)
	{
		FuelBar->SetPercent(FMath::Clamp(CurrentFuel / MaxFuel, 0.f, 1.f));
	}
}
