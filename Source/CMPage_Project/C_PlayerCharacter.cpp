// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerCharacter.h"

// Sets default values
AC_PlayerCharacter::AC_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//creates the characters weapon
	CharacterWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player Weapon"));
	FName fnWeaponSocket = TEXT("Weapon");
	CharacterWeapon->SetupAttachment(GetMesh(), fnWeaponSocket);//attaches to hand socket
	CharacterWeapon->SetRelativeLocation(WeaponLocation);

	//Player Camera Setup
	CameraSpringArm = CreateDefaultSubobject < USpringArmComponent>(TEXT("Camera SpringArm"));
	CameraSpringArm->SetupAttachment(FindComponentByClass<USkeletalMeshComponent>());
	CameraSpringArm->SetRelativeLocation(PlayerCamArmPos);
	CameraSpringArm->TargetArmLength = PlayerCamArmLen;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(CameraSpringArm);
	PlayerCamera->SetRelativeLocation(PlayerCamPos);
	PlayerCamera->SetRelativeRotation(PlayerCamRotation);


	//creates map arm
	MapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MapAttachmentArm"));
	MapArm->SetupAttachment(FindComponentByClass<USkeletalMeshComponent>());//attaches to mesh
	//creates map camera
	MapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MapCamera"));
	MapCamera->SetupAttachment(MapArm);
	//sets map arm values
	MapArm->SetRelativeLocation(MapArmLocation);
	MapArm->SetRelativeRotation(MapArmRotation);
	MapArm->TargetArmLength = MapArmLength;
}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsPlayer == false)//checks if its the player or ai
	{
		MapCamera->DestroyComponent();//destroys the camera of ais 
	}
	AmountOfBulletsInMag = MaxMagCapacity;//sets the amount of bullets in mag
	GameModeRef = Cast<ACMPage_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
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

	//actions
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AC_PlayerCharacter::Reload);
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
	if (AmountOfBulletsInMag > EmptyMag)
	{
		AmountOfBulletsInMag--;
		
		AController* ControllerRef = GetController();//gets the controller
		FVector CamLocation;//camera location
		FRotator CamRotation;//camera rotation
		ControllerRef->GetPlayerViewPoint(CamLocation, CamRotation);//uses the location and rotation to get the cameras viewpoint 
		FVector End = CamLocation + CamRotation.Vector() * CastRange;// gets the end point for a raytrace
		if (IsPlayer == true)
		{
			GameModeRef->GetStatData(ShotFired);
		}
		FHitResult Hit;
		bool bTargetHit = GetWorld()->LineTraceSingleByChannel(Hit, CamLocation, End, ECC_Visibility);//fires raytrace
		if (bTargetHit)//if a target is hit
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *Hit.GetActor()->GetName());//outputs the name of object hit by raytrace


			AActor* TraceOwner = GetOwner();
			if (TraceOwner == nullptr)
			{
				return;
			}
			UGameplayStatics::ApplyDamage(
				Hit.GetActor(), //actor that will be damaged
				WeaponDamage, //the base damage to apply
				TraceOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);
		}
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunShotSound, GetActorLocation(), 0.75f, 1.0f, 0.0f);//plays a gunshot sound effect
	}
}

void AC_PlayerCharacter::SpecialAttack()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunShotSound, GetActorLocation(), 0.75f, 1.0f, 0.0f);//plays a gunshot sound effect
	if (AmountOfBulletsInMag > EmptyMag)
	{
		AmountOfBulletsInMag--;

		AController* ControllerRef = GetController();//gets the controller
		FVector CamLocation;//camera location
		FRotator CamRotation;//camera rotation
		ControllerRef->GetPlayerViewPoint(CamLocation, CamRotation);//uses the location and rotation to get the cameras viewpoint 
		FVector End = CamLocation + CamRotation.Vector() * CastRange;// gets the end point for a raytrace
		if (IsPlayer == true)
		{
			GameModeRef->GetStatData(ShotFired);
		}
		FHitResult Hit;
		bool bTargetHit = GetWorld()->LineTraceSingleByChannel(Hit, CamLocation, End, ECC_Visibility);//fires raytrace
		if (bTargetHit)//if a target is hit
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *Hit.GetActor()->GetName());//outputs the name of object hit by raytrace


			AActor* TraceOwner = GetOwner();
			if (TraceOwner == nullptr)
			{
				return;
			}
			UGameplayStatics::ApplyDamage(
				Hit.GetActor(), //actor that will be damaged
				WeaponSpecialDamage, //the base damage to apply
				TraceOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);
		}
	}
}

void AC_PlayerCharacter::Reload()
{
	if (AmountOfBulletsInMag == EmptyMag)//if mag is empty
	{
		if (MaxMagCapacity <= AmountOfBullets)//if theres more than 15 bullets
		{
			AmountOfBulletsInMag = MaxMagCapacity;//sets to max
			AmountOfBullets -= MaxMagCapacity;//takes the max from reserves
		}
		else//less than 15
		{
			AmountOfBulletsInMag += AmountOfBullets;//adds whats left
			AmountOfBullets -= AmountOfBullets;//empty reserves
		}
	}
	else if (AmountOfBulletsInMag < MaxMagCapacity && AmountOfBulletsInMag > EmptyMag)//if mag is lower than 15 but above 0
	{
		MagDifference = MaxMagCapacity - AmountOfBulletsInMag;//finds the difference
		if (MagDifference <= AmountOfBullets)//checks if theres less bullts than th edifference
		{
			AmountOfBulletsInMag += MagDifference;//adds to mag
			AmountOfBullets -= MagDifference;//take sthe differnece
		}
		else
		{
			AmountOfBulletsInMag += AmountOfBullets;//adds to mag
			AmountOfBullets -= AmountOfBullets;//takes from reserves
		}

	}
	if (IsPlayer == true)//if is player
	{
		GameModeRef->GetStatData(ReloadDone);//asks game mode to change hud
	}
}

float AC_PlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (PlayerHealth <= NoHealth)//if health is empty
	{

		IsDead = true;//sets target to dead
		UE_LOG(LogTemp, Warning, TEXT("dead"));
		if (IsPlayer == false)//if its ai
		{
			UE_LOG(LogTemp, Warning, TEXT("enemy"));
			Destroy();
			GameModeRef->EnemyKilled();//executes a gamemode funtion
		}
		else//if player
		{
			GameModeRef->GameOver();//ends the game
			Destroy();
		}

	}
	else//if health isnt empty
	{
		PlayerHealth -= DamageAmount;//decreases health
		UE_LOG(LogTemp, Warning, TEXT("actor damaged"));
	}
	if (IsPlayer == true)
	{
		
		GameModeRef->GetStatData(DamageTaken);//asks game mode to change hud

	}
	return 0.0f;
}

