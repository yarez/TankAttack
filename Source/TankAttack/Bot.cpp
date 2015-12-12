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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TurretMesh(TEXT("/Game/tgun.tgun"));
	BotTurret = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerTurret"));
	BotTurret->AttachTo(RootComponent);
	BotTurret->SetSkeletalMesh(TurretMesh.Object);

	AIControllerClass = ABotController::StaticClass();
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();

}

void ABot::BotOnFire()
{
	// try and fire a projectile
	//if (ProjectileClass != NULL)
	//{
	//if (bCanFire)
	//{

	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "I'm spawning ");

		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		//const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);
		const FVector SpawnLocation = BotTurret->GetSocketLocation("GunSocket");

		AShell *NewShell = GetWorld()->SpawnActor<AShell>(ProjectileClass, SpawnLocation, SpawnRotation);
		ATank *Enemy = Cast<ABotController>(Controller)->BestPawn;
		NewShell->ProjectileMovement->SetVelocityInLocalSpace(Direction);
	

		//bCanFire = false;
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABot::ShotTimerExpired, 1.f);

		// spawn the projectile at the muzzle
		//World->SpawnActor<AShell>(ProjectileClass, SpawnLocation, SpawnRotation);

	//}

}

void ABot::ShotTimerExpired()
{
	bCanFire = true;
}