// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SetUpQuadTree.h"
#include "Math/UnrealMathUtility.h"
// Sets default values
AC_SetUpQuadTree::AC_SetUpQuadTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//gameModeRef = Cast<ACMPage_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));// casts in the gameref so that the class can execute gamemode functions
}

// Called when the game starts or when spawned
void AC_SetUpQuadTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_SetUpQuadTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AC_SetUpQuadTree::StartSetup()
{
	//set map size
	
	mapDimensions = mapDimensions * FVector(100.0f, 100.0f, 1.0f);
	AC_QuadRooms* initialQuad = NewQuadCell(GetActorLocation() + (mapDimensions/2), (mapDimensions/2));
	//initialQuad->BoundingBox->SetBoxExtent(mapDimensions);
	//limit the max number of rooms
	int mapCalc = (roomWallBorder*2)+ sliceRoomMinSize;
	FVector diviedDim = mapDimensions / 100.0f;
	int maxRooms = ceilf(((diviedDim.X / mapCalc) * (diviedDim.Y / mapCalc)) * 0.75f);

	//main loop

	for (int mainInd = 0; mainInd < maxRooms; mainInd++)
	{
		sliceBreak = true;
		if (mainInd < QuadRoomArray.Num() )//if ind is smaller than quads array then
		{
			
			SliceTry = 0;
			currentQuadBounds = QuadRoomArray[mainInd];
			while (sliceBreak && SliceTry <= slice_MaxTries)//while within slice tries
			{
				for (int index = 0; index < slice_MaxTries; index++)
				{
					float randfloat = FMath::RandRange(1, 100);//random float between 1 and 100
					SliceTry = index;
					if (randfloat <= chanceToDropQuad && mainInd >= 4)
					{
						break;
					}
					else
					{
						generateQuads(currentQuadBounds, mainInd);//create the 4 quads from current boundary
						if (slices)break;
					}
				}
				sliceBreak = false;
			}
		}
		else
		{
			break;
		}
	}
	//after main loop
	for (int i = 0; i < QuadRoomArray.Num(); i++)
	{
		currentQuadBounds = QuadRoomArray[i];
		if (currentQuadBounds->hasChild)
		{
			justTrunkNodes_QuadRoom.Add(currentQuadBounds);//add to junk
			currentQuadBounds->SetActorHiddenInGame(false);//makes quad visible
		}
		else
		{
			justLeafNodes_QuadRoom.Add(currentQuadBounds);//add to leaf nodes used in corners later on
		}
	}
}


void AC_SetUpQuadTree::generateQuads(AC_QuadRooms*& quadRoomIn,int mainInt )
{
	slices = false;


	int horSlice;
	int verSlice;
	float fHorSlice;
	float fVerSlice;
	sliceRand(quadRoomIn, horSlice, verSlice, fHorSlice, fVerSlice);//gets rasndom values within bounds 

	float left;
	float right;
	float top;
	float bottom;
	quadRoomIn->BoundaryBounds(left, right, top, bottom);//gets current quads bounds
	float ifcriteria = (sliceRoomMinSize + roomWallBorder) * tileSize;
	
	if (abs(fHorSlice - left) >= ifcriteria) {
		if (abs(right - fHorSlice) >= ifcriteria) {
			if (abs(top - fVerSlice) >= ifcriteria) {
				if (abs(fVerSlice - bottom) >= ifcriteria) {//if within size critera
					sliceBreak = true;
					slices = true;

					TArray<FVector> sizeArray = CellSize(fHorSlice, fVerSlice, quadRoomIn);//gets the size
					TArray<FVector> centreArray = Center(fHorSlice, fVerSlice, sizeArray);//gets the centre
					for (int i = 0; i < 3; i++)//loops through new quads
					{
						
						float halfX = quadRoomIn->half_x;
						float halfY = quadRoomIn->half_y;
						AC_QuadRooms* tempQuad;
						
						if (mainInt == 0) {
							tempQuad = NewQuadCell2(FVector(centreArray[i].X - abs(halfX), centreArray[i].Y - abs(halfY), centreArray[i].Z), sizeArray[i], quadRoomIn);//creates quad
							tempQuad->K2_AttachRootComponentToActor(quadRoomIn);
							//attaches new quad to current quad
						}
						else {
						
							sizeArray = CellSize(fHorSlice, fVerSlice, quadRoomIn);
							centreArray = Center(fHorSlice, fVerSlice, sizeArray);
							tempQuad = NewQuadCell2(FVector(centreArray[i].X - quadRoomIn->posDif.X, centreArray[i].Y - quadRoomIn->posDif.Y, centreArray[i].Z), sizeArray[i], quadRoomIn);//creates quad
							
							
							tempQuad->K2_AttachRootComponentToActor(quadRoomIn);//attaches new quad to current quad
							
						}
						tempQuad->absCentre_X = tempQuad->GetActorLocation().X;//gets absolute location for generating rooms in griddata
						tempQuad->absCentre_Y = tempQuad->GetActorLocation().Y;
						tempQuad->posDif = tempQuad->GetActorLocation() - quadRoomIn->GetActorLocation();
						quadRoomIn->childBoundaries.Add(quadRoomIn);
					}
					quadRoomIn->hasChild = true;//sets children to true
				}
			}
		}
	}
		
		
	
	

}


AC_QuadRooms* AC_SetUpQuadTree::NewQuadCell(FVector center, FVector Half)
{//used only for the initial quad
	AC_QuadRooms* boxComp;
	
	
	boxComp = GetWorld()->SpawnActor<AC_QuadRooms>(quadRoomsSubClass, center, FRotator::ZeroRotator);//creates actor
	boxComp->initBounds(center.X, center.Y, Half.X, Half.Y);

	QuadRoomArray.Add(boxComp);
	return boxComp;
}

AC_QuadRooms* AC_SetUpQuadTree::NewQuadCell2(FVector center, FVector Half, AC_QuadRooms* parentObj)
{//used for all children quads
	AC_QuadRooms* boxComp;


	boxComp = GetWorld()->SpawnActor<AC_QuadRooms>(quadRoomsSubClass, center, FRotator::ZeroRotator);//creates actor
	boxComp->initBounds(center.X, center.Y, Half.X, Half.Y);
	boxComp->SetOwner(this);
	//boxComp->SetActorRelativeLocation(FVector(center.X - Half.X, center.Y - Half.Y, center.Z));
	QuadRoomArray.Add(boxComp);
	return boxComp;
}
	

void AC_SetUpQuadTree::sliceRand(AC_QuadRooms* index, int& horSlice, int& verSlice, float& fHorSlice, float& fVerSlice)
{//creates random sizes for new boundaries
	bool possibleVal = false;
	float left = 0;
	float right = 0;
	float top = 0;
	float bottom = 0;
	index->BoundaryBounds(left, right, top, bottom);//gets bounds of current quad
	
	int iLeft = floorf(left) / tileSize;
	int iRight = floorf(right) / tileSize;
	int iTop = floorf(top) / tileSize;
	int iBottom = floorf(bottom) / tileSize;

	horSlice = FMath::RandRange(iLeft,iRight)*tileSize;//gets rand

	fHorSlice = horSlice;

	verSlice = FMath::RandRange(iBottom,iTop )* tileSize;//gets rand
	

	fVerSlice = verSlice;
	
}

TArray<FVector> AC_SetUpQuadTree::CellSize(float sliceX, float sliceY, AC_QuadRooms* index)
{
	float left;
	float right;
	float top;
	float bottom;

	index->BoundaryBounds(left, right, top, bottom);//gets boundaries 
	TArray<FVector> subArray;

	subArray.Add(FVector(sliceX - left, top - sliceY, 1.0f) / 2);
	subArray.Add(FVector(right - sliceX, top - sliceY, 1.0f) / 2);
	subArray.Add(FVector(sliceX - left, sliceY - bottom, 1.0f) / 2);
	subArray.Add(FVector(right - sliceX,sliceY-bottom, 1.0f) / 2);
	return subArray;
}

TArray<FVector> AC_SetUpQuadTree::Center(float sliceX, float sliceY, TArray<FVector> parentArray)
{//calculates centre of each quad
	TArray<FVector> subArray;
	int i = 0;
	parentArray[i] = parentArray[i] / 1.0f;
	subArray.Add(FVector(sliceX - parentArray[i].X, sliceY + parentArray[i].Y, parentArray[i].Z));

	i++;
	parentArray[i] = parentArray[i] / 1.0f;
	subArray.Add(FVector(sliceX + parentArray[i].X, sliceY + parentArray[i].Y, parentArray[i].Z));

	i++;
	parentArray[i] = parentArray[i] / 1.0f;
	subArray.Add(FVector(sliceX - parentArray[i].X, sliceY - parentArray[i].Y, parentArray[i].Z));

	i++;
	parentArray[i] = parentArray[i] / 1.0f;
	subArray.Add(FVector(sliceX + parentArray[i].X, sliceY - parentArray[i].Y, parentArray[i].Z));

	return subArray;
}




