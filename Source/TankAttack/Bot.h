// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Bot.generated.h"

UCLASS()
class TANKATTACK_API ABot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABot(const class FObjectInitializer&);

	UPROPERTY(Category = TankParts, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* BotTurret;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

};
