// Copyright Epic Games, Inc. All Rights Reserved.


#include "CMPage_ProjectGameModeBase.h"


void ACMPage_ProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	checkStart();
	createDungeon();
}


void ACMPage_ProjectGameModeBase::checkStart()
{
}

void ACMPage_ProjectGameModeBase::createDungeon()
{
	gridDataRef = GetWorld()->SpawnActor<AC_GridData>(gridDataSubClass, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
	quadTreeRef = GetWorld()->SpawnActor<AC_SetUpQuadTree > (quadTreeSubClass, FVector(0.0f,0.0f,0.0f), FRotator::ZeroRotator);
	quadTreeRef->StartSetup();
	gridDataRef->passInVariables(quadTreeRef->mapDimensions, quadTreeRef->tileSize, quadTreeRef->roomWallBorder, 1, quadTreeRef->sliceRoomMinSize);
	gridDataRef->createGrid(quadTreeRef);
}

void ACMPage_ProjectGameModeBase::spawnUnits()
{
}
