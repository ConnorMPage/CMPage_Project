// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr)//checks if connected to ai controller
	{
		return EBTNodeResult::Failed;// if its not then the task fails
	}

	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();// gets the AI pawn
	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//finds the player pawn

	FHitResult Hit;//holds all the hit data such as who was hit

	FVector TraceStartLoc = AIActor->GetActorLocation() + AddHeightToTrace;//increase the height of the actors location to avoid hitting itself

	bool bTargetHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStartLoc, PlayerPawn->GetActorLocation(), ECC_Visibility);//fires raytrace
	if (bTargetHit)//if a target is hit
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *Hit.GetActor()->GetName());//outputs the name of object hit by raytrace

		UGameplayStatics::ApplyDamage(
			Hit.GetActor(), //actor that will be damaged
			WeaponDamage, //the base damage to apply
			AIActor->GetInstigatorController(), //controller that caused the damage
			AIActor, //Actor that actually caused the damage
			UDamageType::StaticClass()); //class that describes the damage that was done
	}
	return EBTNodeResult::Succeeded;//marks the task as successful
}
