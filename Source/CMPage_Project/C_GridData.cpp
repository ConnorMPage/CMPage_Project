// Fill out your copyright notice in the Description page of Project Settings.
#include "C_GridData.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AC_GridData::AC_GridData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Mesh initialisation
	
	capFIllerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Cap Filler Mesh"));
	cornerFillerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Corner Filler Mesh"));
	groundFillerFullMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Ground Filler Full Mesh"));
	capWallMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Cap Wall Mesh"));
	insideCornerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Inside Corner Mesh"));
	outsideCornerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Outside Corner Mesh"));
	wallMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT(" Wall Mesh"));
	floorMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Floor Mesh"));
	pillarWallMesh =  CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("pillar Mesh"));

	capFIllerMesh->SetCullDistances(5000, 6000);
	cornerFillerMesh->SetCullDistances(5000, 6000);
	groundFillerFullMesh->SetCullDistances(5000, 6000);
	capWallMesh->SetCullDistances(5000, 6000);
	insideCornerMesh->SetCullDistances(5000, 6000);
	outsideCornerMesh->SetCullDistances(5000, 6000);
	wallMesh->SetCullDistances(5000, 6000);
	floorMesh->SetCullDistances(5000, 6000);
	pillarWallMesh->SetCullDistances(5000, 6000);
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

void AC_GridData::passInVariables(FVector mapDim, int tSize, int rwborder, int corW, int roomMin)
{
	
	tileSize = tSize;
	mapDimensions = mapDim / tileSize;
	roomWallBorder = rwborder;
	corridorWidth = corW;
	roomMinSize = roomMin;
	
	int startSize = floor(mapDimensions.X * mapDimensions.Y);
	tiles.SetNum(startSize);
	tileType.SetNum(startSize);
	cornerRotationArray.SetNum(startSize);
	fillerCreated.SetNum(startSize);
	tileCollisionActors.SetNum(startSize);
	for (int i = 0; i < tiles.Num(); i++)
	{
		tiles[i] = false;
		tileType[i] = 0;
		cornerRotationArray[i] = 1;
		fillerCreated[i] = false;
	}
}

void AC_GridData::createGrid(AC_SetUpQuadTree* quadTreeRef)
{
	quadTree = quadTreeRef;
	for (int i = 0; i < quadTree->QuadRoomArray.Num(); i++)
	{
		GenerateRoomTiles(quadTree->QuadRoomArray[i]);
	}
	for (int i = 0; i < quadTree->QuadRoomArray.Num(); i++)
	{
		generateCorridorTiles(quadTree->QuadRoomArray[i], quadTree->justLeafNodes_QuadRoom);
	}
	lastIndex = floor((mapDimensions.X * mapDimensions.Y) - 1.0f);
	xMax = floor(mapDimensions.X);
	yMax = floor(mapDimensions.Y);
	
	edgeClearing();
	generateWalls();
	


	for (int index = 0; index < lastIndex; index++)
	{
		tileIndex = index;
		int xAxis, yAxis;
		getXYBaseOnIndex(tileIndex, xMax, yMax, xAxis, yAxis);

		FVector transVector=( FVector(xAxis,yAxis,0.0f)+ FVector(0.0f,0.0f, 0.0f))* tileSize;
		FRotator transRot = FRotator(0.0f, (cornerRotationArray[tileIndex] + 3) * 90.0f, 0.0f);
		FVector visVector = transVector + FVector((tileSize / 2), (tileSize / 2), 0.0f);

		visualTransform = FTransform(transRot, transVector, FVector(1.0f, 1.0f, 1.0f));
		collisionTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), transVector, FVector(1.0f, 1.0f, 1.0f));

		if (tileType[tileIndex] == 99)
		{
			FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f),collisionTransform.GetScale3D());
			AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);
		}
		else
		{
			if (tileType[tileIndex] == 100)
			{
				FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
				AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);
			}
			else
			{
				if (tileType[tileIndex] == 101)
				{
					FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
					AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);
				}
				else
				{
					if (tileType[tileIndex] == 102)
					{
						FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
						AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);
					}
					else
					{
						if (tileType[tileIndex] == 103)
						{
							FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
							AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);
						}
						else
						{
							if (tileType[tileIndex] != 0)
							{
								floorMesh->AddInstance(visualTransform);
								tiles[tileIndex] = true;
								// finish off
							}
							else
							{
								groundFillerFullMesh->AddInstance(visualTransform);
								FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
								AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < tileType.Num(); i++)
	{
		if (tileType[i] == 100 || tileType[i] == 101 || tileType[i] == 102 || tileType[i] == 103 || tileType[i] == 99 || tileType[i] == 0)
		{
			tileType[i] = -1;
		}
	}
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
	for (int y = floor(quadRoomBound_Bottom / tileSize); y < (floor(quadRoomBound_Top / tileSize) - 1); y++)
	{
		for (int x = floor(quadRoomBound_Left / tileSize); x < (floor(quadRoomBound_Right / tileSize) - 1); x++)
		{
			getArrayValueXYinbool(x, y, tiles, indexOut,value);
			tiles[indexOut] = true;
			tileType[indexOut] = 1;
			 
		}
	}
}

bool AC_GridData::digCorridor(FVector room1Centre, FVector room2Centre)
{
	col1 = floor(room1Centre.X-0.5f);
	row1= floor(room1Centre.Y - 0.5f);
	col2 = floor(room2Centre.X - 0.5f);
	row2 = floor(room2Centre.Y - 0.5f);

	int indexOut;
	bool value;
	if (row1 <= row2)
	{
		for (int x = col1; x <(col1+corridorWidth);x++)
		{
			for (int y = row1; y < (row2 +0) ;y++)
			{
				getArrayValueXYinbool(x, y, tiles, indexOut, value);
				if (tileType[indexOut] != 1)
				{
					tiles[indexOut] = true;
					tileType[indexOut] = 2;
				}
			}
		}
	}
	else
	{
		for (int x = col1; x < (col1 + corridorWidth); x++)
		{
			for (int y = row2; y < (row1 + 0); y++)
			{
				getArrayValueXYinbool(x, y, tiles, indexOut, value);
				if (tileType[indexOut] != 1)
				{
					tiles[indexOut] = true;
					tileType[indexOut] = 2;
				}
			}
		}
	}
	
	if (col1 <= col2)
	{
		for (int y = row2; y < (row2 + corridorWidth); y++)
		{
			for (int x = col1; x < col2; x++)
			{
				getArrayValueXYinbool(x, y, tiles, indexOut, value);
				if (tileType[indexOut] != 1)
				{
					tiles[indexOut] = true;
					tileType[indexOut] = 2;
				}
			} 
		}
	}
	else
	{
		for (int y = row2; y < (row2 + corridorWidth); y++)
		{
			for (int x = col2; x < col1; x++)
			{
				getArrayValueXYinbool(x, y, tiles, indexOut, value);
				if (tileType[indexOut] != 1)
				{
					tiles[indexOut] = true;
					tileType[indexOut] = 2;
				} 
			}
		}
	}

	return true;
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
	int x = xMax - 1;
	int indexOut;
	bool value;
	for (int i = 0 ; i > x; i++)
	{
		getArrayValueXYinbool(0, i, tiles, indexOut, value);
		tiles[indexOut] = false;
		tileType[indexOut] = 0;
	}
	for (int i = 0; i > x; i++)
	{
		getArrayValueXYinbool(x, i, tiles, indexOut, value);
		tiles[indexOut] = false;
		tileType[indexOut] = 0;
	}
	int y = yMax - 1;
	for (int i = 0; i > y; i++)
	{
		getArrayValueXYinbool(i, y, tiles, indexOut, value);
		tiles[indexOut] = false;
		tileType[indexOut] = 0;
	}
	for (int i = 0; i > y; i++)
	{
		getArrayValueXYinbool(i, 0, tiles, indexOut, value);
		tiles[indexOut] = false;
		tileType[indexOut] = 0;
	}
}

void AC_GridData::generateWalls()
{
	int tileO1;
	int tileO2;
	int tileO3;
	int tileO4;
	int tileO5;
	int tileO6;
	int tileO7;
	int tileO8;

	cornerRotationArray.Empty();
	cornerRotationArray.SetNum(tileType.Num() - 1);
	for (int arrayIndex = 0; arrayIndex < tileType.Num(); arrayIndex++)
	{
		getXYBaseOnIndex(arrayIndex, floor(mapDimensions.X), floor(mapDimensions.Y), localXIndex, localYIndex);
		int value;
		int indexOut;
		getArrayValueXYin(localXIndex, localYIndex, tileType, indexOut, value);
	
		if (value == 0)
		{
			testNSEW(localXIndex, localYIndex, tileType, tileO1, tileO2, tileO3, tileO4, tileO5, tileO6, tileO7, tileO8);
			if (floorOrCorridor(tileO1) || floorOrCorridor(tileO2) || floorOrCorridor(tileO3) || floorOrCorridor(tileO4) ||
				floorOrCorridor(tileO5) || floorOrCorridor(tileO6) || floorOrCorridor(tileO7) || floorOrCorridor(tileO8))
			{
				tileType[arrayIndex] = 99;
			}
		}
	}
	testArray.Empty();
	testArray = tileType;
	for (int arrayIndex = 0; arrayIndex < tileType.Num(); arrayIndex++)
	{
		tileIndex = arrayIndex;
		getXYBaseOnIndex(arrayIndex, floor(mapDimensions.X), floor(mapDimensions.Y), localXIndex, localYIndex);
		int value;
		int indexOut;
		getArrayValueXYin(localXIndex, localYIndex, testArray, indexOut, value);
		if (value == 99)
		{
			testNSEW(localXIndex, localYIndex, testArray, test_n1_0, test_n1_1, test_0_1, test_1_1, test_1_0, test_1_n1, test_0_n1, test_n1_n1);
			if (floorOrCorridor(test_n1_0)&&test_0_1 == 99 && test_0_n1 == 99 && wallOrEmptyOrOutside(test_1_0))
			{
				cornerRot = 3;
				getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
				tileType[indexOut] = 99;
				cornerRotationArray[indexOut] = cornerRot;
				makeWall(makeTileTransform());
			}
			else
			{
				if (floorOrCorridor(test_0_1) && test_n1_0 == 99 && test_1_0 == 99 &&wallOrEmptyOrOutside(test_0_n1))
				{
					cornerRot = 2;
					getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
					tileType[indexOut] = 99;
					cornerRotationArray[indexOut] = cornerRot;
					makeWall(makeTileTransform());
				}
				else
				{
					if (floorOrCorridor(test_1_0) && test_0_1 == 99 && test_0_n1 == 99 && wallOrEmptyOrOutside(test_n1_0))
					{
						cornerRot = 1;
						getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
						tileType[indexOut] = 99;
						cornerRotationArray[indexOut] = cornerRot;
						makeWall(makeTileTransform());
					}
					else
					{
						if (floorOrCorridor(test_0_n1) && test_1_0 == 99 && test_n1_0 == 99 && wallOrEmptyOrOutside(test_0_1))
						{
							cornerRot = 0;
							getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
							tileType[indexOut] = 99;
							cornerRotationArray[indexOut] = cornerRot;
							makeWall(makeTileTransform());
						}
						else
						{
							if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_1_0) && test_0_n1 == 99 && test_0_1 == 99)
							{
								cornerRot = 3;
								getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
								tileType[indexOut] = 102;
								cornerRotationArray[indexOut] = cornerRot;
								makeDoubleWall(makeTileTransform());
							}
							else
							{
								if (floorOrCorridor(test_0_1) && floorOrCorridor(test_0_n1) && test_n1_0 == 99 && test_1_0 == 99)
								{
									cornerRot = 2;
									getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
									tileType[indexOut] = 102;
									cornerRotationArray[indexOut] = cornerRot;
									makeDoubleWall(makeTileTransform());
								}
								else
								{
									if (floorOrCorridor(test_1_0) && floorOrCorridor(test_n1_0) && test_0_1 == 99 && test_0_n1 == 99)
									{
										cornerRot = 1;
										getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
										tileType[indexOut] = 102;
										cornerRotationArray[indexOut] = cornerRot;
										makeDoubleWall(makeTileTransform());
									}
									else
									{
										if (floorOrCorridor(test_0_n1) && floorOrCorridor(test_0_1) && test_n1_0 == 99 && test_1_0 == 99)
										{
											cornerRot = 0;
											getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
											tileType[indexOut] = 102;
											cornerRotationArray[indexOut] = cornerRot;
											makeDoubleWall(makeTileTransform());
										}
										else
										{
											if (test_n1_0 == 99 && test_0_1 == 99 && anyTile(test_n1_1) && floorOrCorridor(test_1_n1) && floorOrCorridor(test_1_0) && floorOrCorridor(test_0_n1))
											{
												cornerRot = 3;
												getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
												tileType[indexOut] = 100;
												cornerRotationArray[indexOut] = cornerRot;
												makeCorner(makeTileTransform());
											}
											else
											{
												if (test_0_1 == 99 && test_1_0 == 99 && anyTile(test_1_1) && floorOrCorridor(test_n1_n1) && floorOrCorridor(test_0_n1) && floorOrCorridor(test_n1_0))
												{
													cornerRot = 2;
													getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
													tileType[indexOut] = 100;
													cornerRotationArray[indexOut] = cornerRot;
													makeCorner(makeTileTransform());
												}
												else
												{
													if (test_1_0 == 99 && test_0_n1 == 99 && anyTile(test_1_n1) && floorOrCorridor(test_n1_1) && floorOrCorridor(test_n1_0) && floorOrCorridor(test_0_1))
													{
														cornerRot = 1;
														getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
														tileType[indexOut] = 100;
														cornerRotationArray[indexOut] = cornerRot;
														makeCorner(makeTileTransform());
													}
													else
													{
														if (test_0_n1 == 99 && test_n1_0 == 99 && anyTile(test_n1_n1) && floorOrCorridor(test_1_1) && floorOrCorridor(test_0_1) && floorOrCorridor(test_1_0))
														{
															cornerRot = 0;
															getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
															tileType[indexOut] = 100;
															cornerRotationArray[indexOut] = cornerRot;
															makeCorner(makeTileTransform());
														}
														else
														{
															if (floorOrCorridor(test_0_1 )&&floorOrCorridor(test_1_0)&& floorOrCorridor(test_0_n1)&&test_n1_0==99)
															{
																cornerRot = 3;
																getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																tileType[indexOut] = 103;
																cornerRotationArray[indexOut] = cornerRot;
																makeCap(makeTileTransform());
															}
															else
															{
																if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_1_0) && floorOrCorridor(test_0_n1) && test_0_1==99)
																{
																	cornerRot = 2;
																	getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																	tileType[indexOut] = 103;
																	cornerRotationArray[indexOut] = cornerRot;
																	makeCap(makeTileTransform());
																}
																else
																{
																	if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_0_1) && floorOrCorridor(test_0_n1) && test_1_0 ==99)
																	{
																		cornerRot = 1;
																		getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																		tileType[indexOut] = 103;
																		cornerRotationArray[indexOut] = cornerRot;
																		makeCap(makeTileTransform());
																	}
																	else
																	{
																		if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_0_1) && floorOrCorridor(test_1_0) && test_0_n1 == 99)
																		{
																			cornerRot = 0;
																			getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																			tileType[indexOut] = 103;
																			cornerRotationArray[indexOut] = cornerRot;
																			makeCap(makeTileTransform());
																		}
																		else
																		{
																			if (floorOrCorridor(test_n1_0)&& floorOrCorridor(test_0_1)&& floorOrCorridor(test_1_0)&& floorOrCorridor(test_0_n1))
																			{
																				cornerRot = 1;
																				pillarWallMesh->AddInstance(makeTileTransform());
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			
		}
	}
	for (int index = 0; index < tileType.Num(); index++)
	{
		tileIndex = index;
		alreadyMade = false;
		getXYBaseOnIndex(index, floor(mapDimensions.X), floor(mapDimensions.Y), localXIndex, localYIndex);
		int value;
		int outInd;
		getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
		if (value == 99)
		{
			testNSEW(localXIndex, localYIndex, testArray, test_n1_0, test_n1_1, test_0_1, test_1_1, test_1_0, test_1_n1, test_0_n1, test_n1_n1);

			FRotator newRot = FRotator(0.0f, ((cornerRot + 3) * 90.0f), 0.0f);
			FVector newPos = FVector(0.0f, 0.0f, 0.0f);
			int xAxis,yAxis;
			getXYBaseOnIndex(tileIndex, xMax, yMax,xAxis,yAxis);
			newPos.X = newPos.X + xAxis;
			newPos.Y = newPos.Y + yAxis;
			visualTransform = FTransform(newRot, newPos, FVector(1.0f, 1.0f, 1.0f));

			if (test_n1_0 == 99 && test_0_1 == 99 && floorOrCorridor(test_n1_1))
			{
				cornerRot = 2;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
			if (test_0_1 == 99 && test_1_0 == 99 && floorOrCorridor(test_1_1))
			{
				cornerRot = 1;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
			if (test_1_0 == 99 && test_0_n1 == 99 && floorOrCorridor(test_1_n1))
			{
				cornerRot = 0;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
			if (test_0_n1 == 99 && test_n1_0 == 99 && floorOrCorridor(test_n1_n1))
			{
				cornerRot = 3;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
		}
	}
}

void AC_GridData::testNSEW(int X, int Y, TArray<int> inTestGrid, int& TileOut1, int& TileOut2, int& TileOut3, int& TileOut4, int& TileOut5, int& TileOut6, int& TileOut7, int& TileOut8)
{
	tileTestOut.Empty();
	int x_axis;
	int y_axis;
	int value;
	int indexOut;
	for (int i = 0; i < test8Points.Num(); i++)
	{
		x_axis = floor(test8Points[i].X) + X;
		y_axis = floor(test8Points[i].Y) + Y;
		

		y_axis = floor(test8Points[i].Y) + Y;

		if (x_axis < xMax&& y_axis < yMax && x_axis >= 0&& y_axis >= 0)
		{
			getArrayValueXYin(x_axis, y_axis, inTestGrid, indexOut, value);
			tileTestOut.Add(value);
			
		}
		else
		{
			tileTestOut.Add(666);
		}
	}
	int index = 0;
	TileOut1 = tileTestOut[0];
	index++;
	TileOut2 = tileTestOut[1];
	index++;
	TileOut3 = tileTestOut[2];
	index++;
	TileOut4 = tileTestOut[3];
	index++;
	TileOut5 = tileTestOut[4];
	index++;
	TileOut6 = tileTestOut[5];
	index++;
	TileOut7 = tileTestOut[6];
	index++;
	TileOut8 = tileTestOut[7];
	
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
	wallMesh->AddInstance(transform);
	FRotator newRotation = (transform.GetRotation().Rotator() + FRotator(0.0f, 180.0f, 0.0f));
	FTransform newPos = FTransform(newRotation, transform.GetLocation(), transform.GetScale3D());
	wallMesh->AddInstance(newPos);
	if (!fillerCreated[tileIndex])
	{
		groundFillerFullMesh->AddInstance(transform);
		fillerCreated[tileIndex] = true;
	}
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
	quadHolding = quadRoomIn;
	okForTiles = false;
	if (!quadRoomIn->hasChild)
	{
		FVector quadNWC;
		FVector quadNEC;
		FVector quadSWC;
		FVector quadSEC;
		quadHolding->BoundaryCorners(quadNWC, quadNEC, quadSEC, quadSWC);
		quadNWC = quadNWC / tileSize;
		quadSEC = quadSEC / tileSize;
		quadRoomBound_Right = quadNWC.X;
		quadRoomBound_Left = quadSEC.X;
		quadRoomBound_Top = quadNWC.Y;
		quadRoomBound_Bottom = quadSEC.Y;


		for (int index = 0; index <= 14; index++)
		{
			//debug

			//
			roomCentre_X = FMath::RandRange((roomWallBorder+quadRoomBound_Left + (roomMinSize / 2.0f)), (quadRoomBound_Right-(roomMinSize/2.0f))-roomWallBorder);
			roomCentre_Y = FMath::RandRange((roomWallBorder + quadRoomBound_Bottom + (roomMinSize / 2.0f)), (quadRoomBound_Top - (roomMinSize / 2.0f)) - roomWallBorder);

			halfY = (quadRoomBound_Top-roomCentre_Y) - roomWallBorder;
			halfY2 = (roomCentre_Y-quadRoomBound_Bottom) - roomWallBorder;
			halfX = (quadRoomBound_Right - roomCentre_X)-roomWallBorder;
			halfX2 = (roomCentre_X - quadRoomBound_Left) - roomWallBorder;

			if (halfX2 < halfX)
			{
				halfX = halfX2;
			}

			if (halfX > (roomMaxSize / 2.0f))
			{
				halfX = roomMaxSize / 2.0f;
			}

			roomHalf_X = round(FMath::RandRange(roomMinSize / 2.0f, ceil(halfX)));

			if (halfY2 < halfY) halfY = halfY2;
			if (halfY > (roomMaxSize / 2.0f)) halfY = roomMaxSize / 2.0f;
			roomHalf_Y = round(FMath::RandRange(roomMinSize / 2.0f, ceil(halfY)));

			FVector centreVect =( FVector(roomCentre_X, roomCentre_Y, 0.0f) * tileSize);
			FVector halfVect = (FVector(roomHalf_X, roomHalf_Y, 1.0f) * tileSize);
			centreVect;
			halfVect;
			FVector toRight = quadHolding->GetActorLocation() + quadHolding->BoundingBox->GetUnscaledBoxExtent();
			FVector toLeft = quadHolding->GetActorLocation() - quadHolding->BoundingBox->GetUnscaledBoxExtent();

			
			if ( abs(centreVect.X + halfVect.X)   >= toRight.X||
				abs(centreVect.X - halfVect.X)  <= toLeft.X||
				abs(centreVect.Y + halfVect.Y) >= toRight.Y || 
				abs(centreVect.Y - halfVect.Y) <= toLeft.Y)
			{
				
			}
			else
			{
				if ((abs((centreVect.X + halfVect.X) - (centreVect.X - halfVect.X)) >= 400.0f && abs((centreVect.Y + halfVect.Y)-(centreVect.Y - halfVect.Y)) >= 200.0f) ||
					(abs((centreVect.X + halfVect.X) - (centreVect.X - halfVect.X)) >= 200.0f && abs((centreVect.Y + halfVect.Y) - (centreVect.Y - halfVect.Y)) >= 400.0f))
				{
					okForTiles = true;
					break;
				}
			}
		}
		if (okForTiles)
		{
			AC_QuadRooms* boxComp;
			FVector spawnPos = FVector(roomCentre_X, roomCentre_Y, 0.0f) * tileSize;
			FVector spawnHalfPos = FVector(roomHalf_X, roomHalf_Y, 1.0f) * tileSize;

			boxComp = GetWorld()->SpawnActor<AC_QuadRooms>(quadRoomsSubClass, spawnPos, FRotator::ZeroRotator);
			boxComp->initBounds(spawnPos.X, spawnPos.Y, spawnHalfPos.X, spawnHalfPos.Y);
			boxComp->absCentre_X = boxComp->GetActorLocation().X;
			boxComp->absCentre_Y = boxComp->GetActorLocation().Y;
			digRooms(boxComp);
			quadHolding->RealRoom = boxComp;
			realRoomsArray.Add(boxComp);
		}
	}
}

void AC_GridData::generateCorridorTiles(AC_QuadRooms* quadRoomIn, TArray<AC_QuadRooms*> LeafQuadRoom)
{
	quadHolding = quadRoomIn;
	leafCopy = LeafQuadRoom;
	if (quadRoomIn->childBoundaries.Num() > 0)
	{
		nw_QuadRoom = quadHolding->childBoundaries[0];

		if (quadRoomIn->childBoundaries.Num() > 1)ne_QuadRoom = quadHolding->childBoundaries[1];
		if (quadRoomIn->childBoundaries.Num() > 2)sw_QuadRoom = quadHolding->childBoundaries[2];
		if(quadRoomIn->childBoundaries.Num() > 3) se_QuadRoom = quadHolding->childBoundaries[3];
		
	}
	if (ne_QuadRoom != nullptr)ne_QuadRoom = ne_QuadRoom->RealRoom;
	if (nw_QuadRoom != nullptr)nw_QuadRoom = nw_QuadRoom->RealRoom;
	if (se_QuadRoom != nullptr)se_QuadRoom = se_QuadRoom->RealRoom;
	if (sw_QuadRoom != nullptr)sw_QuadRoom = sw_QuadRoom->RealRoom;

	if (b_HasChildrenWithRooms(quadHolding))
	{
		FVector neCentre = originVec;
		FVector nwCentre = originVec;
		FVector seCentre = originVec;
		FVector swCentre = originVec;
		if (ne_QuadRoom != nullptr)neCentre = ne_QuadRoom->GetActorLocation() / tileSize;
		if (nw_QuadRoom != nullptr)nwCentre = nw_QuadRoom->GetActorLocation() / tileSize;
		if (se_QuadRoom != nullptr)seCentre = se_QuadRoom->GetActorLocation() / tileSize;
		if (sw_QuadRoom != nullptr)swCentre = sw_QuadRoom->GetActorLocation() / tileSize;

		if (ne_QuadRoom != nullptr && nw_QuadRoom != nullptr)
		{
			bool isComplete = digCorridor(nwCentre,neCentre);
			connectedOnce.AddUnique(ne_QuadRoom);

		}
		else 
		{
			if (ne_QuadRoom != nullptr && se_QuadRoom != nullptr)
			{
				bool isComplete = digCorridor(neCentre, seCentre);
				connectedOnce.AddUnique(se_QuadRoom);
			}
			else
			{
				if (se_QuadRoom != nullptr && sw_QuadRoom != nullptr)
				{
					bool isComplete = digCorridor(seCentre, swCentre);
					connectedOnce.AddUnique(sw_QuadRoom);
				}
				else
				{
					if (nw_QuadRoom != nullptr && sw_QuadRoom != nullptr)
					{
						bool isComplete = digCorridor(nwCentre, swCentre);
						connectedOnce.AddUnique(nw_QuadRoom);
					}
					
				}
			}
		}
	}
	else
	{
		newDist = 5000000.0f;
		for (int i = 0;i < leafCopy.Num();i++)
		{
			if (leafCopy[i] != quadHolding)
			{
				if (!connectedOnce.Contains(leafCopy[i]->RealRoom))
				{
					d_temp = leafCopy[i]->RealRoom->GetDistanceTo(quadHolding->RealRoom);
					if (d_temp < newDist)
					{
						closestReturn = leafCopy[i];
						newDist = d_temp;
					}
				}
			}
		}
		FVector holdingCentre = originVec;
		if(quadHolding->RealRoom!= nullptr)holdingCentre = quadHolding->RealRoom->GetActorLocation() / tileSize;
		FVector closestCentre = closestReturn->GetActorLocation() / tileSize;
		bool isComplete = digCorridor(closestCentre, holdingCentre);
		connectedOnce.AddUnique(quadHolding->RealRoom);
	}
}

bool AC_GridData::floorOrCorridor(int in)
{

	bool result;
	if (in == 1 || in == 2) result = true;
	else result = false;
	
	return result;
}

bool AC_GridData::emptyorOutside(int in)
{
	
	bool result;
	if (in == 0 || in == 666) result = true;
	else result = false;

	return result;
}

bool AC_GridData::wallOrEmptyOrOutside(int in)
{
	
	bool result;
	if (in == 0 || in == 666 || in == 99) result = true;
	else result = false;

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
	FVector translation = (FVector(fX, fY, 0.0f)+ originVec)*tileSize;
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

