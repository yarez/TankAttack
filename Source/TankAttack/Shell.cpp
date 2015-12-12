// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"

#include "TankController.h"
#include "HealthPack.h"
#include "Tank.h"
#include "Wall.h"
#include "Bot.h"
#include "MyHUD.h"
#include "Shell.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShell::AShell()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShell::OnHit);		// set up a notification for when this component hits something blocking

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

void AShell::OnHit(AActor* SelfActor, UPrimitiveComponent *otherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "I'm hitting somethin! ");
	AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	TArray<AActor*> OverlapActors;
	UClass* filter = 0;

	AWall* ThisWall = Cast<AWall>(otherActor);
	GetOverlappingActors(OverlapActors, filter);
		if (OverlapActors.Find(ThisWall)){
			//WallActor->SetActorHiddenInGame(true);
			//WallActor->SetActorEnableCollision(false);
		//}

	//}
	//if (GEngine){
		//if (otherActor->GetActorLabel().Contains(TEXT("Wall"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "I HIT WALL! ");
			FVector newDir = this->GetVelocity();
			if (ThisWall->orientation){ //if the wall is vertical
				ProjectileMovement->SetVelocityInLocalSpace(FVector((newDir.X * -1), newDir.Y, newDir.Z));
			}
			else {
				ProjectileMovement->SetVelocityInLocalSpace(FVector(newDir.X, (newDir.Y * -1), newDir.Z));
			}
			if (ThisWall->canBreak){
				//ThisWall->hits += 1;
				//if (ThisWall->hits >= 2){
					ThisWall->SetActorHiddenInGame(false);
					ThisWall->SetActorEnableCollision(false);
			//	}
			}
		}

		ATank* ThisTank = Cast<ATank>(otherActor);
		if (OverlapActors.Find(ThisTank)){
		//if (otherActor->GetActorLabel().Contains(TEXT("Tank"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			HUD->LoseHealth();
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "HIT MYSELF! ");
		}

		ABot* ThisBot = Cast<ABot>(otherActor);
		if (OverlapActors.Find(ThisBot)){
		//if (otherActor->GetActorLabel().Contains(TEXT("Bot"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			
			//ThisBot->hits += 1;
			//if (ThisBot->hits >= 3){
				ThisBot->SetActorHiddenInGame(true);
				ThisBot->SetActorEnableCollision(false);
			//}
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "KILL ENEMY! ");
		}
		
		AHealthPack* ThisPack = Cast<AHealthPack>(otherActor);
		if (OverlapActors.Find(ThisPack)){
		//if (otherActor->GetActorLabel().Contains(TEXT("HealthPack"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)){
			HUD->AddHealth();
			ThisPack->SetActorHiddenInGame(true);
			ThisPack->SetActorEnableCollision(false);
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, "ST MARAS BLESSING! ");
		}
	//}
}


