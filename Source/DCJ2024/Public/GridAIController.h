// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GridAIController.generated.h"

/**
 * 
 */
class UGridPawnMovementComponent;

UCLASS()
class DCJ2024_API AGridAIController : public AAIController
{
	GENERATED_BODY()

public:

	TArray<FIntPoint> GetPathToLocation(FIntPoint Location);

public:

	UPROPERTY()
	UGridPawnMovementComponent* MovementComponent;

	
};
