// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GridData.h"

// Sets default values
AC_GridData::AC_GridData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Mesh initialisation
	//pillarWallMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Pillar Wall Mesh"));
	//capFIllerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Cap Filler Mesh"));
	//cornerFillerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Corner Filler Mesh"));
	//groundFillerFullMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Ground Filler Full Mesh"));
	//capWallMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Cap Wall Mesh"));
	//insideCornerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Inside Corner Mesh"));
	//outsideCornerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Outside Corner Mesh"));
	//wallMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT(" Wall Mesh"));
	//floorMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Floor Mesh"));
	
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
	quadRoomIn->BoundaryBounds(quadRoomBound_Left, quadRoomBound_Right, quadRoomBound_Top, quadRoomBound_Bottom);
	if (quadRoomBound_Right < quadRoomBound_Left)
	{
		tmp = quadRoomBound_Right;
		quadRoomBound_Right = quadRoomBound_Left;
		quadRoomBound_Left = tmp;
	}
	if (quadRoomBound_Top < quadRoomBound_Bottom)
	{
		tmp = 0.0f;
		quadRoomBound_Top = quadRoomBound_Bottom;
		quadRoomBound_Bottom = tmp;
	}
	int indexOut;
	bool value;
	for (int y = floor(quadRoomBound_Bottom / tileSize); y > (floor(quadRoomBound_Top / tileSize) - 1); y++)
	{
		for (int x = floor(quadRoomBound_Left / tileSize); x > (floor(quadRoomBound_Right / tileSize) - 1); x++)
		{
			getArrayValueXYinbool(x, y, tiles, indexOut,value);
			tiles[indexOut] = true;
			tileType[indexOut] = 1;
			 
		}
	}
}

bool AC_GridData::digCorridor(FVector room1Centre, FVector room2Centre)
{
	return false;
}

bool AC_GridData::b_HasChildrenWithRooms(AC_QuadRooms* quadRoomIn)
{

	bool hasChildren = false;


	if (!b_HasChildren(quadRoomIn)) {
		hasChildren = false;
	}
	else
	{
		if (quadRoomIn->childBoundaries.Num() > 0)hasChildren = true;
		else hasChildren = false;
	}
	
	return hasChildren;
}

bool AC_GridData::b_HasChildren(AC_QuadRooms* quadRoomIn)
{
	bool result = false;
	if (quadRoomIn->childBoundaries.Num() > 0)result = true;
	else result = false;
	return result;
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
	wallMesh->AddInstance(transform);
	if (!fillerCreated[tileIndex])
	{
		groundFillerFullMesh->AddInstance(transform);
		fillerCreated[tileIndex] = true;
	}
}

void AC_GridData::makeDoubleWall(FTransform transform)
{
}

void AC_GridData::makeCorner(FTransform transform)
{
	outsideCornerMesh->AddInstance(transform);
	if (!fillerCreated[tileIndex])
	{
		cornerFillerMesh->AddInstance(transform);
		fillerCreated[tileIndex] = true;
	}
}

void AC_GridData::makeCap(FTransform transform)
{
	capWallMesh->AddInstance(transform);
	if (!fillerCreated[tileIndex])
	{
		capFIllerMesh->AddInstance(transform);
		fillerCreated[tileIndex] = true;
	}
} 

void AC_GridData::safeArrayGetCheck(int X, int Y)
{
}

void AC_GridData::getArrayValueXYinbool(int X, int Y, TArray<bool> arrayIn, int& indexOut, bool& value)
{
	indexOut = (floor(mapDimensions.Y)*Y) + X;
	value = arrayIn[indexOut];
}
void AC_GridData::getArrayValueXYin(int X, int Y, TArray<int> arrayIn, int& indexOut,int& value)
{
	indexOut = (floor(mapDimensions.Y) * Y) + X;
	value = arrayIn[indexOut];
}

void AC_GridData::getXYBaseOnIndex(int indexin, int XMax, int YMax, int& X, int& Y)
{
	X = indexin % YMax;
	Y = indexin / YMax;
}

void AC_GridData::GenerateRoomTiles(AC_QuadRooms* quadRoomIn)
{
}

void AC_GridData::generateCorridorTiles(AC_QuadRooms* quadRoomIn, TArray<AC_QuadRooms*> LeafQuadRoom)
{
}

bool AC_GridData::floorOrCorridor(int in)
{
	bool if1;
	bool if2;
	
	if (in == 1)if1 = true;
	else if1 = false;
	
	if (in == 2)if2 = true;
	else if2 = false;
	
	bool result = if1 || if2;
	
	return result;
}

bool AC_GridData::emptyorOutside(int in)
{
	bool if1;
	bool if2;

	if (in == 0)if1 = true;
	else if1 = false;

	if (in == 666)if2 = true;
	else if2 = false;

	bool result = if1 || if2;

	return result;
}

bool AC_GridData::wallOrEmptyOrOutside(int in)
{
	bool if1;
	bool if2;
	bool if3;
	if (in == 0)if1 = true;
	else if1 = false;

	if (in == 666)if2 = true;
	else if2 = false;

	if (in == 99)if3 = true;
	else if3 = false;

	bool result = if1 || if2 || if3;

	return result;
}

FTransform AC_GridData::makeTileTransform()
{
	FRotator rotation = FRotator(0.0f, (cornerRot + 3) * 90.0f,0.0f);

	int x;
	int y;
	getXYBaseOnIndex(tileIndex, xMax, yMax, x, y);
	float fX = x;
	float fY = y;
	FVector translation = FVector(fX, fY, 0.0f);
	return FTransform(rotation,translation,FVector(1.0f,1.0f,1.0f));
}

bool AC_GridData::anyTile(int in)
{
	bool if1;
	bool if2;
	bool if3;
	bool if4;
	bool if5;
	if (in == 0)if1 = true;
	else if1 = false;

	if (in == 666)if2 = true;
	else if2 = false;

	if (in == 99)if3 = true;
	else if3 = false;

	if (in == 99)if4 = true;
	else if4 = false;

	if (in == 99)if5 = true;
	else if5 = false;

	bool result = if1 || if2 || if3 || if4 || if5;

	return result;
}

