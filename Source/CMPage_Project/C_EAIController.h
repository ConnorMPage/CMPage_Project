// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "C_EAIController.generated.h"

/**
 * 
 */
UCLASS()
class CMPAGE_PROJECT_API AC_EAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere)
		APawn* PlayerPawn;//creates player pawn object
	UPROPERTY(EditAnywhere)
		TArray<AActor*> Waypoints;//create waypoint array

	UFUNCTION()
		AActor* ChooseWaypoint();//choses a waypoint at random

	UPROPERTY(VisibleAnywhere)
		UBehaviorTree* EnemyMovementTree;// attaches the behavior tree to controller

	UFUNCTION()
		bool CheckIfInFront(AActor* CheckActor);//runs a dot product to check if playe ris in front of ai
};
