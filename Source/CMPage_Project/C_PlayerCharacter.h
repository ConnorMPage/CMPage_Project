// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TargetPoint.h"
#include "CMPage_ProjectGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "C_PlayerCharacter.generated.h"

UCLASS()
class CMPAGE_PROJECT_API AC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//basic character setup
	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;

	//spawn positions
	UPROPERTY(VisibleAnywhere)
		FVector PlayerCamPos = FVector(0.85f, 60.0f, 132.58f);//camera location
	UPROPERTY(VisibleAnyWhere)
		FRotator PlayerCamRotation = FRotator(0, -25, 0);// Camera Rotation
	UPROPERTY(VisibleAnywhere)
		FVector PlayerCamArmPos = FVector(0.0f, 0.0f, 90.0f);//location of the spring arm
	UPROPERTY(VisibleAnywhere)
		float PlayerCamArmLen = 200.0f;//Length of Springarm


	UPROPERTY(EditAnywhere)
		float CastRange = 5000.0f;
	//functions for player movement 
	//Movement functions
	UFUNCTION()
		void ForwardMovement(float AxisAmount);//for forward movment 
	UFUNCTION()
		void Strafe(float AxisAmount);//left and right movement
	UFUNCTION()
		void LookUp(float AxisAmount);//looking up and down
	UFUNCTION()
		void Turn(float AxisAmount);//rotating to the left and right
	UFUNCTION()
		void StartCrouch();
	UFUNCTION()
		void EndCrouch();
	UFUNCTION()
		void OnFire();
	UFUNCTION()
		void BasicAttack();
	UFUNCTION()
		void SpecialAttack();
	UFUNCTION()
		void Reload();//reload process
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
			AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
		int MaxMagCapacity = 15;
	UPROPERTY(EditAnywhere)
		float MaxPlayerHealth = 100.0f;
	UPROPERTY(EditAnywhere)
		int AmountOfBulletsInMag = MaxMagCapacity;
	UPROPERTY(EditAnywhere)
		float PlayerHealth = MaxPlayerHealth;
	UPROPERTY(EditAnywhere)
		int AmountOfBullets = 75;
	UPROPERTY(EditAnywhere)
		float NoHealth = 0.0f;
	UPROPERTY(EditAnywhere)
		USoundBase* GunShotSound;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* MapArm;//creates springarm for the map camera
	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* MapCamera;//Creates map camera
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* CharacterWeapon;// this is a second mesh for the gun
	UPROPERTY(VisibleAnywhere)
		FRotator MapArmRotation = FRotator(0.0f, -90.0f, 90.0f);//rotation of map arm
	UPROPERTY(VisibleAnywhere)
		FVector MapArmLocation = FVector(0.0f, 0.0f, 130.0f);//location of map arm
	UPROPERTY(EditAnywhere)
		float MapArmLength = 500.0f;// length of map arm
	UPROPERTY(VisibleAnywhere)
		FVector WeaponLocation = FVector(0.0f, 0.0f, -4.0f);// location of player weapon

	UPROPERTY(EditAnywhere)
		float WeaponDamage = 25.0f;//amount of damage to do
	UPROPERTY(EditAnywhere)
		float WeaponSpecialDamage = 40.0f;//amount of damage to do
	
	UPROPERTY(EditAnywhere)
		bool IsDead = false;//checks if dead
	UPROPERTY(EditAnywhere)
		bool IsPlayer = true;//checks if player 
	UPROPERTY(EditAnywhere)
		int EmptyMag = 0;
	UPROPERTY(EditAnywhere)
		int MagDifference;//checks how much is left in mag compared to how much it can hold
	
	UPROPERTY(VisibleAnywhere)
		ACMPage_ProjectGameModeBase* GameModeRef;// creates reference to the gamemode
	UPROPERTY(EditAnywhere)
		TArray<AActor*> Waypoints;//create waypoint array
	//to update hud
	UPROPERTY(VisibleAnywhere)
		int ShotFired = 1;
	UPROPERTY(VisibleAnywhere)
		int ReloadDone = 2;
	
	UPROPERTY(VisibleAnywhere)
		int DamageTaken = 4;

	
	
};
