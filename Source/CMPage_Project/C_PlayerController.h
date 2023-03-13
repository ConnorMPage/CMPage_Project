// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "C_PlayerCharacter.h"
#include "CMPage_ProjectGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CMPAGE_PROJECT_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		ACMPage_ProjectGameModeBase* GameModeRef;//references the gamemode
	UPROPERTY(VisibleAnywhere)
		AC_PlayerCharacter* PlayerRef;//references the player
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CrosshairClass;//creats widget subclass for crosshair
	UPROPERTY()
		UUserWidget* CrosshairUI;//creates the widget object for croshair
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerHudClass;//creats widget subclass for hud
	UPROPERTY()
		UUserWidget* PlayerHudUI;
	UPROPERTY()
		UUserWidget* MiniMapUI;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MiniMapClass;//creats widget subclass for map
	UFUNCTION()
		void ProvideStats(int StatOption);//changes stat value
	UFUNCTION(BlueprintPure)
		int GetMagazineAmount();//changes text in widget
	UFUNCTION(BlueprintPure)
		int GetAmmoAmount();//changes text in widget
	
	UFUNCTION(BlueprintPure)
		float GetHealthAmount();//changes text in widget

	//values for stat to change
	UPROPERTY(VisibleAnywhere)
		int ShotFired = 1;
	UPROPERTY(VisibleAnywhere)
		int ReloadDone = 2;
	
	UPROPERTY(VisibleAnywhere)
		int DamageTaken = 4;
	UPROPERTY(VisibleAnywhere)
		int AddHealth = 5;
	
	UPROPERTY(VisibleAnywhere)
		int AddAmmo = 7;
	
	//stats for hud
	
	UPROPERTY(EditAnywhere)
		int AmountOfBullets = 75;
	UPROPERTY(EditAnyWhere)
		int MaxMagCapacity = 15;
	UPROPERTY(EditAnywhere)
		int AmountOfBulletsInMag = MaxMagCapacity;
	UPROPERTY(EditAnywhere)
		float BonusHealth = 20.0f;
	UPROPERTY(EditAnywhere)
		int BonusBullets = 30;
	UPROPERTY(EditAnywhere)
		float WeaponDamage = 25.0f;
	UPROPERTY(EditAnywhere)
		int EmptyMag = 0;
	UPROPERTY(EditAnywhere)
		int MagDifference;
	UPROPERTY(EditAnywhere)
		float MaxPlayerHealth = 110.0f;
	UPROPERTY(EditAnywhere)
		float PlayerHealth = MaxPlayerHealth;
	UPROPERTY(EditAnywhere)
		float HealthPercentage;
};
