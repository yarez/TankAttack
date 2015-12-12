// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Wall.h"


// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> WallMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> WallMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BreakWall;
		FConstructorStatics()
			: WallMesh(TEXT("/Game/WallMesh.WallMesh"))
			, WallMaterial(TEXT("/Game/WallMaterial.WallMaterial"))
			, BreakWall(TEXT("/Game/Break.Break"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh0"));
	WallMesh->SetStaticMesh(ConstructorStatics.WallMesh.Get());
	//Changes shape of wall
	WallMesh->SetRelativeScale3D(FVector(.5, 2.5, 2.f));
	WallMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	//Sets the starting material color
	WallMesh->SetMaterial(0, ConstructorStatics.WallMaterial.Get());
	WallMesh->SetSimulatePhysics(false);
	WallMesh->AttachTo(DummyRoot);

	hits = 0;
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	if (canBreak)
		WallMesh->SetMaterial(0, BreakMaterial);

}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
