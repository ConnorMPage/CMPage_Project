// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_QuadRooms.h"
#include <vector>

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "C_SetUpQuadTree.generated.h"

UCLASS()
class CMPAGE_PROJECT_API AC_SetUpQuadTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_SetUpQuadTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		FVector mapDimensions = FVector(64.0f, 64.0f, 1.0f);
	UPROPERTY(EditAnywhere)
		int sliceRoomMinSize = 7;
	UPROPERTY(EditAnywhere)
		int tileSize = 100;
	UPROPERTY(EditAnywhere)
		float chanceToDropQuad = 0.0f;
	UPROPERTY(EditAnywhere)
		int roomWallBorder = 2;
	UFUNCTION()
		void generateQuads(AC_QuadRooms*& quadRoomIn, int mainInt);
	UFUNCTION()
		void StartSetup();
	UPROPERTY()
		TArray<AC_QuadRooms*> QuadRoomArray;
	UPROPERTY()
		TArray<AC_QuadRooms*> justLeafNodes_QuadRoom;
	UPROPERTY()
		TArray<AC_QuadRooms*> justTrunkNodes_QuadRoom;
private:
	UPROPERTY()
		AC_QuadRooms* AABB;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_QuadRooms> quadRoomsSubClass;
	
	UPROPERTY()
		int slice_MaxTries = 1000;
	UPROPERTY()
		int SliceTry = 0;
	UPROPERTY()
		bool sliceBreak = false;
	UPROPERTY()
		float sliceHorX = 0.0f;
	UPROPERTY()
		float sliceVerY = 0.0f;
	UPROPERTY()
		bool slices = false;
	UPROPERTY()
		AC_QuadRooms* currentQuadBounds;
	
	UPROPERTY()
		int mainLoopI = 0;
	//UPROPERTY()
		//ACMPage_ProjectGameModeBase* gameModeRef;


	//functions
	
	UFUNCTION()
		AC_QuadRooms* NewQuadCell(FVector center, FVector Half);
	UFUNCTION()
		AC_QuadRooms* NewQuadCell2(FVector center, FVector Half, AC_QuadRooms* parentObj);
	UFUNCTION()
	void sliceRand(AC_QuadRooms* index,int& horSlice, int& verSlice,float& fHorSlice,float& fVerSlice);
	UFUNCTION()
		TArray<FVector> CellSize(float sliceX, float sliceY, AC_QuadRooms* index);
	UFUNCTION()
		TArray<FVector> Center(float sliceX, float sliceY, TArray<FVector> parentArray);
		
};
