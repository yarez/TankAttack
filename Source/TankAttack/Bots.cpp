// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Bots.h"

//Global Variables
ABot** bots;

// Sets default values
ABots::ABots()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	//Find the blueprint object class for ABot
	static ConstructorHelpers::FObjectFinder<UBlueprint> EnemyBot(TEXT("Blueprint'/Game/EnemyBot.EnemyBot'"));
	if (EnemyBot.Object){
		BotBlueprint = (UClass*)EnemyBot.Object->GeneratedClass;
	}

	//Establishes the number of bots to spawn
	BotSpawn = 3;
}

// Called when the game starts or when spawned
void ABots::BeginPlay()
{
	Super::BeginPlay();

	//Loop to spawn the bots next to each other
	for (int32 BotIndex = 0; BotIndex<BotSpawn; BotIndex++)
	{
		const float XOffset = (BotIndex / BotSpawn) * 300; // Divide by dimension
		const float YOffset = (BotIndex%BotSpawn) * 600; // Modulo gives remainder

		// Make postion vector, offset from Grid location
		const FVector BotLocation = FVector(XOffset + 20, YOffset, 0.f) + GetActorLocation();
		ABot *NewBot = GetWorld()->SpawnActor<ABot>(BotBlueprint, BotLocation, FRotator(0, 0, 0));

	}
}

// Called every frame
void ABots::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

