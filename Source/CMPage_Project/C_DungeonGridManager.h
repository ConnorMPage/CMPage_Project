// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DungeonTile.h"
#include "C_ProcGenAlgs.h"
#include "Math/UnrealMathUtility.h"
#include "C_DungeonGridManager.generated.h"

class AC_DungeonTile;


UCLASS()
class CMPAGE_PROJECT_API AC_DungeonGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_DungeonGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TArray<TArray<AC_DungeonTile*>> DungeonGrid;
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
		int32 DungeonSize = 25;
private:
	UFUNCTION()
		void constructGrid();
	UPROPERTY(EditAnywhere)
		float tileOffset = 200.0f;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_DungeonTile> DungeonTileClass;
	UPROPERTY()
		UC_ProcGenAlgs* procGenRefs;
};
