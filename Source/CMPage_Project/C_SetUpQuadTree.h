// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "C_SimpleBoundary.h"
#include <vector>
#include "GameFramework/Actor.h"

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
private:
	//UPROPERTY()
		//AC_SimpleBoundary* AABB;
	
	/*
	UFUNCTION()
		void StartSetup();
	//UFUNCTION()
		//AC_SimpleBoundary* NewQuadCell(FVector center, FVector Half, AC_SimpleBoundary* parentObj);
	UFUNCTION()
		std::tuple <int, int, float, float> sliceRand(AC_SimpleBoundary* index);
	UFUNCTION()
		std::vector<FVector> CellSize(float sliceX, float sliceY, AC_SimpleBoundary* index);
	UFUNCTION()
		std::vector<FVector> Center(float sliceX, float sliceY, AC_SimpleBoundary* index);
		*/
};
