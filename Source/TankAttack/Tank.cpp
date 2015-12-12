// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "Tank.h"
#include "TankController.h"
#include "MyHUD.h"
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
	CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TurretMesh(TEXT("/Game/tgun.tgun"));
	Turret = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerTurret"));
	Turret->AttachTo(RootComponent);
	Turret->SetSkeletalMesh(TurretMesh.Object);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;


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
	//}
}

void ATank::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATank::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATank::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AMyHUD* InHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (InHUD->canMove){
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void ATank::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AMyHUD* InHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (InHUD->canMove){
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

void ATank::ToggleMenu(){
	AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD->DontDrawHUD == true){
		HUD->DontDrawHUD = false;
		HUD->ThePC->ConsoleCommand("Pause");
	}
}
