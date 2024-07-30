// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MathUtility.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMathUtility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWN_API IMathUtility
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Lerps an angle and wraps it to -360 ~ 360
	static double LerpAngle(double from, double to, double ratio)
	{
		return FMath::Fmod(from + ((FMath::Fmod(FMath::Fmod(to - from, 360.0) + 540.0, 360.0) - 180.0) * ratio), 360.0);
	}

};
