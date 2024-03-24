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

bool UDungeonCrawlerGameInstance::IsValidMovement(FIntPoint PawnCoordinate, FIntPoint& NewCoordinate, int32 Orientation, FVector& Target)
{
	FIntPoint NextCoord;

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

	//UE_LOG(LogTemp, Warning, TEXT("NextCoordinate: X-%i Y-%i"), NextCoord.X, NextCoord.Y);
	NewCoordinate = NextCoord + PawnCoordinate;
	FGridSpaceData* Data = GridSpaces.Find(NewCoordinate);
	if (Data)
	{
		UE_LOG(LogTemp, Warning, TEXT("NextTile: X:%i Y:%i"), NewCoordinate.X, NewCoordinate.Y);

		Target = Data->WorldLocation;
		return !Data->Collides;
	}
	return false;
}
