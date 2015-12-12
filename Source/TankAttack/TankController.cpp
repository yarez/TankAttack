// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "TankController.h"
#include "Tank.h"


ATankController::ATankController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Trace to see what is under the mouse cursor

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

	FVector dir;
	dir = Hit.ImpactPoint - Tank->GetActorLocation();
	dir = dir.GetSafeNormal(1.0f) * 1000;
	Tank->Direction = FVector(dir.X, dir.Y, 0.f);
}