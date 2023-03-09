// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "C_QuadRooms.generated.h"

UCLASS()
class CMPAGE_PROJECT_API AC_QuadRooms : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_QuadRooms();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void initBounds(float XCentre, float YCentre, float XHalf, float YHalf);
	UFUNCTION()
		bool containsPoint(float X, float Y);
	UFUNCTION()
		void BoundaryCorners(FVector& NWOut, FVector& NEOut, FVector& SEOut, FVector& SWOut);
	UFUNCTION()
		void BoundaryBounds(float& Left, float& Right, float& Top, float& Bottom);
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoundingBox;
	//variables
	UPROPERTY()
		float centre_x;
	UPROPERTY()
		float centre_y;
	UPROPERTY()
		float half_x;
	UPROPERTY()
		float half_y;
	UPROPERTY()
		FVector posDif;
	
	UPROPERTY()
		AC_QuadRooms* parentobj;
	UPROPERTY()
		AC_QuadRooms* RealRoom;
	UPROPERTY()
		TArray< AC_QuadRooms*> childBoundaries;
	UPROPERTY()
		bool hasChild = false;
private:
	UPROPERTY(VisibleAnywhere)
		float centre;
	
	UPROPERTY()
		FVector BoundaryExtent = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY()
		FVector BoundaryPos = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY()
		bool returnbool = false;

};
