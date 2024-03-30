// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GridPawnMovementComponent.generated.h"

/**
 * 
 */

class UDcjAudioGiSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementComplete);

UENUM()
enum class EGridMovementState {
	Idle = 0,
	Moving,
	Turning
};

UENUM()
enum class EGridPawnType {
	Player = 0,
	AI
};

UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class DCJ2024_API UGridPawnMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:

	UGridPawnMovementComponent();

	UFUNCTION(BlueprintCallable)
	virtual void Move(FIntPoint AxisValue);

	UFUNCTION(BlueprintCallable)
	virtual void Rotate(float AxisValue);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerStart();

	UFUNCTION(BlueprintCallable)
	void SetCoordinates(FIntPoint New);

	UFUNCTION(BlueprintCallable)
	FIntPoint GetCoordinates();

protected:

	virtual void BeginPlay() override;

	virtual void SetMovementState(EGridMovementState NewState);
	void AddOrientation(bool Right);


public:

	UPROPERTY(EditAnywhere, Category = Movement)
	float MoveSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float TurnSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float GridSize = 100;

	UPROPERTY(EditAnywhere, Category = Movement)
	EGridPawnType PawnType;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnMovementComplete MoveComplete;

protected:

	FIntPoint Coordinates;
	int32 Orientation = 0;

private:

	EGridMovementState MovementState = EGridMovementState::Idle;
	
	//Info for LERPs
	FVector StartLocation;
	FVector TargetLocation;

	FRotator StartRotation;
	FRotator TargetRotation;

	float MovementAlpha = 0.0f;

	UDcjAudioGiSubsystem* DcjAudioGiSubsystem;
};
