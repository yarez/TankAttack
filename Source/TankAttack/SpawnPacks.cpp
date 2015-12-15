/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the cpp file for the Spawn Packs class which places the health packs in the scene.
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

	//Size based on the 10x10 maze grid spawned
	Size = 10;
	PackSpacing = 240.f;
}

// Called when the game starts or when spawned
void ASpawnPacks::BeginPlay()
{
	Super::BeginPlay();

	//Sets 3 health packs into the scene
	int32 NumPacks = 3;

	for (int32 PackIndex = 0; PackIndex<NumPacks; PackIndex++){
		const float XOffset = (PackIndex / Size) * PackSpacing; // Divide by dimension
		const float YOffset = (PackIndex%Size) * 195; // Modulo gives remainder

		// Make postion vector, offset from Grid location
		const FVector PackLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a Health Pack
		AHealthPack* NewPack = GetWorld()->SpawnActor<AHealthPack>(PackLocation, FRotator(0, 0, 0));

		HPacks[PackIndex] = NewPack;
	}

}

// Called every frame
void ASpawnPacks::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

