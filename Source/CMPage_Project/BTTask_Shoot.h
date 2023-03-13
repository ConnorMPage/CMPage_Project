// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class CMPAGE_PROJECT_API UBTTask_Shoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;//executes task
private:
	UPROPERTY(VisibleAnywhere)
		float WeaponDamage = 25.0f;//amound of damage for apply damage
	UPROPERTY(VisibleAnywhere)
		FVector AddHeightToTrace = FVector(0.0f, 10.0f, 0.0f);
};
