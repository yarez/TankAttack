/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the Health Pack class.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "TankController.h"
#include "Tank.h"


ATankController::ATankController()
{
	//Display the cursor as a crosshair to aid aiming
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Trace to see what is under the mouse cursor
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetPointLocation(Hit.ImpactPoint);
	}

}

void ATankController::SetPointLocation(const FVector Location){
	ATank* Tank = Cast<ATank>(GetPawn());
	if (Tank){
		// We hit something, point there
		FRotator Rot = FRotationMatrix::MakeFromX(Location - Tank->GetActorLocation()).Rotator();
		Tank->Turret->SetWorldRotation(FRotator(0.f, Rot.Yaw, 0.f));
	}

	//Calculates and sets the direction for the player tank's projectile 
	FVector dir;
	dir = Hit.ImpactPoint - Tank->GetActorLocation();	//Finds the vector between the tank and the cursor
	dir = dir.GetSafeNormal(1.0f) * 1000;				//Normalizes and scales the vector to a uniform speed
	Tank->Direction = FVector(dir.X, dir.Y, 0.f);		//Zeros out the  Z value so the projectile moves solely on the hoeizontal plane
}