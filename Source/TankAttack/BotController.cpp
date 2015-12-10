// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "BotController.h"
#include "Bot.h"
#include "Tank.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

ABotController::ABotController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
}

void ABotController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	ABot* Bot = Cast<ABot>(InPawn);
	if (Bot && Bot->BotBehavior)
	{
		UBlackboardData* BlackboardData = Bot->BotBehavior->BlackboardAsset;
		BlackboardComp->InitializeBlackboard(*BlackboardData);
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");

		BehaviorComp->StartTree(*Bot->BotBehavior);
	}
}

bool ABotController::PawnCanBeSeen(APawn* target)
{
	if (target == NULL || GetPawn() == NULL)
	{
		return false;
	}
	FVector difference = target->GetActorLocation() - GetPawn()->GetActorLocation();
	float angle = FVector::DotProduct(difference, GetPawn()->GetActorRotation().Vector());

	if (LineOfSightTo(target, GetPawn()->GetActorLocation()) && angle >0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ABotController::SearchForEnemy()
{
	APawn* MyBot = GetPawn();
	ABot* Tank = Cast<ABot>(GetPawn());
	if (MyBot == NULL)
		return;

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	ATank* BestPawn = NULL;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		ATank* TestPawn = Cast<ATank>(*It);
		if (PawnCanBeSeen(*It)){
			if (TestPawn)
			{
				const float DistSq = FVector::Dist(TestPawn->GetActorLocation(), MyLoc);
				if (DistSq < BestDistSq)
				{
					BestDistSq = DistSq;
					BestPawn = TestPawn;
				}
			}
		}
	}

	if (BestPawn)
	{
		SetEnemy(BestPawn);
		FRotator Rot = FRotationMatrix::MakeFromX(BestPawn->GetActorLocation() - Tank->GetActorLocation()).Rotator();
		Tank->BotTurret->SetWorldRotation(FRotator(0.f, Rot.Yaw, 0.f));
	}
}

void ABotController::SetEnemy(class APawn* InPawn)
{
	BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
	BlackboardComp->SetValue<UBlackboardKeyType_Vector>(EnemyLocationID, InPawn->GetActorLocation()*.5);
}




