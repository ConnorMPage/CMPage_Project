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

	//sets the mesh cull distance allowing it to be seen at close range but not from afar to help performance
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

void AC_GridData::passInVariables(FVector mapDim, int tSize, int rwborder, int corW, int roomMin)// passes in variables from the gamemode
{
	
	tileSize = tSize;//size of tiles
	mapDimensions = mapDim / tileSize;//map size
	roomWallBorder = rwborder;//size of the rooms
	corridorWidth = corW;//width of the corridors
	roomMinSize = roomMin;//minimum room size
	
	// resizes the arrays to the required quantity of tiles
	int startSize = floor(mapDimensions.X * mapDimensions.Y);
	tiles.SetNum(startSize);
	tileType.SetNum(startSize);
	cornerRotationArray.SetNum(startSize);
	fillerCreated.SetNum(startSize);
	tileCollisionActors.SetNum(startSize);
	for (int i = zeroInt; i < tiles.Num(); i++)
	{//initialises all array
		tiles[i] = false;
		tileType[i] = zeroInt;
		cornerRotationArray[i] = 1;
		fillerCreated[i] = false;
	}
}

void AC_GridData::createGrid(AC_SetUpQuadTree* quadTreeRef)//main creation function started externally from gamemode
{
	quadTree = quadTreeRef;
	for (int i = zeroInt; i < quadTree->QuadRoomArray.Num(); i++)
	{
		GenerateRoomTiles(quadTree->QuadRoomArray[i]);//creates the actual rooms array and digs the room
	}
	for (int i = zeroInt; i < quadTree->QuadRoomArray.Num(); i++)
	{
		generateCorridorTiles(quadTree->QuadRoomArray[i], quadTree->justLeafNodes_QuadRoom);//creates the corner array and digs the corridors
	}
	lastIndex = floor((mapDimensions.X * mapDimensions.Y) - 1.0f);
	xMax = floor(mapDimensions.X);//sets the x and y max values
	yMax = floor(mapDimensions.Y);
	
	edgeClearing();// creates the gap between rooms and ceilings for the walls
	generateWalls();//creates the wall mesh instances
	


	for (int index = zeroInt; index < lastIndex; index++)//loops through tiles
	{
		tileIndex = index;//sets the tile index to index
		int xAxis, yAxis;
		getXYBaseOnIndex(tileIndex, xMax, yMax, xAxis, yAxis);//initalises the x and y axis

		FVector transVector=( FVector(xAxis,yAxis, zeroFloat)+ FVector(zeroFloat, zeroFloat, zeroFloat))* tileSize;
		FRotator transRot = FRotator(zeroFloat, (cornerRotationArray[tileIndex] + 3) * 90.0f, zeroFloat);
		FVector visVector = transVector + FVector((tileSize / 2), (tileSize / 2), zeroFloat);

		visualTransform = FTransform(transRot, transVector, FVector(1.0f, 1.0f, 1.0f));
		collisionTransform = FTransform(FRotator(zeroFloat, zeroFloat, zeroFloat), transVector, FVector(1.0f, 1.0f, 1.0f));

		if (tileType[tileIndex] == 99)//checks index for  rotation then makes ftransform for that rotation
		{
			FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f),collisionTransform.GetScale3D());
			AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);//spawns wall collision actor
		}
		else
		{
			if (tileType[tileIndex] == 100)//checks index for  rotation then makes ftransform for that rotation
			{
				FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
				AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);//spawns wall collision actor
			}
			else
			{
				if (tileType[tileIndex] == 101)//checks index for  rotation then makes ftransform for that rotation
				{
					FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
					AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);//spawns wall collision actor
				}
				else
				{
					if (tileType[tileIndex] == 102)//checks index for  rotation then makes ftransform for that rotation
					{
						FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
						AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);//spawns wall collision actor
					}
					else
					{
						if (tileType[tileIndex] == 103)//checks index for  rotation then makes ftransform for that rotation
						{
							FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
							AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);//spawns wall collision actor
						}
						else
						{
							if (tileType[tileIndex] != 0)//checks index for  rotation then makes ftransform for that rotation
							{
								floorMesh->AddInstance(visualTransform);
								tiles[tileIndex] = true;
								// finish off
							}
							else
							{
								groundFillerFullMesh->AddInstance(visualTransform);
								FTransform tmpTransform = FTransform(collisionTransform.GetRotation(), collisionTransform.GetLocation() + FVector(-50.0f, -50.0f, -50.0f), collisionTransform.GetScale3D());
								AC_WallCollision* wallColl = GetWorld()->SpawnActor<AC_WallCollision>(wallColCLass, tmpTransform);//spawns wall collision actor
							}
						}
					}
				}
			}
		}
	}
	for (int i = zeroInt; i < tileType.Num(); i++)//loops through tiles
	{
		if (tileType[i] == 100 || tileType[i] == 101 || tileType[i] == 102 || tileType[i] == 103 || tileType[i] == 99 || tileType[i] == 0)//any of these set to -1
		{
			tileType[i] = -1;
		}
	}
}

void AC_GridData::digRooms(AC_QuadRooms* quadRoomIn)
{
	quadRoomIn->BoundaryBounds(quadRoomBound_Left, quadRoomBound_Right, quadRoomBound_Top, quadRoomBound_Bottom);//gets the boundary
	if (quadRoomBound_Right < quadRoomBound_Left)
	{
		tmp = quadRoomBound_Right;
		quadRoomBound_Right = quadRoomBound_Left;
		quadRoomBound_Left = tmp;
	}
	if (quadRoomBound_Top < quadRoomBound_Bottom)
	{
		tmp = zeroFloat;
		quadRoomBound_Top = quadRoomBound_Bottom;
		quadRoomBound_Bottom = tmp;
	}//previous if statments get the highest numbers
	int indexOut;
	bool value;
	for (int y = floor(quadRoomBound_Bottom / tileSize); y < (floor(quadRoomBound_Top / tileSize) - 1); y++)
	{
		for (int x = floor(quadRoomBound_Left / tileSize); x < (floor(quadRoomBound_Right / tileSize) - 1); x++)
		{
			getArrayValueXYinbool(x, y, tiles, indexOut,value);//gets the array vallue
			tiles[indexOut] = true;//sets tile to true
			tileType[indexOut] = 1;
			 
		}
	}
}

bool AC_GridData::digCorridor(FVector room1Centre, FVector room2Centre)
{
	//initialises the variables for col and rows
	col1 = floor(room1Centre.X-0.5f);
	row1= floor(room1Centre.Y - 0.5f);
	col2 = floor(room2Centre.X - 0.5f);
	row2 = floor(room2Centre.Y - 0.5f);

	int indexOut;
	bool value;
	if (row1 <= row2)//if row 1 is smaller
	{
		for (int x = col1; x <(col1+corridorWidth);x++)//if col 1 is smaller
		{
			for (int y = row1; y < (row2 + zeroInt) ;y++)
			{
				getArrayValueXYinbool(x, y, tiles, indexOut, value);//gets the bool value
				if (tileType[indexOut] != 1)
				{
					tiles[indexOut] = true;//sets to true
					tileType[indexOut] = 2;
				}
			}
		}
	}
	else//repeats as above
	{
		for (int x = col1; x < (col1 + corridorWidth); x++)
		{
			for (int y = row2; y < (row1 + zeroInt); y++)
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
	
	if (col1 <= col2)//repeats as above
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
	else//repeats as above
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

	return true;//returns true
}

bool AC_GridData::b_HasChildrenWithRooms(AC_QuadRooms* quadRoomIn)
{

	bool hasChildren = false;//sets has children to false


	if (!b_HasChildren(quadRoomIn)) {
		hasChildren = false;//checks if has children if notr then flase
	}
	else
	{
		if (quadRoomIn->childBoundaries.Num() > zeroInt)hasChildren = true;
		else hasChildren = false;
	}
	
	return hasChildren;//returns has children
}

bool AC_GridData::b_HasChildren(AC_QuadRooms* quadRoomIn)
{
	bool result = false;
	if (quadRoomIn->childBoundaries.Num() > zeroInt)result = true;
	else result = false;//checks if has children if notr then flase
	return result;
}
void AC_GridData::edgeClearing()
{
	int x = xMax - 1;
	int indexOut;
	bool value;
	for (int i = zeroInt; i > x; i++)
	{
		getArrayValueXYinbool(zeroInt, i, tiles, indexOut, value);//gets array bool
		tiles[indexOut] = false;//sets false
		tileType[indexOut] = zeroInt;
	}
	for (int i = zeroInt; i > x; i++)
	{
		getArrayValueXYinbool(x, i, tiles, indexOut, value);//gets array bool
		tiles[indexOut] = false;//sets false
		tileType[indexOut] = zeroInt;
	}
	int y = yMax - 1;
	for (int i = zeroInt; i > y; i++)
	{
		getArrayValueXYinbool(i, y, tiles, indexOut, value);//gets array bool
		tiles[indexOut] = false;//sets false
		tileType[indexOut] = zeroInt;
	}
	for (int i = zeroInt; i > y; i++)
	{
		getArrayValueXYinbool(i, zeroInt, tiles, indexOut, value);//gets array bool
		tiles[indexOut] = false;//sets false
		tileType[indexOut] = zeroInt;
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
	for (int arrayIndex = zeroInt; arrayIndex < tileType.Num(); arrayIndex++)
	{
		getXYBaseOnIndex(arrayIndex, floor(mapDimensions.X), floor(mapDimensions.Y), localXIndex, localYIndex);//gets x and y
		int value;
		int indexOut;
		getArrayValueXYin(localXIndex, localYIndex, tileType, indexOut, value);
	
		if (value == zeroInt)
		{
			testNSEW(localXIndex, localYIndex, tileType, tileO1, tileO2, tileO3, tileO4, tileO5, tileO6, tileO7, tileO8);//produces tile id num
			if (floorOrCorridor(tileO1) || floorOrCorridor(tileO2) || floorOrCorridor(tileO3) || floorOrCorridor(tileO4) ||
				floorOrCorridor(tileO5) || floorOrCorridor(tileO6) || floorOrCorridor(tileO7) || floorOrCorridor(tileO8))//if any statment is true then
			{
				tileType[arrayIndex] = 99;
			}
		}
	}
	testArray.Empty();
	testArray = tileType;
	for (int arrayIndex = zeroInt; arrayIndex < tileType.Num(); arrayIndex++)
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
			{//all 17 statements are the same but create different instances
				cornerRot = 3;
				getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
				tileType[indexOut] = 99;
				cornerRotationArray[indexOut] = cornerRot;
				makeWall(makeTileTransform());//creates wall instance
			}
			else
			{
				if (floorOrCorridor(test_0_1) && test_n1_0 == 99 && test_1_0 == 99 &&wallOrEmptyOrOutside(test_0_n1))
				{
					cornerRot = 2;
					getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
					tileType[indexOut] = 99;
					cornerRotationArray[indexOut] = cornerRot;
					makeWall(makeTileTransform());//creates wall instance
				}
				else
				{
					if (floorOrCorridor(test_1_0) && test_0_1 == 99 && test_0_n1 == 99 && wallOrEmptyOrOutside(test_n1_0))
					{
						cornerRot = 1;
						getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
						tileType[indexOut] = 99;
						cornerRotationArray[indexOut] = cornerRot;
						makeWall(makeTileTransform());//creates wall instance
					}
					else
					{
						if (floorOrCorridor(test_0_n1) && test_1_0 == 99 && test_n1_0 == 99 && wallOrEmptyOrOutside(test_0_1))
						{
							cornerRot = zeroInt;
							getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
							tileType[indexOut] = 99;
							cornerRotationArray[indexOut] = cornerRot;
							makeWall(makeTileTransform());//creates wall instance
						}
						else
						{
							if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_1_0) && test_0_n1 == 99 && test_0_1 == 99)
							{
								cornerRot = 3;
								getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
								tileType[indexOut] = 102;
								cornerRotationArray[indexOut] = cornerRot;
								makeDoubleWall(makeTileTransform());//creates double wall instance
							}
							else
							{
								if (floorOrCorridor(test_0_1) && floorOrCorridor(test_0_n1) && test_n1_0 == 99 && test_1_0 == 99)
								{
									cornerRot = 2;
									getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
									tileType[indexOut] = 102;
									cornerRotationArray[indexOut] = cornerRot;
									makeDoubleWall(makeTileTransform());//creates double wall instance
								}
								else
								{
									if (floorOrCorridor(test_1_0) && floorOrCorridor(test_n1_0) && test_0_1 == 99 && test_0_n1 == 99)
									{
										cornerRot = 1;
										getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
										tileType[indexOut] = 102;
										cornerRotationArray[indexOut] = cornerRot;
										makeDoubleWall(makeTileTransform());//creates double wall instance
									}
									else
									{
										if (floorOrCorridor(test_0_n1) && floorOrCorridor(test_0_1) && test_n1_0 == 99 && test_1_0 == 99)
										{
											cornerRot = zeroInt;
											getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
											tileType[indexOut] = 102;
											cornerRotationArray[indexOut] = cornerRot;
											makeDoubleWall(makeTileTransform());//creates double wall instance
										}
										else
										{
											if (test_n1_0 == 99 && test_0_1 == 99 && anyTile(test_n1_1) && floorOrCorridor(test_1_n1) && floorOrCorridor(test_1_0) && floorOrCorridor(test_0_n1))
											{
												cornerRot = 3;
												getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
												tileType[indexOut] = 100;
												cornerRotationArray[indexOut] = cornerRot;
												makeCorner(makeTileTransform());//creates corner
											}
											else
											{
												if (test_0_1 == 99 && test_1_0 == 99 && anyTile(test_1_1) && floorOrCorridor(test_n1_n1) && floorOrCorridor(test_0_n1) && floorOrCorridor(test_n1_0))
												{
													cornerRot = 2;
													getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
													tileType[indexOut] = 100;
													cornerRotationArray[indexOut] = cornerRot;
													makeCorner(makeTileTransform());//creates corner
												}
												else
												{
													if (test_1_0 == 99 && test_0_n1 == 99 && anyTile(test_1_n1) && floorOrCorridor(test_n1_1) && floorOrCorridor(test_n1_0) && floorOrCorridor(test_0_1))
													{
														cornerRot = 1;
														getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
														tileType[indexOut] = 100;
														cornerRotationArray[indexOut] = cornerRot;
														makeCorner(makeTileTransform());//creates corner
													}
													else
													{
														if (test_0_n1 == 99 && test_n1_0 == 99 && anyTile(test_n1_n1) && floorOrCorridor(test_1_1) && floorOrCorridor(test_0_1) && floorOrCorridor(test_1_0))
														{
															cornerRot = zeroInt;
															getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
															tileType[indexOut] = 100;
															cornerRotationArray[indexOut] = cornerRot;
															makeCorner(makeTileTransform());//creates corner
														}
														else
														{
															if (floorOrCorridor(test_0_1 )&&floorOrCorridor(test_1_0)&& floorOrCorridor(test_0_n1)&&test_n1_0==99)
															{
																cornerRot = 3;
																getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																tileType[indexOut] = 103;
																cornerRotationArray[indexOut] = cornerRot;
																makeCap(makeTileTransform());//creates cap
															}
															else
															{
																if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_1_0) && floorOrCorridor(test_0_n1) && test_0_1==99)
																{
																	cornerRot = 2;
																	getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																	tileType[indexOut] = 103;
																	cornerRotationArray[indexOut] = cornerRot;
																	makeCap(makeTileTransform());//creates cap
																}
																else
																{
																	if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_0_1) && floorOrCorridor(test_0_n1) && test_1_0 ==99)
																	{
																		cornerRot = 1;
																		getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																		tileType[indexOut] = 103;
																		cornerRotationArray[indexOut] = cornerRot;
																		makeCap(makeTileTransform());//creates cap
																	}
																	else
																	{
																		if (floorOrCorridor(test_n1_0) && floorOrCorridor(test_0_1) && floorOrCorridor(test_1_0) && test_0_n1 == 99)
																		{
																			cornerRot = zeroInt;
																			getArrayValueXYin(localXIndex, localYIndex, testArray, value, indexOut);
																			tileType[indexOut] = 103;
																			cornerRotationArray[indexOut] = cornerRot;
																			makeCap(makeTileTransform());//creates cap
																		}
																		else
																		{
																			if (floorOrCorridor(test_n1_0)&& floorOrCorridor(test_0_1)&& floorOrCorridor(test_1_0)&& floorOrCorridor(test_0_n1))
																			{
																				cornerRot = 1;
																				pillarWallMesh->AddInstance(makeTileTransform());//creates pillar
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
	for (int index = zeroInt; index < tileType.Num(); index++)
	{
		tileIndex = index;
		alreadyMade = false;
		getXYBaseOnIndex(index, floor(mapDimensions.X), floor(mapDimensions.Y), localXIndex, localYIndex);//gets x and y
		int value;
		int outInd;
		getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);//gets int value
		if (value == 99)
		{
			testNSEW(localXIndex, localYIndex, testArray, test_n1_0, test_n1_1, test_0_1, test_1_1, test_1_0, test_1_n1, test_0_n1, test_n1_n1);//tests instance ids 

			FRotator newRot = FRotator(0.0f, ((cornerRot + 3) * 90.0f), 0.0f);
			FVector newPos = FVector(0.0f, 0.0f, 0.0f);
			int xAxis,yAxis;
			getXYBaseOnIndex(tileIndex, xMax, yMax,xAxis,yAxis);//gets x and y
			newPos.X = newPos.X + xAxis;
			newPos.Y = newPos.Y + yAxis;
			visualTransform = FTransform(newRot, newPos, FVector(1.0f, 1.0f, 1.0f));

			if (test_n1_0 == 99 && test_0_1 == 99 && floorOrCorridor(test_n1_1))//checks if id is inside corner
			{
				cornerRot = 2;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);//creates inside corner mesh
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);//creates ground filler mesh
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
			if (test_0_1 == 99 && test_1_0 == 99 && floorOrCorridor(test_1_1))//checks if id is inside corner
			{
				cornerRot = 1;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);//creates inside corner mesh
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);//creates ground filler mesh
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
			if (test_1_0 == 99 && test_0_n1 == 99 && floorOrCorridor(test_1_n1))//checks if id is inside corner
			{
				cornerRot = zeroInt;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);//creates inside corner mesh
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);//creates ground filler mesh
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
			if (test_0_n1 == 99 && test_n1_0 == 99 && floorOrCorridor(test_n1_n1))//checks if id is inside corner
			{
				cornerRot = 3;
				getArrayValueXYin(localXIndex, localYIndex, testArray, outInd, value);
				tileType[outInd] = 101;
				cornerRotationArray[outInd] = cornerRot;
				insideCornerMesh->AddInstance(visualTransform);//creates inside corner mesh
				if (!alreadyMade)
				{
					if (!fillerCreated[tileIndex])
					{
						groundFillerFullMesh->AddInstance(visualTransform);//creates ground filler mesh
						fillerCreated[tileIndex] = true;
						alreadyMade = true;
					}
				}
			}
		}
	}
}

void AC_GridData::testNSEW(int X, int Y, TArray<int> inTestGrid, int& TileOut1, int& TileOut2, int& TileOut3, int& TileOut4, int& TileOut5, int& TileOut6, int& TileOut7, int& TileOut8)
{//used to get room boundaries
	tileTestOut.Empty();//clears array
	int x_axis;
	int y_axis;
	int value;
	int indexOut;
	for (int i = zeroInt; i < test8Points.Num(); i++)
	{
		x_axis = floor(test8Points[i].X) + X;
		y_axis = floor(test8Points[i].Y) + Y;
		

		y_axis = floor(test8Points[i].Y) + Y;

		if (x_axis < xMax&& y_axis < yMax && x_axis >= zeroInt && y_axis >= zeroInt)
		{
			getArrayValueXYin(x_axis, y_axis, inTestGrid, indexOut, value);//gets array value
			tileTestOut.Add(value);
			
		}
		else
		{
			tileTestOut.Add(666);
		}
	}
	int index = zeroInt;
	//fills the outputs with array contents
	TileOut1 = tileTestOut[index];
	index++;
	TileOut2 = tileTestOut[index];
	index++;
	TileOut3 = tileTestOut[index];
	index++;
	TileOut4 = tileTestOut[index];
	index++;
	TileOut5 = tileTestOut[index];
	index++;
	TileOut6 = tileTestOut[index];
	index++;
	TileOut7 = tileTestOut[index];
	index++;
	TileOut8 = tileTestOut[index];
	
}

void AC_GridData::makeWall(FTransform transform)
{
	wallMesh->AddInstance(transform);//creates the main instnce of function
	if (!fillerCreated[tileIndex])
	{
		groundFillerFullMesh->AddInstance(transform);
		fillerCreated[tileIndex] = true;
	}
}

void AC_GridData::makeDoubleWall(FTransform transform)
{
	wallMesh->AddInstance(transform);//creates the main instnce of function
	FRotator newRotation = (transform.GetRotation().Rotator() + FRotator(0.0f, 180.0f, 0.0f));
	FTransform newPos = FTransform(newRotation, transform.GetLocation(), transform.GetScale3D());
	wallMesh->AddInstance(newPos);//creates the main instnce of function
	if (!fillerCreated[tileIndex])
	{
		groundFillerFullMesh->AddInstance(transform);
		fillerCreated[tileIndex] = true;
	}
}

void AC_GridData::makeCorner(FTransform transform)
{
	outsideCornerMesh->AddInstance(transform);//creates the main instnce of function
	if (!fillerCreated[tileIndex])
	{
		cornerFillerMesh->AddInstance(transform);
		fillerCreated[tileIndex] = true;
	}
}

void AC_GridData::makeCap(FTransform transform)
{
	capWallMesh->AddInstance(transform);//creates the main instnce of function
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
	{//initilisation of variables
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


		for (int index = zeroInt; index <= 14; index++)
		{
			//debug

			//gets random numbers for centre points
			roomCentre_X = FMath::RandRange((roomWallBorder+quadRoomBound_Left + (roomMinSize / 2.0f)), (quadRoomBound_Right-(roomMinSize/2.0f))-roomWallBorder);
			roomCentre_Y = FMath::RandRange((roomWallBorder + quadRoomBound_Bottom + (roomMinSize / 2.0f)), (quadRoomBound_Top - (roomMinSize / 2.0f)) - roomWallBorder);

			halfY = (quadRoomBound_Top-roomCentre_Y) - roomWallBorder;
			halfY2 = (roomCentre_Y-quadRoomBound_Bottom) - roomWallBorder;
			halfX = (quadRoomBound_Right - roomCentre_X)-roomWallBorder;
			halfX2 = (roomCentre_X - quadRoomBound_Left) - roomWallBorder;
			//if stamnets to get biggest value
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

			FVector centreVect =( FVector(roomCentre_X, roomCentre_Y, 0.0f) * tileSize);//vector for room centre
			FVector halfVect = (FVector(roomHalf_X, roomHalf_Y, 1.0f) * tileSize);//vector for half of centre
			centreVect;
			halfVect;
			FVector toRight = quadHolding->GetActorLocation() + quadHolding->BoundingBox->GetUnscaledBoxExtent();
			FVector toLeft = quadHolding->GetActorLocation() - quadHolding->BoundingBox->GetUnscaledBoxExtent();

			
			if ( abs(centreVect.X + halfVect.X)   >= toRight.X||
				abs(centreVect.X - halfVect.X)  <= toLeft.X||
				abs(centreVect.Y + halfVect.Y) >= toRight.Y || 
				abs(centreVect.Y - halfVect.Y) <= toLeft.Y)//if within boundary limits
			{
				
			}
			else
			{
				if ((abs((centreVect.X + halfVect.X) - (centreVect.X - halfVect.X)) >= 400.0f && abs((centreVect.Y + halfVect.Y)-(centreVect.Y - halfVect.Y)) >= 200.0f) ||
					(abs((centreVect.X + halfVect.X) - (centreVect.X - halfVect.X)) >= 200.0f && abs((centreVect.Y + halfVect.Y) - (centreVect.Y - halfVect.Y)) >= 400.0f))
				{
					okForTiles = true;//sets to true
					break;
				}
			}
		}
		if (okForTiles)//if true
		{
			AC_QuadRooms* boxComp;//creates quadroom comp
			FVector spawnPos = FVector(roomCentre_X, roomCentre_Y, 0.0f) * tileSize;//gets pos
			FVector spawnHalfPos = FVector(roomHalf_X, roomHalf_Y, 1.0f) * tileSize;

			boxComp = GetWorld()->SpawnActor<AC_QuadRooms>(quadRoomsSubClass, spawnPos, FRotator::ZeroRotator);//spawns actor 
			boxComp->initBounds(spawnPos.X, spawnPos.Y, spawnHalfPos.X, spawnHalfPos.Y);//initialises box comp in actor
			boxComp->absCentre_X = boxComp->GetActorLocation().X;
			boxComp->absCentre_Y = boxComp->GetActorLocation().Y;
			digRooms(boxComp);//digs the room 
			quadHolding->RealRoom = boxComp;//adds to real room array
			realRoomsArray.Add(boxComp);
		}
	}
}

void AC_GridData::generateCorridorTiles(AC_QuadRooms* quadRoomIn, TArray<AC_QuadRooms*> LeafQuadRoom)
{
	quadHolding = quadRoomIn;
	leafCopy = LeafQuadRoom;
	if (quadRoomIn->childBoundaries.Num() > zeroInt)
	{
		nw_QuadRoom = quadHolding->childBoundaries[zeroInt];

		if (quadRoomIn->childBoundaries.Num() > 1)ne_QuadRoom = quadHolding->childBoundaries[1];
		if (quadRoomIn->childBoundaries.Num() > 2)sw_QuadRoom = quadHolding->childBoundaries[2];
		if(quadRoomIn->childBoundaries.Num() > 3) se_QuadRoom = quadHolding->childBoundaries[3];
		
	}//if not nullptrs get real room
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
		if (ne_QuadRoom != nullptr)neCentre = ne_QuadRoom->GetActorLocation() / tileSize;//if not nullptrs get pos
		if (nw_QuadRoom != nullptr)nwCentre = nw_QuadRoom->GetActorLocation() / tileSize;
		if (se_QuadRoom != nullptr)seCentre = se_QuadRoom->GetActorLocation() / tileSize;
		if (sw_QuadRoom != nullptr)swCentre = sw_QuadRoom->GetActorLocation() / tileSize;

		if (ne_QuadRoom != nullptr && nw_QuadRoom != nullptr)
		{
			bool isComplete = digCorridor(nwCentre,neCentre);//dig corridor
			connectedOnce.AddUnique(ne_QuadRoom);//add to array for connections

		}
		else 
		{
			if (ne_QuadRoom != nullptr && se_QuadRoom != nullptr)
			{
				bool isComplete = digCorridor(neCentre, seCentre);//dig corridor
				connectedOnce.AddUnique(se_QuadRoom);//add to array for connections
			}
			else
			{
				if (se_QuadRoom != nullptr && sw_QuadRoom != nullptr)
				{
					bool isComplete = digCorridor(seCentre, swCentre);//dig corridor
					connectedOnce.AddUnique(sw_QuadRoom);//add to array for connections
				}
				else
				{
					if (nw_QuadRoom != nullptr && sw_QuadRoom != nullptr)
					{
						bool isComplete = digCorridor(nwCentre, swCentre);//dig corridor
						connectedOnce.AddUnique(nw_QuadRoom);//add to array for connections
					}
					
				}
			}
		}
	}
	else
	{
		newDist = 5000000.0f;
		for (int i = zeroInt;i < leafCopy.Num();i++)
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
		if(quadHolding->RealRoom!= nullptr)holdingCentre = quadHolding->RealRoom->GetActorLocation() / tileSize;//gets real room pos
		FVector closestCentre = closestReturn->GetActorLocation() / tileSize;//gets the next rooms centre
		bool isComplete = digCorridor(closestCentre, holdingCentre);//digs corridor
		connectedOnce.AddUnique(quadHolding->RealRoom);
	}
}
//three or bool functions provide a true or false
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
	if (in == zeroInt || in == 666) result = true;
	else result = false;

	return result;
}

bool AC_GridData::wallOrEmptyOrOutside(int in)
{
	
	bool result;
	if (in == zeroInt || in == 666 || in == 99) result = true;
	else result = false;

	return result;
}

FTransform AC_GridData::makeTileTransform()//creates a ftransform from titleindex
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
//bool to see if tile
bool AC_GridData::anyTile(int in)
{
	bool if1;
	bool if2;
	bool if3;
	bool if4;
	bool if5;
	if (in == zeroInt)if1 = true;
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

