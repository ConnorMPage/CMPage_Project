// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DungeonTile.generated.h"

UCLASS()
class CMPAGE_PROJECT_API AC_DungeonTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_DungeonTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleInstanceOnly)
		FIntPoint TileIndex;
private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TileMesh;
};
