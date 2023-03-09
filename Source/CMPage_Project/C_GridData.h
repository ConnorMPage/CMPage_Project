// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "C_QuadRooms.h"
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
		void passInVariables(FVector mapDim, int tSize, int rwborder, int corW);
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
private:
	//Meshes 
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* pillarWallMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* capFIllerMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* cornerFillerMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* groundFillerFullMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* capWallMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* insideCornerMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* outsideCornerMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* wallMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* floorMesh;
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

	/*UFUNCTION()
		void getArrayValueXYin(int X, int Y, TArray<void>& arrayIn, int indexOut);
	UFUNCTION()
		void getXYBaseOnIndex(int indexin, int XMax, int YMax, int& X, int& Y);
	UFUNCTION()
		void GenerateRoomTiles(AC_QuadRooms* quadRoomIn);
	UFUNCTION()
		void generateCorridorTiles(AC_QuadRooms* quadRoomIn, TArray<AC_QuadRooms*>LeafQuadRoom);
	UFUNCTION()
		bool floorOrCorridor(int in);
	UFUNCTION()
		bool emptyorOutside(int in);*/
	
};
