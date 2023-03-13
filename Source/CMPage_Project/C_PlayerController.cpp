// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerController.h"

void AC_PlayerController::BeginPlay()
{
	GameModeRef = Cast<ACMPage_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	Super::BeginPlay();
	CrosshairUI = CreateWidget(this, CrosshairClass);//attaches widget class to the widget object
	if (CrosshairUI != nullptr)//if nullptr return out of fucntion
	{
		CrosshairUI->AddToViewport();//adds crosshair to viewport
	}
	PlayerHudUI = CreateWidget(this, PlayerHudClass);//attaches widget class to the widget object
	if (PlayerHudUI != nullptr)//if nullptr return out of fucntion
	{
		PlayerHudUI->AddToViewport();//adds hud to viewport
	}
	MiniMapUI = CreateWidget(this, MiniMapClass);//attaches widget class to the widget object
	if (MiniMapUI != nullptr)//if nullptr return out of fucntion
	{
		MiniMapUI->AddToViewport();//adds mini map to viewport
	}
}

void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProvideStats(GameModeRef->UpdateStats());//updates stats 
	GameModeRef->GetStatData(EmptyMag);
}

void AC_PlayerController::ProvideStats(int StatOption)
{
	if (StatOption == ShotFired)
	{
		AmountOfBulletsInMag--;//decreases amount of bullets
	}
	else if (StatOption == ReloadDone)
	{
		if (AmountOfBulletsInMag == EmptyMag)//if mag is empty
		{
			if (MaxMagCapacity <= AmountOfBullets)//more bullets than mag size
			{
				AmountOfBulletsInMag = MaxMagCapacity;//fill mag
				AmountOfBullets -= MaxMagCapacity;//take size away from reserves
			}
			else
			{
				AmountOfBulletsInMag += AmountOfBullets;//adds remaining bullets
				AmountOfBullets -= AmountOfBullets;//empty reserves
			}
		}
		else if (AmountOfBulletsInMag < MaxMagCapacity && AmountOfBulletsInMag > EmptyMag)//if mag is lower than 15 but above 0
		{
			MagDifference = MaxMagCapacity - AmountOfBulletsInMag;//gets the difference 
			if (MagDifference <= AmountOfBullets)
			{
				AmountOfBulletsInMag += MagDifference;//adds amount of bullets to mag
				AmountOfBullets -= MagDifference;//takes away the difference 
			}
			else
			{
				AmountOfBulletsInMag += AmountOfBullets;//adds all remaining bullets
				AmountOfBullets -= AmountOfBullets;//empty reserves 
			}

		}
	}
	else if (StatOption == DamageTaken)
	{
		PlayerHealth -= WeaponDamage;//decrease health
	}
	
}

int AC_PlayerController::GetMagazineAmount()
{
	return AmountOfBulletsInMag;//return int for bullets
}

int AC_PlayerController::GetAmmoAmount()
{
	return AmountOfBullets;
}

float AC_PlayerController::GetHealthAmount()
{
	HealthPercentage = PlayerHealth / MaxPlayerHealth;//creattes percentage
	return HealthPercentage;
}
