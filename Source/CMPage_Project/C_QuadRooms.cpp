// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuadRooms.h"

AC_QuadRooms::AC_QuadRooms()
{
	PrimaryActorTick.bCanEverTick = true;
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounds"));//creates collison box
}

// Sets default values

// Called when the game starts or when spawned
void AC_QuadRooms::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AC_QuadRooms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_QuadRooms::initBounds(float XCentre, float YCentre, float XHalf, float YHalf)
{
	half_x = XHalf;
	half_y = YHalf;
	centre_x = XCentre;
	centre_y = YCentre;

	BoundaryExtent.X = half_x;
	BoundaryExtent.Y = half_y;

	BoundaryPos.X = centre_x;
	BoundaryPos.Y = centre_y;


	
	BoundingBox->SetBoxExtent(BoundaryExtent);//sets box size
	//BoundingBox->SetRelativeLocation(BoundaryPos);//sets location to origin
}

bool AC_QuadRooms::containsPoint(float X, float Y)
{
	returnbool = true;
	if (X > centre_x + half_x ||
		Y > centre_y + half_y ||
		X < centre_x - half_x ||
		Y < centre_y - half_y)
	{
		returnbool = false;
	}
	return returnbool;
}

void AC_QuadRooms::BoundaryCorners(FVector& NWOut, FVector& NEOut, FVector& SEOut, FVector& SWOut)
{
	NWOut.X = absCentre_X + half_x;
	NWOut.Y = absCentre_Y + half_y;

	NEOut.X = absCentre_X - half_x;
	NEOut.Y = NWOut.Y;

	SEOut.X = NEOut.X;
	SEOut.Y = absCentre_Y - half_y;

	SWOut.X = NWOut.X;
	SWOut.Y = SEOut.Y;

}

void AC_QuadRooms::BoundaryBounds(float& Left, float& Right, float& Top, float& Bottom)
{
	Left = centre_x - half_x;
	Right = centre_x + half_x;
	Top = centre_y + half_y;
	Bottom = centre_y - half_y;
}
