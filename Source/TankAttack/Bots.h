// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bot.h"
#include "GameFramework/Actor.h"
#include "Bots.generated.h"

UCLASS()
class TANKATTACK_API ABots : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = BotSpawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;
	
public:	
	// Sets default values for this actor's properties
	ABots();

	//Controls the amount of bots to spawn in the scene
	UPROPERTY(Category = BotSpawn, EditAnywhere, BlueprintReadOnly)
	int32 BotSpawn;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Establishes the bot blueprint as a subclass of ABot
	TSubclassOf<class ABot> BotBlueprint;
	
};
