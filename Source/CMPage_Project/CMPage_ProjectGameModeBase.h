// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_SetUpQuadTree.h"
#include "C_WorldData.h"
#include "C_GridData.h"
#include "CMPage_ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CMPAGE_PROJECT_API ACMPage_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void checkStart();
	UFUNCTION()
		void createDungeon();
	UFUNCTION()
		void spawnUnits();

	UPROPERTY()
		AC_SetUpQuadTree* quadTreeRef;
	UPROPERTY()
		AC_WorldData* worldDataRef;
	UPROPERTY()
		AC_GridData* gridDataRef;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_SetUpQuadTree> quadTreeSubClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_GridData> gridDataSubClass;
};
