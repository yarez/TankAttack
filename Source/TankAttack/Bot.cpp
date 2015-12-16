/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the cpp file for the AI Bot class. It builds the tank by attaching the turret to the blueprint class, and spawns the shell projectiles moving in the 
	direction set by the BotController class after being called by the behavior tree.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Bot.h"
#include "MyHUD.h"
#include "TimerManager.h"
#include "Shell.h"
#include "Tank.h"
#include "BotController.h"

// Sets default values
ABot::ABot(const class FObjectInitializer&)
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the turret and attatches it to the tank
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TurretMesh(TEXT("/Game/tgun.tgun"));
	BotTurret = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerTurret"));
	BotTurret->AttachTo(RootComponent);
	BotTurret->SetSkeletalMesh(TurretMesh.Object);

	//Initially links the bot tot the bot controller class
	AIControllerClass = ABotController::StaticClass();

	ProjectileClass = AShell::StaticClass();

	Direction = FVector(0.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();

}

void ABot::BotOnFire()
{

	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "Bot Fire ");

		//Gets the rotation for the turret and the location to spawn from
		//Spawns from the location of the socket attached at the end of the turret skeletal mesh
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = BotTurret->GetSocketLocation("GunSocket");

		//Spawns a new shell projectile and sets its velocity to the set direction
		AShell *NewShell = GetWorld()->SpawnActor<AShell>(ProjectileClass, SpawnLocation, SpawnRotation);
		NewShell->ProjectileMovement->SetVelocityInLocalSpace(Direction);
	
		//Only allows the AI bot to shoot again after 1 second
		//bCanFire = false;
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABot::ShotTimerExpired, 1.f);

}

//Allows the bot to shoot again after the shot timer expires
void ABot::ShotTimerExpired()
{
	bCanFire = true;
}