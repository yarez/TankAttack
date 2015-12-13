// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Shell.h"
#include "TankController.h"
#include "Wall.h"
#include "Bot.h"
#include "MyHUD.h"
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
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "I'm hitting somethin! ");
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
			otherActor->Destroy();
		}

		/*APill* PillHit = Cast<APill>(otherActor);
		//AMyHUD*	HUD = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (otherActor->GetActorLabel().Contains(TEXT("Tank"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			otherActor->SetActorHiddenInGame(true);
			otherActor->SetActorEnableCollision(false);

			if (PillHit->isWhite)
				invPills++;
			else if (PillHit->isRed){
				GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, "Ouch! "); //Detract Time
				HUD->sub5();
			}
			else if (PillHit->isBlue){
				GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "Refreshing! "); //Add Time
				HUD->add5();
			}
		}
		
		AWall* WallHit = Cast<AWall>(otherActor);
		if (otherActor->GetActorLabel().Contains(TEXT("Health"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			WallActor = otherActor;
		}

		if (otherActor->GetActorLabel().Contains(TEXT("Bot"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			AMyHUD* HUD2 = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if (invPills < 20)
				HUD2->NoWinDraw();
			//GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, "Sorry! Not enough pills! Go find me some more! ");
			else
				HUD2->WinDraw();
			//GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "YOU'RE CURED! YAY");

		}*/


	}
}


