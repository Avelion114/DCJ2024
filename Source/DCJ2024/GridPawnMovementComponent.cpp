// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPawnMovementComponent.h"
#include "GameFramework/Controller.h"

UGridPawnMovementComponent::UGridPawnMovementComponent()
{

}

void UGridPawnMovementComponent::Move(float AxisValue)
{

	if (MovementState == EGridMovementState::Idle && AxisValue != 0.0f)
	{

		//Get grid system for next location and set target location


		//
		StartLocation = PawnOwner->GetActorLocation();
		TargetLocation = StartLocation + (PawnOwner->GetActorForwardVector() * AxisValue) * GridSize;

		SetMovementState(EGridMovementState::Moving);
	}
}

void UGridPawnMovementComponent::Rotate(float AxisValue)
{
	

	if (MovementState == EGridMovementState::Idle && AxisValue != 0.0f)
	{
		StartRotation = PawnOwner->GetControlRotation();
		TargetRotation = StartRotation;
		TargetRotation.Yaw += float(90.0 * AxisValue);

		SetMovementState(EGridMovementState::Turning);
	}
}

void UGridPawnMovementComponent::SetMovementState(EGridMovementState NewState)
{
	switch (NewState)
	{
	case EGridMovementState::Idle:
		MovementAlpha = 0.0f;
		break;
	}
	MovementState = NewState;
}

void UGridPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	switch (MovementState)
	{
	case EGridMovementState::Idle:
		break;
	case EGridMovementState::Moving:
		MovementAlpha = FMath::Clamp((MovementAlpha + (DeltaTime * MoveSpeed)), 0.0f, 1.0f );

		PawnOwner->SetActorLocation(FMath::Lerp(StartLocation, TargetLocation, MovementAlpha));
		if (MovementAlpha == 1.0)
		{
			SetMovementState(EGridMovementState::Idle);
		}
		break;
	case EGridMovementState::Turning:
		MovementAlpha = FMath::Clamp((MovementAlpha + (DeltaTime * TurnSpeed)), 0.0f, 1.0f);
		PawnOwner->GetController()->SetControlRotation(FMath::LerpRange(StartRotation, TargetRotation, MovementAlpha));
		if (MovementAlpha == 1.0)
		{
			SetMovementState(EGridMovementState::Idle);
		}
		break;
	}
}
