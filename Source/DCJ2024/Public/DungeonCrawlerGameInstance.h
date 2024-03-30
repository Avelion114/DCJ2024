// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DungeonCrawlerGameInstance.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartUp);

USTRUCT(BlueprintType)
struct FGridSpaceData
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector WorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Tags;


	int32 GCost = 0;
	int32 HCost = 0;

	FIntPoint Parent = { -1,-1 };

	bool HasTag(FName Tag)
	{
		for (auto T : Tags)
		{
			if (T == Tag) { return true; }
		}
		return false;
	}

	int32 GetFCost() { return GCost + HCost; }

	void ResetCost()
	{
		GCost = 0;
		HCost = 0;
	}

	bool operator< (FGridSpaceData B)
	{
		if (GetFCost() == B.GetFCost())
		{
			return HCost < B.HCost;
		}
		return GetFCost() < B.GetFCost();
	}
};


UCLASS()
class DCJ2024_API UDungeonCrawlerGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	FIntPoint FindPlayerStart(bool& Found);

	UFUNCTION(BlueprintCallable)
	bool IsValidMovement(FIntPoint PawnCoordinate, FIntPoint& NewCoordinate, FIntPoint Direction, int32 Orientation, FVector& Target);

public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnStartUp StartupDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FIntPoint, FGridSpaceData> GridSpaces;

	void ResetCostData();



};
