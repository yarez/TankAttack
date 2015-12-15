/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the Health Pack class.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Shell.h"
#include "TankController.h"
#include "Wall.h"
#include "Bot.h"
#include "MyHUD.h"
#include "HealthPack.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShell::AShell()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	AActor* ShellAsActor = Cast<AActor>(this);
	ShellAsActor->OnActorHit.AddDynamic(this, &AShell::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AShell::OnHit(AActor* SelfActor, AActor *otherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GEngine){
		if (otherActor->GetActorLabel().Contains(TEXT("Wall"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			AWall* ThisWall = Cast<AWall>(otherActor);
			//FVector newDir = this->GetVelocity();
			//if (ThisWall->orientation){ //if the wall is vertical
			//	ProjectileMovement->SetVelocityInLocalSpace(FVector((newDir.X * -1), newDir.Y, newDir.Z));
			//}
			//else {
			//	ProjectileMovement->SetVelocityInLocalSpace(FVector(newDir.X, (newDir.Y * -1), newDir.Z));
			//}

			if (ThisWall->canBreak){
				ThisWall->hits++;
				if (ThisWall->hits >= 2){
					ThisWall->SetActorHiddenInGame(true);
					ThisWall->SetActorEnableCollision(false);
				}
			}
			
		}

		else if (otherActor->GetActorLabel().Contains(TEXT("Bot"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			ABot* ThisBot = Cast<ABot>(otherActor);
			ThisBot->hits += 1;
			if (ThisBot->hits >= 3){
				otherActor->Destroy();
			}
			this->Destroy();
		}

		else if(otherActor->GetActorLabel().Contains(TEXT("Tank"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			HUD->LoseHealth();
			this->Destroy();
		}

		else if (otherActor->GetActorLabel().Contains(TEXT("HealthPack"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			HUD->AddHealth();
			AHealthPack* ThisPack = Cast<AHealthPack>(otherActor);
			ThisPack->SetActorHiddenInGame(true);
			ThisPack->SetActorEnableCollision(false);
			this->Destroy();
		}
	}
}
