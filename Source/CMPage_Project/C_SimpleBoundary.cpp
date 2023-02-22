// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SimpleBoundary.h"

// Sets default values
AC_SimpleBoundary::AC_SimpleBoundary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_SimpleBoundary::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_SimpleBoundary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

