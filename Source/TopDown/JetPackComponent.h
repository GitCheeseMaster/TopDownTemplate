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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWN_API UJetPackComponent : public UActorComponent
{
	GENERATED_BODY()


public:

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float MaximumFuel = 100.f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float FuelDecayRate = 0.5f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float RefuelRate = 0.6f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float MinimumFuelRequiredToActivate = MaximumFuel / 10.f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float VerticalImpulseStrength = 5.0f;

	UPROPERTY(Category = "JetPack", EditAnywhere, BlueprintReadWrite)
	float HorizontalImpulseStrength = 5.0f;

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

	float GetFuel() const
	{
		return Fuel;
	}

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
	TArray< class UNiagaraComponent* > AttachedNiagaraComponents;
	EJetPackState State;
	float Fuel;
	float CooldownTimer;
	FVector HorizontalInput;
	FVector DesiredImpulse;


};
