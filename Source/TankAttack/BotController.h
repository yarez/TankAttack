// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BotController.generated.h"

/**
*
*/
UCLASS()
class TANKATTACK_API ABotController : public AAIController
{
	GENERATED_BODY()

public:
	ABotController(const class FObjectInitializer& PCIP);

	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;

	virtual void Possess(class APawn *InPawn);

	void SetEnemy(class APawn *InPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void SearchForEnemy();

	UFUNCTION(BlueprintCallable, Category = Behaviour)
		bool PawnCanBeSeen(APawn * target);

protected:
	uint8 EnemyKeyID;
	uint8 EnemyLocationID;
};