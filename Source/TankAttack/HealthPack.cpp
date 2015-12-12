// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "HealthPack.h"


// Sets default values
AHealthPack::AHealthPack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Healthpack;
		FConstructorStatics()
			: Healthpack(TEXT("/Game/Healthpack.Healthpack"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	Healthpack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HPackMesh0"));
	Healthpack->SetStaticMesh(ConstructorStatics.Healthpack.Get());
	Healthpack->SetRelativeScale3D(FVector(2, 2, 2));
	Healthpack->SetRelativeLocation(FVector(130.f, 0.f, 7.f));

	Healthpack->SetSimulatePhysics(false);
	Healthpack->AttachTo(DummyRoot);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPack::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

