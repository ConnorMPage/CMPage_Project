// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SetUpQuadTree.h"

// Sets default values
AC_SetUpQuadTree::AC_SetUpQuadTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_SetUpQuadTree::BeginPlay()
{
	Super::BeginPlay();
	StartSetup();
}

// Called every frame
void AC_SetUpQuadTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_SetUpQuadTree::StartSetup()
{

}

AC_SimpleBoundary* AC_SetUpQuadTree::NewQuadCell(FVector center, FVector Half, AC_SimpleBoundary* parentObj)
{
	return nullptr;
}

/*std::tuple<int, int, float, float> AC_SetUpQuadTree::sliceRand(AC_SimpleBoundary* index)
{
	return std::tuple<int, int, float, float>();
}*/

std::vector<FVector> AC_SetUpQuadTree::Center(float sliceX, float sliceY, AC_SimpleBoundary* index)
{
	return std::vector<FVector>();
}

std::vector<FVector> AC_SetUpQuadTree::CellSize(float sliceX, float sliceY, AC_SimpleBoundary* index)
{
	return std::vector<FVector>();
}

