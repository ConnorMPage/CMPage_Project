// Fill out your copyright notice in the Description page of Project Settings.


#include "C_WallCollision.h"

// Sets default values
AC_WallCollision::AC_WallCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_WallCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_WallCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

