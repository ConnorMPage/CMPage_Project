// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerCharacter.h"

// Sets default values
AC_PlayerCharacter::AC_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Player Camera Setup
	CameraSpringArm = CreateDefaultSubobject < USpringArmComponent>(TEXT("Camera SpringArm"));
	CameraSpringArm->SetupAttachment(FindComponentByClass<USkeletalMeshComponent>());
	CameraSpringArm->SetRelativeLocation(PlayerCamArmPos);
	CameraSpringArm->TargetArmLength = PlayerCamArmLen;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(CameraSpringArm);
	PlayerCamera->SetRelativeLocation(PlayerCamPos);
	PlayerCamera->SetRelativeRotation(PlayerCamRotation);
}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// movement
	PlayerInputComponent->BindAxis(TEXT("ForwardMovement"), this, &AC_PlayerCharacter::ForwardMovement);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &AC_PlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AC_PlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AC_PlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AC_PlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AC_PlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AC_PlayerCharacter::EndCrouch);


//attacks
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AC_PlayerCharacter::OnFire);
	PlayerInputComponent->BindAction(TEXT("SpecialAttack"), IE_Pressed, this, &AC_PlayerCharacter::OnFire);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &AC_PlayerCharacter::BasicAttack);
	PlayerInputComponent->BindAction(TEXT("SpecialAttack"), IE_Released, this, &AC_PlayerCharacter::SpecialAttack);
}


// Player Movement
void AC_PlayerCharacter::ForwardMovement(float AxisAmount)
{
	AddMovementInput(GetActorForwardVector() * AxisAmount);
}

void AC_PlayerCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector() * AxisAmount);
}

void AC_PlayerCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

void AC_PlayerCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}

void AC_PlayerCharacter::StartCrouch()
{
	AC_PlayerCharacter::Crouch();
}

void AC_PlayerCharacter::EndCrouch()
{
	AC_PlayerCharacter::UnCrouch();
}

void AC_PlayerCharacter::OnFire()
{
}

void AC_PlayerCharacter::BasicAttack()
{
	FVector CamLocation;//camera location
	FRotator CamRotation;//camera rotation
	AController* ControllerRef = GetController();//gets the controller
	ControllerRef->GetPlayerViewPoint(CamLocation, CamRotation);//uses the location and rotation to get the cameras viewpoint 
	FVector End = CamLocation + CamRotation.Vector() * CastRange;// gets the end point for a raytrace
	FHitResult Hit;
	bool bTargetHit = GetWorld()->LineTraceSingleByChannel(Hit, CamLocation, End, ECC_Visibility);//fires raytrace
	if (bTargetHit)//if a target is hit
	{
		UE_LOG(LogTemp, Warning, TEXT("Uses Basic Attack on: %s"), *Hit.GetActor()->GetName());//outputs the name of object hit by raytrace
	}
}

void AC_PlayerCharacter::SpecialAttack()
{
	FVector CamLocation;//camera location
	FRotator CamRotation;//camera rotation
	AController* ControllerRef = GetController();//gets the controller
	ControllerRef->GetPlayerViewPoint(CamLocation, CamRotation);//uses the location and rotation to get the cameras viewpoint 
	FVector End = CamLocation + CamRotation.Vector() * CastRange;// gets the end point for a raytrace
	FHitResult Hit;
	bool bTargetHit = GetWorld()->LineTraceSingleByChannel(Hit, CamLocation, End, ECC_Visibility);//fires raytrace
	if (bTargetHit)//if a target is hit
	{
		UE_LOG(LogTemp, Warning, TEXT("Uses Special Attack on: %s"), *Hit.GetActor()->GetName());//outputs the name of object hit by raytrace
	}
}

