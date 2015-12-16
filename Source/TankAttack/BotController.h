/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the AI Bot Controller class.
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

	//Component pointer for the Blackboard to use with the behavior tree 
	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;

	//Behavior tree pointer to the bot's "brain"
	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;

	//Posses a bot class
	virtual void Possess(class APawn *InPawn);

	//Set the closest enemy found to the target
	void SetEnemy(class APawn *InPawn);

	//Find the closest player to the bot
	UFUNCTION(BlueprintCallable, Category = Behavior)
		void SearchForEnemy();

	//Return true if the found player is within line-of-sight
	UFUNCTION(BlueprintCallable, Category = Behaviour)
		bool PawnCanBeSeen(APawn * target);

	//The Bot's target
	ATank* BestPawn;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:
	
	//keys used for the bot blackboard
	uint8 EnemyKeyID;
	uint8 EnemyLocationID;
	uint8 CanMoveID;
	uint8 HasStartedID;
};