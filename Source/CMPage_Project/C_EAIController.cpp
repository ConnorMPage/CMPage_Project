// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EAIController.h"

void AC_EAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//sets playerpawnn object to be the player pawn

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);//gets all the waypoints and adds to array

	if (EnemyMovementTree != nullptr)//checks if the tree is nullptr
	{
		RunBehaviorTree(EnemyMovementTree);//runs behaviour tree
	}
}

void AC_EAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetBlackboardComponent()->SetValueAsVector(TEXT("WayPointLocation"), ChooseWaypoint()->GetActorLocation());//sets a new waypoint to go to each tick
	if (LineOfSightTo(PlayerPawn) && CheckIfInFront(PlayerPawn))//if the player is in front
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());//sets the player location
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}


AActor* AC_EAIController::ChooseWaypoint()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);//randomly selects a number within array size
	return Waypoints[index];//sets the random nnumber as the waypoint to go to
}

bool AC_EAIController::CheckIfInFront(AActor* CheckActor)
{
	AActor* AIPawn = GetPawn();//gets ai pawn
	FVector AIForwardVector = AIPawn->GetActorForwardVector();//finds forward vector
	FVector PlayerPositionVector = CheckActor->GetActorLocation();//gets player location
	FVector AIPositionVector = AIPawn->GetActorLocation();//gets actor location
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;//checks distance between th etwo
	AIToPlayerVector.Normalize();//normalises it
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);//complets th edot product
	if (DirectionDotProduct > 0)//if facing player
	{
		return true;//facing player true
	}
	else
	{
		return false;//facing player false
	}
}
