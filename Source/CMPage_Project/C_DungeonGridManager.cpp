// Fill out your copyright notice in the Description page of Project Settings.


#include "C_DungeonGridManager.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AC_DungeonGridManager::AC_DungeonGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	procGenRefs = Cast<UC_ProcGenAlgs>(UGameplayStatics::GetObjectClass(GetWorld()));
}

// Called when the game starts or when spawned
void AC_DungeonGridManager::BeginPlay()
{
	Super::BeginPlay();
	DungeonGrid.SetNumZeroed(DungeonSize);
	for (int i = 0; i < DungeonGrid.Num(); i++)
	{
		DungeonGrid[i].SetNumZeroed(DungeonSize);
	}

	constructGrid();
}

// Called every frame
void AC_DungeonGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_DungeonGridManager::constructGrid()
{
	std::vector<TArray<TArray<AC_DungeonTile*>>> test = procGenRefs->binarySpacePartitioning(DungeonGrid, 5, 5);

	for (int x = 0; x < DungeonSize; x++)
	
	{
		for (int y = 0; y < DungeonSize; y++)
		{
			const float xPos = x * tileOffset;
			const float yPos = y * tileOffset;
			const float zPos = -10.0f;
			AC_DungeonTile* newTile = GetWorld()->SpawnActor<AC_DungeonTile>(DungeonTileClass, FVector(xPos, yPos, zPos), FRotator::ZeroRotator);
			newTile->TileIndex = FIntPoint(x, y);
			DungeonGrid[x][y] = newTile;
		}
	}

}

