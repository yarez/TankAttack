/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the AI Bot class.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Bot.generated.h"

UCLASS()
class TANKATTACK_API ABot : public ACharacter
{
	GENERATED_BODY()

public:

	//Bot fire function. Blueprint callable, so the behavior tree can access it
	UFUNCTION(BlueprintCallable, Category = GunGunGun)
	void BotOnFire();

	void ShotTimerExpired();

	//Set the initial amount of hits on the Bot to 0
	int hits = 0;

	//Direction Vector for the bot's turret
	FVector Direction;

	/* Flag to control firing  */
	bool bCanFire = true;

	// Sets default values for this character's properties
	ABot(const class FObjectInitializer&);

	//Turret Mesh for the bot's turret
	UPROPERTY(Category = TankParts, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* BotTurret;

	//Behavior component to control the AI
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AShell> ProjectileClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
