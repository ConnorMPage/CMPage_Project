// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "C_QuadRooms.h"
#include "C_WallCollision.h"
#include "C_SetUpQuadTree.h"
#include "C_GridData.generated.h"

UCLASS()
class CMPAGE_PROJECT_API AC_GridData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GridData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void passInVariables(FVector mapDim, int tSize, int rwborder, int corW, int roomMin);
	UFUNCTION()
		void createGrid(AC_SetUpQuadTree* quadTreeRef);
	UPROPERTY(VisibleAnywhere)
		FVector mapDimensions;
	UPROPERTY(VisibleAnywhere)
		int tileSize;
	UPROPERTY(VisibleAnywhere)
		int roomWallBorder;
	UPROPERTY(VisibleAnywhere)
		int corridorWidth;
	UPROPERTY(VisibleAnywhere)
		int roomMinSize;
private:
	//Meshes 
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* pillarWallMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* capFIllerMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* cornerFillerMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* groundFillerFullMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* capWallMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* insideCornerMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* outsideCornerMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* wallMesh;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* floorMesh;
	/*UPROPERTY(EditAnywhere)*/
	/*	UStaticMesh* pillarWallMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* capFIllerMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* cornerFillerMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* groundFillerFullMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* capWallMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* insideCornerMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* outsideCornerMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* wallMeshInstance;
	UPROPERTY(EditAnywhere)
		UStaticMesh* floorMeshInstance;*/
	//functions
	UFUNCTION()
		void digRooms(AC_QuadRooms* quadRoomIn);
	UFUNCTION()
		bool digCorridor(FVector room1Centre, FVector room2Centre);
	UFUNCTION()
		bool b_HasChildrenWithRooms(AC_QuadRooms* quadRoomIn);
	UFUNCTION()
		bool b_HasChildren(AC_QuadRooms* quadRoomIn);
	UFUNCTION()
		AC_QuadRooms* closestRoom(AC_QuadRooms* quadRoomIn);
	UFUNCTION()
		void edgeClearing();
	UFUNCTION()
		void generateWalls();
	UFUNCTION()
		void testNSEW(int X,int Y,TArray<int> inTestGrid,int& TileOut1, int& TileOut2, int& TileOut3,
			int& TileOut4, int& TileOut5, int& TileOut6, int& TileOut7, int& TileOut8);
	UFUNCTION()
		void makeWall(FTransform transform);
	UFUNCTION()
		void makeDoubleWall(FTransform transform);
	UFUNCTION()
		void makeCorner(FTransform transform);
	UFUNCTION()
		void makeCap(FTransform transform);
	UFUNCTION()
		void safeArrayGetCheck(int X,int Y);

	UFUNCTION()
		void getArrayValueXYinbool(int X, int Y, TArray<bool> arrayIn, int& indexOut, bool& value);
	UFUNCTION()
		void getArrayValueXYin(int X, int Y, TArray<int> arrayIn, int& indexOut,int& value);
	UFUNCTION()
		void getXYBaseOnIndex(int indexin, int XMax, int YMax, int& X, int& Y);
	UFUNCTION()
		void GenerateRoomTiles(AC_QuadRooms* quadRoomIn);
	UFUNCTION()
		void generateCorridorTiles(AC_QuadRooms* quadRoomIn, TArray<AC_QuadRooms*>LeafQuadRoom);
	UFUNCTION()
		bool floorOrCorridor(int in);
	UFUNCTION()
		bool emptyorOutside(int in);
	UFUNCTION()
		bool wallOrEmptyOrOutside(int in);
	UFUNCTION()
		FTransform makeTileTransform();
	UFUNCTION()
		bool anyTile(int in);
	UPROPERTY()
		AC_SetUpQuadTree* quadTree;
	//main Variables
	UPROPERTY()
		TArray<int> testArray;
	UPROPERTY()
		FTransform tempTransform;
	UPROPERTY()
		TArray<bool> tiles;
	UPROPERTY()
		TArray<int> tileType;
	UPROPERTY()
		int col1;
	UPROPERTY()
		int row1;
	UPROPERTY()
		int col2;
	UPROPERTY()
		int row2;
	UPROPERTY()
		int i_temp;
	UPROPERTY()
		int roomMaxSize = 32;
	UPROPERTY()
		AC_QuadRooms* closestReturn;
	UPROPERTY()
		AC_QuadRooms* quadHolding;
	UPROPERTY()
		TArray<AC_QuadRooms*> findNearestArray;
	UPROPERTY()
		TArray<AC_QuadRooms*> leafCopy;
	UPROPERTY()
		float d_temp;
	UPROPERTY()
		float newDist = 5000000.0f;
	UPROPERTY()
		bool isWall = false;
	UPROPERTY()
		int genWallOffset = 1;
	UPROPERTY()
		FTransform defaultTransform;
	UPROPERTY()
		TArray<int> finalTyleType;
	UPROPERTY()
		int localXIndex;
	UPROPERTY()
		int localYIndex;
	UPROPERTY()
		TArray<int> cornerRotationArray;
	UPROPERTY()
		FTransform visualTransform;
	UPROPERTY()
		FTransform collisionTransform;
	UPROPERTY()
		bool alreadyMade = true;
	UPROPERTY()
		TArray<bool> fillerCreated;
	UPROPERTY()
		bool okForTiles;
	UPROPERTY()
		TArray<AC_WallCollision*> tileCollisionActors;
	UPROPERTY()
		int xMax;
	UPROPERTY()
		int yMax;
	UPROPERTY()
		int cornerRot;
	UPROPERTY()
		int tileIndex;
	UPROPERTY()
		int lastIndex;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_QuadRooms>quadRoomsSubClass;

	// Generate room variables
	UPROPERTY()
		float halfX;
	UPROPERTY()
		float roomHalf_X;
	UPROPERTY()
		float quadRoomBound_Left;
	UPROPERTY()
		float quadRoomBound_Right;
	UPROPERTY()
		float quadRoomBound_Top;
	UPROPERTY()
		float quadRoomBound_Bottom;
	UPROPERTY()
		float roomCentre_X;
	UPROPERTY()
		float roomCentre_Y;
	UPROPERTY()
		float halfX2;
	UPROPERTY()
		float halfY;
	UPROPERTY()
		float halfY2;
	UPROPERTY()
		float roomHalf_Y;
	UPROPERTY()
		TArray<AC_QuadRooms*> realRoomsArray;
	UPROPERTY()
		float tmp;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_WallCollision> wallColCLass;
	//dig corridor variables
	UPROPERTY()
		AC_QuadRooms* nw_QuadRoom;
	UPROPERTY()
		AC_QuadRooms* ne_QuadRoom;
	UPROPERTY()
		AC_QuadRooms* sw_QuadRoom;
	UPROPERTY()
		AC_QuadRooms* se_QuadRoom;
	UPROPERTY()
		TArray<AC_QuadRooms*> connectedOnce;

	// test variables
	UPROPERTY()
		int test_n1_0;
	UPROPERTY()
		int test_n1_1;
	UPROPERTY()
		int test_0_1;
	UPROPERTY()
		int test_1_1;
	UPROPERTY()
		int test_1_0;
	UPROPERTY()
		int test_1_n1;
	UPROPERTY()
		int test_0_n1;
	UPROPERTY()
		int test_n1_n1;
	UPROPERTY()
		int cornerXTest;
	UPROPERTY()
		int cornerYTest;
	UPROPERTY()
		TArray<int> tileTestOut;
	UPROPERTY()
		TArray<FVector> test8Points = {FVector(-1.0f,0.0f,0.0f),FVector(-1.0f,1.0f,0.0f) ,FVector(0.0f,1.0f,0.0f) ,FVector(1.0f,1.0f,0.0f), 
	FVector(1.0f,0.0f,0.0f),FVector(1.0f,-1.0f,0.0f) ,FVector(0.0f,-1.0f,0.0f),FVector(-1.0f,-1.0f,0.0f) };

	UPROPERTY()
		FVector originVec = FVector(0.0f, 0.0f, 0.0f);
};
