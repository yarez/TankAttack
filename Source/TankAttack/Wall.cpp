/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the cpp file for the Wall class. It sets up the wall instances for the walls
	that are used in the Maze class
*/

#include "TankAttack.h"
#include "Wall.h"

AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization of WallMesh, WallMaterial, BreakWall
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
	//Setup the WallMesh
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh0"));
	WallMesh->SetStaticMesh(ConstructorStatics.WallMesh.Get());
	//Changes shape of wall
	WallMesh->SetRelativeScale3D(FVector(.5, 2.5, 2.f));
	WallMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	//Sets the starting material color
	WallMesh->SetMaterial(0, ConstructorStatics.WallMaterial.Get());
	//Turns off physics
	WallMesh->SetSimulatePhysics(false);
	//Attach WallMesh to a dummy root
	WallMesh->AttachTo(DummyRoot);

	//How many hits has the wall received?
	hits = 0;
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{

	Super::BeginPlay();
	//If the wall canBreak the material is set to a new material
	if (canBreak)
		WallMesh->SetMaterial(0, BreakMaterial);

}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
