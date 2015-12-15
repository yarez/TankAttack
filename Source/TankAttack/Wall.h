/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the Wall class.
*/

#pragma once

#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class TANKATTACK_API AWall : public AActor
{
	GENERATED_BODY()

		/** Dummy root component */
		UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WallMesh;

public:
	// Sets default values for this actor's properties
	AWall();

	//Boolean values that include the orientation of the wall
	//if the wall is going to be drawn, if it is an inner wall
	//and if it can be broken
	bool drawit, innerw, orientation, canBreak;
	//bool movRight, movLeft, alreadymoving;
	//Variables used with disjoint sets
	int cella, cellb;
	//int steps;
	//How many hits the wall has received
	int hits;

	/** Pointer to Breakable material used on walls that can break*/
	UPROPERTY()
	class UMaterialInstance* BreakMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetHWallMesh() const { return WallMesh; }	
	
};
