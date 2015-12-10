// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Bot.h"
#include "BotController.h"

// Sets default values
ABot::ABot(const class FObjectInitializer&)
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABotController::StaticClass();
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}