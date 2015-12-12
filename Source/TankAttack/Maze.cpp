// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Maze.h"
#include "Wall.h"
#include <ctime>

//Global Variables
AWall** walls;
AWall** mazewalls;
int32 NumH;
int32 NumV;

// Sets default values
AMaze::AMaze()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	Size = 10;
}

// Called when the game starts or when spawned
//Trace disjoint sets and make it work for 10by10
//Also add the organic part in here to remove the extra walls 
void AMaze::BeginPlay()
{
	Super::BeginPlay();

	//srand(time(NULL));
	//GetWorldTimerManager().SetTimer(mhandle, this, &AMaze::Organic, 3.0f, true);

	NumH = (Size*Size) + Size;
	NumV = NumH;
	int cells = 0;


	walls = new AWall*[NumH + NumV];
	//mazewalls = new AWall*[NumH + NumV - (Size*Size - 1) - 1];

	// Loop to spawn each horizontal wall
	for (int32 BlockIndex = 0; BlockIndex<NumH; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * 240; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * 197; // Modulo gives remainder

		// Make postion vector, offset from Grid location
		const FVector WallLocation = FVector(XOffset + 20, YOffset, 0.f) + GetActorLocation();
		AWall *NewWall = GetWorld()->SpawnActor<AWall>(WallLocation, FRotator(0, 0, 0));
		NewWall->drawit = true;
		NewWall->orientation = false; //horizontal = false

		if (BlockIndex >= 0 && BlockIndex <= (Size - 1)){
			NewWall->cella = cells;
			NewWall->cellb = NULL;
			NewWall->innerw = false;
		}
		else if (BlockIndex >= (NumH - Size)){
			NewWall->cella = NULL;
			NewWall->cellb = cells;
			NewWall->innerw = false;
		}
		else{
			NewWall->cella = cells;
			NewWall->cellb = cells - Size;
			NewWall->innerw = true;
		}

		walls[BlockIndex] = NewWall;
		cells++;
	}

	cells = 0;
	// Loop to spawn each vertical wall
	for (int32 BlockIndex = 0; BlockIndex < NumV; BlockIndex++)
	{
		const float XOffset = (BlockIndex / (Size + 1)) * 240; // Divide by dimension
		const float YOffset = (BlockIndex % (Size + 1)) * 198; // Modulo gives remainder
		const FVector WallLocation = FVector(XOffset + 135, YOffset - 95, 0.f) + GetActorLocation();
		AWall *NewWall = GetWorld()->SpawnActor<AWall>(WallLocation, FRotator(0, 90, 0));
		NewWall->drawit = true;
		NewWall->orientation = true; //vertical = true

		if (BlockIndex == 0 || (BlockIndex % (Size + 1)) == 0){
			NewWall->cella = NULL;
			NewWall->cellb = cells++;
			NewWall->innerw = false;
		}
		else if ((BlockIndex % (Size + 1)) == Size){
			NewWall->cella = cells - 1;
			NewWall->cellb = NULL;
			NewWall->innerw = false;
		}
		else{
			NewWall->cella = cells - 1;
			NewWall->cellb = cells++;
			NewWall->innerw = true;
		}

		walls[BlockIndex + NumH] = NewWall;
	}

	//openexit = false;
	RemoveWalls();
	//RemoveExit();

}

//Finds the roots for the disjoint set
int AMaze::FindRoot(int leaf, int cells[])
{
	int root = leaf;
	while (cells[root] != -1){
		root = cells[root];
	}
	return root;
}

//Removes walls randomly until a solvable maze is created
void AMaze::RemoveWalls(void)
{
	int totalsets = Size*Size;
	int wallID, mwID = 0;
	int aroot, broot;
	//ATankGameState* TankState = Cast<ATankGameState>(GetWorld()->GetGameState());
	//int32 Seed = TankMode->rand.GetCurrentSeed();

	stream.GetInitialSeed();

	int* cells = new int[Size*Size];
	for (int i = 0; i < totalsets; i++){
		cells[i] = -1;
	}

	while (totalsets > 1){
		//wallID = rand() % (NumH + NumV);
		wallID = stream.FRandRange(0, NumH + NumV);
		while (!(walls[wallID]->drawit) || !(walls[wallID]->innerw)){
			wallID = stream.FRandRange(0, NumH + NumV);
		}

		aroot = FindRoot(walls[wallID]->cella, cells);
		broot = FindRoot(walls[wallID]->cellb, cells);

		if (aroot != broot){
			cells[broot] = aroot;
			walls[wallID]->drawit = false;
			totalsets--;
		}
	}

	//Randomly generates entrance to maze
	//wallID = rand() % 9;
	//walls[wallID]->drawit = false;

	//Keeps track of only the walls to be drawn into the scene
	for (int i = 0; i < NumH + NumV; i++){
		if (walls[i]->drawit){
			//mazewalls[mwID] = walls[i];
			mwID++;
		}
		else{
			walls[i]->SetActorHiddenInGame(true);
			walls[i]->SetActorEnableCollision(false);
		}
	}
	for (int i = 0; i < 60; i++){
		//mwID = rand() % ((NumH + NumV) - 1);
		mwID = stream.FRandRange(0, (NumH + NumV) - 1);
		while (!walls[mwID]->innerw || !walls[mwID]->drawit){
			mwID = stream.FRandRange(0, (NumH + NumV) - 1);
		}
		walls[mwID]->SetActorHiddenInGame(true);
		walls[mwID]->SetActorEnableCollision(false);
		walls[mwID]->drawit = false;
	}

	for (int i = 0; i < 7; i++){
		mwID = stream.FRandRange(0, (NumH + NumV) - 1);
		while (!walls[mwID]->innerw || !walls[mwID]->drawit){
			mwID = stream.FRandRange(0, (NumH + NumV) - 1);
		}
		walls[mwID]->canBreak = true;
	}
}

// Called every frame
void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




