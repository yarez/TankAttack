// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Maze.h"


// Sets default values
AMaze::AMaze()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMaze::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaze::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

