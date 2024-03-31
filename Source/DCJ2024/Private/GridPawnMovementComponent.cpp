// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPawnMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Audio/AudioHelperData.h"
#include "DungeonCrawlerGameInstance.h"

UGridPawnMovementComponent::UGridPawnMovementComponent()
{

}

bool UGridPawnMovementComponent::Move(FIntPoint AxisValue)
{

	if (MovementState == EGridMovementState::Idle && AxisValue.Size() != 0.0f)
	{

		//Get grid system for next location and set target location

		UDungeonCrawlerGameInstance* GI = Cast<UDungeonCrawlerGameInstance>(GetWorld()->GetGameInstance());
		FIntPoint TileCoord;
		if (GI->IsValidMovement(Coordinates, TileCoord, AxisValue, Orientation, TargetLocation))
		{
			StartLocation = PawnOwner->GetActorLocation();
			Coordinates = TileCoord;
			SetMovementState(EGridMovementState::Moving);
			return true;
		}
		UE_LOG(LogTemp, Warning, TEXT("Invalid Movement"));
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Movement State is not Idle"));
	return false;

}

void UGridPawnMovementComponent::Rotate(float AxisValue)
{
	if (MovementState == EGridMovementState::Idle && AxisValue != 0.0f)
	{
		StartRotation = PawnOwner->GetControlRotation();
		TargetRotation = StartRotation;
		TargetRotation.Yaw += float(90.0 * AxisValue);
		AddOrientation(AxisValue > 0);
		SetMovementState(EGridMovementState::Turning);
	}
}

void UGridPawnMovementComponent::SetPlayerStart()
{
	if (PawnType == EGridPawnType::Player)
	{
		UDungeonCrawlerGameInstance* GI = Cast<UDungeonCrawlerGameInstance>(GetWorld()->GetGameInstance());
		bool Found = false;
		Coordinates = GI->FindPlayerStart(Found);
		UE_LOG(LogTemp, Warning, TEXT("Player Start: X-%i Y-%i"), Coordinates.X, Coordinates.Y);
		if (!Found) { UE_LOG(LogTemp, Error, TEXT("Player Start not found!")); }
		GetPawnOwner()->SetActorLocation(GI->GridSpaces.Find(Coordinates)->WorldLocation);
		GetPawnOwner()->GetController()->SetControlRotation({ 0.0f,0.0f,0.0f });
	}
}

void UGridPawnMovementComponent::SetCoordinates(FIntPoint New)
{
	Coordinates = New;
}

FIntPoint UGridPawnMovementComponent::GetCoordinates()
{
	return Coordinates;
}


void UGridPawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	UDungeonCrawlerGameInstance* GI = Cast<UDungeonCrawlerGameInstance>(GetWorld()->GetGameInstance());
	GI->StartupDelegate.AddDynamic(this, &UGridPawnMovementComponent::SetPlayerStart);
}

void UGridPawnMovementComponent::SetMovementState(EGridMovementState NewState)
{
	//UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	//FAxSendMsg_PlyrSfx OutgoingMessage;
	//FGameplayTag ChannelTag_Moving = FGameplayTag::RequestGameplayTag("GPM.Sfx.Plyr.Moved");
	//FGameplayTag ChannelTag_Turning = FGameplayTag::RequestGameplayTag("GPM.Sfx.Plyr.Turned");

	MovementState = NewState;
	switch (NewState)
	{
	case EGridMovementState::Idle:
		MovementAlpha = 0.0f;
		break;
	case EGridMovementState::Moving:
		//send message to audio that you have moved to a new grid
		//MessageSubsystem.BroadcastMessage(ChannelTag_Moving, OutgoingMessage);
		break;
	case EGridMovementState::Turning:
		//send message to audio that you have turned
		//MessageSubsystem.BroadcastMessage(ChannelTag_Turning, OutgoingMessage);
		break;
	}
	
}

void UGridPawnMovementComponent::AddOrientation(bool Right)
{
	Orientation += Right ? 1 : -1;
	UE_LOG(LogTemp, Warning, TEXT("Orientation: %i"), Orientation);
	if (Orientation > 3) { Orientation = 0; return; }
	if (Orientation < 0) { Orientation = 3; return; }


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
			MoveComplete.Broadcast();
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
