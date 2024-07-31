// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JetPackComponent.generated.h"

/** InternalState for JetPack */
UENUM()
enum class EJetPackState : uint8
{
	Standby,
	Active,
	Cooldown,
};

/**
 *	Jet Pack Component Class.
 *  Calculates a desired impulse from inputs and state
 *  The impulse vector is to be used as desired externally
 *   keeping this class encapsulated and it's funtionality kept to the bare minimum
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWN_API UJetPackComponent : public UActorComponent
{
	GENERATED_BODY()


public:

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float MaximumFuel = 105.f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float FuelDecayRate = 0.5f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float RefuelRate = 0.6f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float MinimumFuelRequiredToActivate = 10.f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float VerticalImpulseStrength = 5.35f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float HorizontalImpulseStrength = 5.1f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float CooldownTime = 1.0f;

public:
	// Sets default values for this component's properties
	UJetPackComponent();

	// Get the desired impulse calculation this tick
	FVector GetDesiredImpulse() const {
		return DesiredImpulse;
	}

	// Try to activate the JetPack. Return false if there is not enough fuel
	bool ActivateJetPack();
	// Deactivates the JetPack
	void DeactivateJetPack();
	// Return whether the JetPack is active or not
	bool IsJetPackActive()const
	{
		return State == EJetPackState::Active;
	}
	// Update horizontal input
	void UpdateHorizontalInput(const FVector& input)
	{
		HorizontalInput = input;
	}
	// Gets the remaining amount of fuel
	float GetFuel() const
	{
		return Fuel;
	}
	// Gets the maximum amount of fuel
	float GetMaximumFuel() const
	{
		return MaximumFuel;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Activate the Niagara Compoents of Attached Actors
	void ActivateJetPackEffects(bool bActive);

private:
	TArray< class UNiagaraComponent* > NiagaraComponents;
	EJetPackState State;
	float Fuel;
	float CooldownTimer;
	FVector HorizontalInput;
	FVector DesiredImpulse;


};
