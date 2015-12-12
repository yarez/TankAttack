// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class TANKATTACK_API ATankController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankController();

	FHitResult Hit;
	
protected:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void SetPointLocation(const FVector Location);
};
