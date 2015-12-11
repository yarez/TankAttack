// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Bots.h"
#include "Bot.h"

//Global Variables
ABot** bots;

// Sets default values
ABots::ABots()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	BotSpawn = 3;
}

// Called when the game starts or when spawned
void ABots::BeginPlay()
{
	Super::BeginPlay();

	bots = new ABot*[BotSpawn];
	
	for (int32 BotIndex = 0; BotIndex<BotSpawn; BotIndex++)
	{
		const float XOffset = (BotIndex / BotSpawn) * 240; // Divide by dimension
		const float YOffset = (BotIndex%BotSpawn) * 197; // Modulo gives remainder

		// Make postion vector, offset from Grid location
		const FVector BotLocation = FVector(XOffset + 20, YOffset, 0.f) + GetActorLocation();
		ABot *NewBot = GetWorld()->SpawnActor<ABot>(BotLocation, FRotator(0, 0, 0));

		bots[BotIndex] = NewBot;
	}
}

// Called every frame
void ABots::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

