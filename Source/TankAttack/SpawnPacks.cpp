/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the Health Pack class.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "SpawnPacks.h"
#include "HealthPack.h"

AHealthPack* HPacks[3];

// Sets default values
ASpawnPacks::ASpawnPacks()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	Size = 10;
	PackSpacing = 240.f;
}

// Called when the game starts or when spawned
void ASpawnPacks::BeginPlay()
{
	Super::BeginPlay();

	int32 NumPacks = 3;
	int randomX = 0;
	int randomY = 0;
	int randomC = 0;

	for (int32 PackIndex = 0; PackIndex<NumPacks; PackIndex++){
		const float XOffset = (PackIndex / Size) * PackSpacing; // Divide by dimension
		const float YOffset = (PackIndex%Size) * 195; // Modulo gives remainder

		// Make postion vector, offset from Grid location
		const FVector PackLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a Pill
		AHealthPack* NewPack = GetWorld()->SpawnActor<AHealthPack>(PackLocation, FRotator(0, 0, 0));

		HPacks[PackIndex] = NewPack;
	}

/*	for (int x = 0; x < (Size*Size) / 2; x++){
		do{
			randomX = rand() % 9;
			randomY = rand() % 9;
		} while (Pills[randomX][randomY]->bHidden);

		Pills[randomX][randomY]->SetActorHiddenInGame(true);
		Pills[randomX][randomY]->SetActorEnableCollision(false);
	}*/

}

// Called every frame
void ASpawnPacks::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

