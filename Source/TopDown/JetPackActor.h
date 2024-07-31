// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// generated
#include "JetPackActor.generated.h"

/**
 *	JetPack Actor class
 *  Holds the Jet Pack component
 */
UCLASS()
class TOPDOWN_API AJetPackActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJetPackActor();

private:

	/** Jetpack Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UJetPackComponent* JetPackComponent;

};
