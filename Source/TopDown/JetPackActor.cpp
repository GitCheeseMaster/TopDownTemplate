// Fill out your copyright notice in the Description page of Project Settings.

#include "JetPackActor.h"
#include "JetPackComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

// Sets default values
AJetPackActor::AJetPackActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create a JetPack component...
	JetPackComponent = CreateDefaultSubobject<UJetPackComponent>(TEXT("JetPack"));
}
