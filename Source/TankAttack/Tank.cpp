/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the cpp file for the Player Tank class. It builds the tank by attaching the turret, and spawns the shell projectiles moving in the 
	direction set by the TankController class.
*/

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Tank.h"
#include "TankController.h"
#include "Shell.h"
#include "MyHUD.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ATank::ATank()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when tank does
	CameraBoom->TargetArmLength = 2000.f;
	CameraBoom->RelativeRotation = FRotator(80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName); //Attach the camera to the create boom component
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	//Create a turret component
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TurretMesh(TEXT("/Game/tgun.tgun"));
	Turret = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerTurret"));
	Turret->AttachTo(RootComponent); //Attach the turret to the top of the base tank
	Turret->SetSkeletalMesh(TurretMesh.Object);

	//Set the rate at which the tank body turns when the keys are pressed
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

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
	// Trace to see what is under the mouse cursor


}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	//AMyHUD* InHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	//if (InHUD->canMove){
		InputComponent->BindAction("Menu", IE_Pressed, this, &ATank::ToggleMenu);
		InputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ATank::MoveRight);

		// We have 2 versions of the rotation bindings to handle different kinds of devices differently
		// "turn" handles devices that provide an absolute delta, such as a mouse.
		// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
		InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		InputComponent->BindAxis("TurnRate", this, &ATank::TurnAtRate);
		InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		InputComponent->BindAxis("LookUpRate", this, &ATank::LookUpAtRate);

		InputComponent->BindAction("Fire", IE_Pressed, this, &ATank::OnFire);
	//}
}

void ATank::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

//move the tank according to the direction pressed 
void ATank::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AMyHUD* InHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (InHUD->canMove){ //If the game is not paused, canMove is true
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

//move the tank according to the direction pressed 
void ATank::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AMyHUD* InHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (InHUD->canMove){ //If the game is not paused, canMove is true
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

//Toggle the in-game menu, and pause the game
void ATank::ToggleMenu(){
	AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()); //Must cast a HUD pointer to the specific HUD instance in the player controller
	if (HUD->DontDrawHUD == true){
		HUD->DontDrawHUD = false;
		HUD->ThePC->ConsoleCommand("Pause");
	}
}

//Control the projectile firing by clicking the mouse button
void ATank::OnFire()
{
	if (bCanFire)
	{
		//Gets the rotation for the turret and the location to spawn from
		//Spawns from the location of the socket attached at the end of the turret skeletal mesh
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = Turret->GetSocketLocation("GunSocket");

		//Spawns a new shell projectile and sets its velocity to the set direction
		AShell *NewShell = GetWorld()->SpawnActor<AShell>(ProjectileClass, SpawnLocation, SpawnRotation);
		NewShell->ProjectileMovement->SetVelocityInLocalSpace(Direction);

		//Only allows the player tank to shoot again after 1 second
		bCanFire = false;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ATank::ShotTimerExpired, 1.f);

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
}

void ATank::ShotTimerExpired()
{
	bCanFire = true;
}
