// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Tank.h"
#include "MyHUD.h"


// Sets default values
ATank::ATank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(InputComponent);
	//Super::SetupPlayerInputComponent(InputComponent);
	//Put movement for tank inside if statement
	if (HUD->canMove){}
	InputComponent->BindAction("Menu", IE_Pressed, this, &ATank::ToggleMenu);
}

void ATank::ToggleMenu(){
	AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD->DontDrawHUD == true)
		HUD->DontDrawHUD = false;
	else
		HUD->DontDrawHUD = true;
}

