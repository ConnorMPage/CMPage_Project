// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_PlayerCharacter.h"
#include "CMPage_ProjectGameModeBase.h"
#include "GameFramework/Actor.h"
#include "C_WorldData.generated.h"

UCLASS()
class CMPAGE_PROJECT_API AC_WorldData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_WorldData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY()
		AC_PlayerCharacter* enemyRef;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_PlayerCharacter> enemyClass;
	UPROPERTY()
		ACMPage_ProjectGameModeBase* gameModeRef;
	UPROPERTY()
		int loopStart = 0;
	UFUNCTION()
		void SpawnUnits();
};
