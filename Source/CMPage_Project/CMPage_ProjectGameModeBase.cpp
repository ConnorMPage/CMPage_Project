// Copyright Epic Games, Inc. All Rights Reserved.


#include "CMPage_ProjectGameModeBase.h"


void ACMPage_ProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	createDungeon();
	spawnUnits();
	StartGame();
}
void ACMPage_ProjectGameModeBase::createDungeon()
{
	gridDataRef = GetWorld()->SpawnActor<AC_GridData>(gridDataSubClass, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
	quadTreeRef = GetWorld()->SpawnActor<AC_SetUpQuadTree > (quadTreeSubClass, FVector(0.0f,0.0f,0.0f), FRotator::ZeroRotator);
	quadTreeRef->StartSetup();
	gridDataRef->passInVariables(quadTreeRef->mapDimensions, quadTreeRef->tileSize, quadTreeRef->roomWallBorder, 1, quadTreeRef->sliceRoomMinSize);
	gridDataRef->createGrid(quadTreeRef);
}



void ACMPage_ProjectGameModeBase::StartGame()
{
	StartGameTimer();//starts game timer
	InGame = true;
}

void ACMPage_ProjectGameModeBase::StartGameTimer()
{
	GetWorld()->GetTimerManager().SetTimer(GameTimer, this, &ACMPage_ProjectGameModeBase::TimesUp, GameLength, false);//starts timer for 15 minutes
}

void ACMPage_ProjectGameModeBase::EnemyKilled()
{
	EnemiesAlive--;
	if (EnemiesAlive == noEnemies)
	{
		PlayerWon = true;//player has won
		GameOver();//starts game over function
		InGame = false;//sets in game to false
	}
}

void ACMPage_ProjectGameModeBase::TimesUp()
{
	OutOfTime = true;//sets outof time to true
	GameOver();//starts game over fuction
	InGame = false;//ends game
}

void ACMPage_ProjectGameModeBase::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMap");
}

void ACMPage_ProjectGameModeBase::GameOver()
{
	GetWorld()->GetTimerManager().SetTimer(EndOfGameTimer, this, &ACMPage_ProjectGameModeBase::Restart, EndGameLength, false);//sets five second timer before restart
	//sends three output mssages depending on outcome
	if (PlayerWon == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("complete"));

	}
	else if (PlayerWon == false && OutOfTime == true)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Out of Time"));
		InGame = false;
	}
	else
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
		InGame = false;
	}
}

int ACMPage_ProjectGameModeBase::UpdateStats()
{
	if (StatNum == ShotFired)
	{
		return ShotFired;
	}
	else if (StatNum == ReloadDone)
	{
		return ReloadDone;
	}
	else if (StatNum == DamageTaken)
	{
		return DamageTaken;
	}
	else if (StatNum == AddHealth)
	{
		return AddHealth;
	}
	else if (StatNum == AddAmmo)
	{
		return AddAmmo;
	}
	else
	{
		return NoChange;
	}
	StatNum = NoChange;
}

void ACMPage_ProjectGameModeBase::GetStatData(int StatToUpdate)
{
	StatNum = StatToUpdate;
}
