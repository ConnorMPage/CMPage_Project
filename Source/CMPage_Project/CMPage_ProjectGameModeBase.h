// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_SetUpQuadTree.h"
#include "C_GridData.h"
#include "C_QuadRooms.h"
#include "CMPage_ProjectGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class CMPAGE_PROJECT_API ACMPage_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void createDungeon();

	UFUNCTION()
		void StartGame();//starts the start timer function
	UFUNCTION()
		void StartGameTimer();//starts the timer
	
	UFUNCTION()
		void TimesUp();//ends the game when out of time
	UFUNCTION()
		void Restart();//restarts the game 
	
	
	UPROPERTY()
		AC_SetUpQuadTree* quadTreeRef;
	UPROPERTY()
		AC_GridData* gridDataRef;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_SetUpQuadTree> quadTreeSubClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_GridData> gridDataSubClass;
	UPROPERTY()
		int EnemiesAlive = 10;//starting amount of enemies
	UPROPERTY(EditAnywhere)
		float GameLength = 900.0f;//15 minute timer
	UPROPERTY(EditAnywhere)
		float EndGameLength = 5.0f;//wait for the game t start
	UPROPERTY()
		int noEnemies = 0;
	//bools 
	UPROPERTY(EditAnywhere)
		bool PlayerWon = false;//if player won
	UPROPERTY(EditAnywhere)
		bool OutOfTime = false;//if out of time
	UPROPERTY(EditAnywhere)
		bool InGame = false;// if in game
	FTimerHandle GameTimer;//game timer

	FTimerHandle EndOfGameTimer;//wait timer
	
	//values for the stat to change
	UPROPERTY(VisibleAnywhere)
		int ShotFired = 1;
	UPROPERTY(VisibleAnywhere)
		int ReloadDone = 2;
	UPROPERTY(VisibleAnywhere)
		int DamageTaken = 4;
	UPROPERTY(VisibleAnywhere)
		int NoChange = 0;
	UPROPERTY(VisibleAnywhere)
		int StatNum = 0;
	UPROPERTY(VisibleAnywhere)
		int AddHealth = 5;
	UPROPERTY(VisibleAnywhere)
		int AddAmmo = 7;
public:	
	UFUNCTION()
		int UpdateStats();//updates the hud stats
	UFUNCTION()
		void GetStatData(int StatToUpdate);
	UFUNCTION()
		void GameOver();//ends the game
	UFUNCTION()
		void EnemyKilled();//if an enemy is killed
	UPROPERTY()
		bool SpawnTheUnits = false;
	UPROPERTY()
		TArray<AC_QuadRooms*> SpawnPoints;
	
}; 
