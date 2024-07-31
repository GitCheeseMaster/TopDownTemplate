// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadLevelArea.generated.h"

/**
 *	LoadLevelArea class
 *  Loads the desired level when the player enter it's collision
 *  The level name can be set per instance
 */
UCLASS()
class TOPDOWN_API ALoadLevelArea : public AActor
{
	GENERATED_BODY()
	
public:

	/** Name of the level to load */
	UPROPERTY(EditAnywhere)
	FName LevelToLoad;

public:	
	// Sets default values for this actor's properties
	ALoadLevelArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// On Overlap
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
