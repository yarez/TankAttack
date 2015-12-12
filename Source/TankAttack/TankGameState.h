// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "TankGameState.generated.h"

/**
 * 
 */
UCLASS()
class TANKATTACK_API ATankGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ATankGameState();

	UPROPERTY(Category = Stream, EditAnywhere)
		FRandomStream rand;
	
	
};
