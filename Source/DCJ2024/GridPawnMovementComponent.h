// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GridPawnMovementComponent.generated.h"

/**
 * 
 */


UENUM()
enum class EGridMovementState {
	Idle = 0,
	Moving,
	Turning
};

UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class DCJ2024_API UGridPawnMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:

	UGridPawnMovementComponent();

	UFUNCTION(BlueprintCallable)
	virtual void Move(float AxisValue);

	UFUNCTION(BlueprintCallable)
	virtual void Rotate(float AxisValue);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void SetMovementState(EGridMovementState NewState);

public:

	UPROPERTY(EditAnywhere, Category = Movement)
	float MoveSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float TurnSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = Testing)
	float GridSize = 100;

private:

	EGridMovementState MovementState = EGridMovementState::Idle;
	
	//Info for LERPs
	FVector StartLocation;
	FVector TargetLocation;

	FRotator StartRotation;
	FRotator TargetRotation;

	float MovementAlpha = 0.0f;

};
