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

void ABotController::SearchForEnemy()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
		return;

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	ATank* BestPawn = NULL;

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
			}
		}
	}

	if (BestPawn)
	{
		SetEnemy(BestPawn);
	}
}

void ABotController::SetEnemy(class APawn* InPawn)
{
	BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
	BlackboardComp->SetValue<UBlackboardKeyType_Vector>(EnemyLocationID, InPawn->GetActorLocation());
}


