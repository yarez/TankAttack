/*
	Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
	Date: 12-12-2015

	This is the header file for the Player Tank class. 
*/

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Tank.generated.h"

UCLASS()
class TANKATTACK_API ATank : public ACharacter
{
	GENERATED_BODY()

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	

public:
	// Sets default values for this character's properties
	ATank();

	//Direction vector for the tank's turret, used by OnFire()
	FVector Direction;

	//Mesh component for the turret
	UPROPERTY(Category = TankParts, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Turret;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AShell> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	//Function to fire a projectile
	UFUNCTION(BlueprintCallable, Category = GunGunGun)
		void OnFire();

	//Pause the game and display the menu
	void ToggleMenu();

protected:

	/* Flag to control firing  */
	bool bCanFire = true;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

<<<<<<< HEAD
=======
	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/

>>>>>>> origin/master
	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void ShotTimerExpired();
};
