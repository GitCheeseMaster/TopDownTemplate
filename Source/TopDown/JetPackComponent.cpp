// Fill out your copyright notice in the Description page of Project Settings.

#include "JetPackComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

// Sets default values for this component's properties
UJetPackComponent::UJetPackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize variables
	State = EJetPackState::Standby;
	Fuel = MaximumFuel;
	CooldownTimer = 0.f;
	HorizontalInput = FVector::Zero();
	DesiredImpulse = FVector::Zero();
}

// Called when the game starts
void UJetPackComponent::BeginPlay()
{
	Super::BeginPlay();
	// Cached all Niagara Components
	for (UActorComponent* Component : GetOwner()->GetComponents())
	{
		if (UNiagaraComponent* NiagaraComponent = Cast< UNiagaraComponent >(Component))
		{
			NiagaraComponents.Add(NiagaraComponent);
		}
	}
}

// Called every frame
void UJetPackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Clear the previously desired impulse
	DesiredImpulse = FVector::Zero();

	// Update by state
	switch (State)
	{

	case EJetPackState::Standby:
	{
		Fuel = FMath::Min(Fuel + RefuelRate, MaximumFuel);
	}
	break;
	case EJetPackState::Active:
	{
		// Vertical movement
		const FVector ImpulseVertical = FVector::UnitZ() * VerticalImpulseStrength;
		DesiredImpulse += ImpulseVertical;
		// Allow for horiztontal movement if input present
		if (!HorizontalInput.IsZero()) {
			FVector ImpulseHorizontal(HorizontalInput.X, HorizontalInput.Y, 0.0);
			ImpulseHorizontal* HorizontalImpulseStrength;
			DesiredImpulse += ImpulseHorizontal;
		}

		Fuel = FMath::Max(Fuel - FuelDecayRate, 0.f);

		// Switch to the cooldown state and init the timer
		if (Fuel <= 0.f)
		{
			CooldownTimer = CooldownTime;
			ActivateJetPackEffects(false);
			State = EJetPackState::Cooldown;
		}

	}
	break;
	case EJetPackState::Cooldown:
	{
		CooldownTimer -= DeltaTime;
		if (CooldownTimer <= 0.f)
		{
			State = EJetPackState::Standby;
		}
	}
	break;
	default:
	{
		// Unknown state
		check(false);
	}
	break;
	}

	// Clear the old inputs
	HorizontalInput = FVector::Zero();
}

bool UJetPackComponent::ActivateJetPack()
{
	if (State == EJetPackState::Standby && Fuel > MinimumFuelRequiredToActivate)
	{
		State = EJetPackState::Active;
		ActivateJetPackEffects(true);
		return true;
	}
	return false;
}

void UJetPackComponent::DeactivateJetPack()
{
	if (State == EJetPackState::Active) {
		State = EJetPackState::Standby;
		ActivateJetPackEffects(false);
	}
}

void UJetPackComponent::ActivateJetPackEffects(bool bActive)
{

	if (NiagaraComponents.Num() <= 0)
	{
		return;
	}

	for (UNiagaraComponent* NiagaraComponent : NiagaraComponents) {
		if (bActive)
		{
			NiagaraComponent->Activate();
		}
		else
		{
			NiagaraComponent->Deactivate();
		}
	}
}




