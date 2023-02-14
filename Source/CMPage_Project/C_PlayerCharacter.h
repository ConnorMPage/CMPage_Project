// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
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
};
