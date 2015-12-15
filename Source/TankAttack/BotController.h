/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the Health Pack class.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
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

	ATank* BestPawn;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:
	uint8 EnemyKeyID;
	uint8 EnemyLocationID;
	uint8 CanMoveID;
	uint8 HasStartedID;
};