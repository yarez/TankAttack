/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the Health Pack class.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Tank.h"
#include "BotController.h"
#include "Bot.h"
#include "MyHUD.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

//Default Constructor: Establishes the bot with a Behavior and blackboard component, to link to the behavior tree and blackboard
ABotController::ABotController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	//Make sure BestPawn is initially NULL
	BestPawn = NULL;
}

//Function to posses a bot with the specific BotController instance
void ABotController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	ABot* Bot = Cast<ABot>(InPawn); //Cast the incoming pawn as a bot class
	if (Bot && Bot->BotBehavior) // make sure the incoming bot exists and has a behavior component
	{
		UBlackboardData* BlackboardData = Bot->BotBehavior->BlackboardAsset;

		//initializes the blackboard keys to be set during play
		BlackboardComp->InitializeBlackboard(*BlackboardData);
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");
		CanMoveID = BlackboardComp->GetKeyID("CanMove");
		HasStartedID = BlackboardComp->GetKeyID("HasStarted"); 

		//Begin the behavior tree once the blackboard keys have been established
		BehaviorComp->StartTree(*Bot->BotBehavior);
	}
}

//A function to determine if the found enemy is within the line-of-sight of the bot
bool ABotController::PawnCanBeSeen(APawn* target)
{
	if (target == NULL || GetPawn() == NULL)
	{
		return false;
	}
	FVector difference = target->GetActorLocation() - GetPawn()->GetActorLocation();
	float angle = FVector::DotProduct(difference, GetPawn()->GetActorRotation().Vector());

	//LineOfSightTo determines if the bot can see the actor in the direction it's facing
	if (LineOfSightTo(target, GetPawn()->GetActorLocation()) && angle >0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function to set the bot's target to the closest player-controlled tank
void ABotController::SearchForEnemy()
{
	APawn* MyBot = GetPawn();
	ABot* Tank = Cast<ABot>(GetPawn());
	if (MyBot == NULL)
		return;

	//indicate the that the game has now started
	BlackboardComp->SetValue<UBlackboardKeyType_Bool>(HasStartedID, true);

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	
	//Iterate through the world objects, and set the closest found player to BestPawn
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		ATank* TestPawn = Cast<ATank>(*It);
		
		if (TestPawn)
		{
			const float DistSq = FVector::Dist(TestPawn->GetActorLocation(), MyLoc);
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
				if (PawnCanBeSeen(*It)){
					FRotator Rot = FRotationMatrix::MakeFromX(BestPawn->GetActorLocation() - Tank->GetActorLocation()).Rotator(); //Find the rotator required for the turret to face it's target
					Tank->BotTurret->SetWorldRotation(FRotator(0.f, Rot.Yaw, 0.f)); //Point the turret to it's target
				}
			}
		}
	}

	if (BestPawn)
	{
		SetEnemy(BestPawn); //Once the closest player is found, set the Bot's target
	}

}

void ABotController::SetEnemy(class APawn* InPawn)
{
	//Set the blackboard keys to the object and location of the found enemy, for use in the MoveTo behavior tree task
	BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
	BlackboardComp->SetValue<UBlackboardKeyType_Vector>(EnemyLocationID, InPawn->GetActorLocation());


	//Calculates and sets the direction for the AI bot's projectile
	ABot* ThisBot = Cast<ABot>(GetPawn());
	ATank *Enemy = Cast<ATank>(this->BestPawn);
	FVector dir;
	dir = Enemy->GetActorLocation() - ThisBot->GetActorLocation();	//Finds the vector between the AI bot and the player tank
	dir = dir.GetSafeNormal(1.0f) * 1000;							//Normalizes and scales the vector for a uniform speed
	ThisBot->Direction = FVector(dir.X, dir.Y, 0.f);				//Zeros out the Z value so the projectile moves solely on the horizontal plane
}


// Called every frame
void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AMyHUD* InHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	BlackboardComp->SetValue<UBlackboardKeyType_Bool>(CanMoveID, InHUD->canMove);

}




