// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GridData.h"

// Sets default values
AC_GridData::AC_GridData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Mesh initialisation
	pillarWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pillar Wall Mesh"));
	capFIllerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap Filler Mesh"));
	cornerFillerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Corner Filler Mesh"));
	groundFillerFullMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ground Filler Full Mesh"));
	capWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap Wall Mesh"));
	insideCornerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Inside Corner Mesh"));
	outsideCornerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outside Corner Mesh"));
	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT(" Wall Mesh"));
	floorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Mesh"));
}

// Called when the game starts or when spawned
void AC_GridData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_GridData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_GridData::passInVariables(FVector mapDim, int tSize, int rwborder, int corW)
{
	mapDimensions = mapDim;
	tileSize = tSize;
	roomWallBorder = rwborder;
	corridorWidth = corW;
}

void AC_GridData::createGrid(AC_SetUpQuadTree* quadTreeRef)
{
	
}

void AC_GridData::digRooms(AC_QuadRooms* quadRoomIn)
{
}

bool AC_GridData::digCorridor(FVector room1Centre, FVector room2Centre)
{
	return false;
}

bool AC_GridData::b_HasChildrenWithRooms(AC_QuadRooms* quadRoomIn)
{
	return false;
}

bool AC_GridData::b_HasChildren(AC_QuadRooms* quadRoomIn)
{
	return false;
}

AC_QuadRooms* AC_GridData::closestRoom(AC_QuadRooms* quadRoomIn)
{
	return nullptr;
}

void AC_GridData::edgeClearing()
{
}

void AC_GridData::generateWalls()
{
}

void AC_GridData::testNSEW(int X, int Y, TArray<int> inTestGrid, int& TileOut1, int& TileOut2, int& TileOut3, int& TileOut4, int& TileOut5, int& TileOut6, int& TileOut7, int& TileOut8)
{
}

void AC_GridData::makeWall(FTransform transform)
{
}

void AC_GridData::makeDoubleWall(FTransform transform)
{
}

void AC_GridData::makeCorner(FTransform transform)
{
}

void AC_GridData::makeCap(FTransform transform)
{
}

void AC_GridData::safeArrayGetCheck(int X, int Y)
{
}

