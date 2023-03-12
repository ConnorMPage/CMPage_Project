// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuadRooms2.h"

// Sets default values
AC_QuadRooms2::AC_QuadRooms2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_QuadRooms2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_QuadRooms2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_QuadRooms2::initBounds(float XCentre, float YCentre, float XHalf, float YHalf)
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
}

bool AC_QuadRooms2::containsPoint(float X, float Y)
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

void AC_QuadRooms2::BoundaryCorners(FVector& NWOut, FVector& NEOut, FVector& SEOut, FVector& SWOut)
{
	NWOut.X = centre_x + half_x;
	NWOut.Y = centre_y + half_y;

	NEOut.X = centre_x - half_x;
	NEOut.Y = NWOut.Y;

	SEOut.X = NEOut.X;
	SEOut.Y = centre_y - half_y;

	SWOut.X = NWOut.X;
	SWOut.Y = SEOut.Y;
}

void AC_QuadRooms2::BoundaryBounds(float& Left, float& Right, float& Top, float& Bottom)
{
	Left = centre_x - half_x;
	Right = centre_x + half_x;
	Top = centre_y + half_y;
	Bottom = centre_y - half_y;
}

void AC_QuadRooms2::AssignRealRoom(AC_QuadRooms* quadIn)
{
	RealRoom = quadIn;
}

AC_QuadRooms* AC_QuadRooms2::returnRealRooms()
{
	return RealRoom;
}

AC_QuadRooms* AC_QuadRooms2::returnParent()
{
	return RealRoom;
}

