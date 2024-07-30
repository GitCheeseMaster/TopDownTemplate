// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadLevelArea.h"
#include "TopDownCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALoadLevelArea::ALoadLevelArea()
{
	PrimaryActorTick.bCanEverTick = false;
	UBoxComponent* Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Collision"));
	RootComponent = Trigger;
	Trigger->InitBoxExtent(FVector(100.0, 100.0, 100.0));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ALoadLevelArea::BeginPlay()
{
	Super::BeginPlay();

	// Add an event on collision overlap
	// @memo adding this event in the constructor results in the event not firing, so it needs to be added here
	UBoxComponent* Trigger = CastChecked< UBoxComponent >(RootComponent);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALoadLevelArea::OnBeginOverlap);
}

// On Overlap
void ALoadLevelArea::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// No level is set to load
	if (LevelToLoad == "")
	{
		return;
	}
	// If our character is the overlapper, load the desired level
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OtherActor == Character)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::OpenLevel(this, LevelToLoad);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Yellow, OtherActor->GetName());

	}

}

