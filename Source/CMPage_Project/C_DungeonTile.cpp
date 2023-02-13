// Fill out your copyright notice in the Description page of Project Settings.


#include "C_DungeonTile.h"

// Sets default values
AC_DungeonTile::AC_DungeonTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AC_DungeonTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_DungeonTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

