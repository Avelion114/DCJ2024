// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCrawlerGameInstance.h"

FIntPoint UDungeonCrawlerGameInstance::FindPlayerStart(bool& Found)
{

	for (auto Pair : GridSpaces)
	{
		if (Pair.Value.HasTag("Start"))
		{
			Found = true;
			return Pair.Key;
		}
	}
	Found = false;
	return FIntPoint{ -1,-1 };
}

bool UDungeonCrawlerGameInstance::IsValidMovement(FIntPoint PawnCoordinate, FIntPoint& NewCoordinate, FIntPoint Direction, int32 Orientation, FVector& Target)
{
	FIntPoint NextCoord = { 0,0 };

	switch (Orientation)
	{
	case 0:
		NextCoord = { 1, 0 };
		break;
	case 1:
		NextCoord = { 0, 1 };
		break;
	case 2:
		NextCoord = { -1, 0 };
		break;
	case 3:
		NextCoord = { 0, -1 };
		break;
	}

	if (Direction.X == 0)
	{
		if (NextCoord.X == 0)
		{
			Swap(Direction.X, Direction.Y);
			NextCoord = Direction * -NextCoord.Y;
		}
		else
		{
			NextCoord = Direction * NextCoord.X;
		}
	}
	else { NextCoord *= Direction.X; }

	UE_LOG(LogTemp, Warning, TEXT("NextCoordinate: X-%i Y-%i"), NextCoord.X, NextCoord.Y);
	NewCoordinate = NextCoord + PawnCoordinate;
	FGridSpaceData* Data = GridSpaces.Find(NewCoordinate);
	if (Data)
	{
		Target = Data->WorldLocation;
		return true;
	}
	return false;
}

void UDungeonCrawlerGameInstance::ResetCostData()
{
	TArray<FGridSpaceData> Values;
	GridSpaces.GenerateValueArray(Values);
	for (auto I : Values)
	{
		I.ResetCost();
	}
}
