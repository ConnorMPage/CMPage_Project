// Fill out your copyright notice in the Description page of Project Settings.

#include "C_QuadRooms.h"
#include "C_WorldData.h"

// Sets default values
AC_WorldData::AC_WorldData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_WorldData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_WorldData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AC_WorldData::SpawnUnits()
{
	
}

