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
	bool Collides;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector WorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Tags;

	bool HasTag(FName Tag)
	{
		for (auto T : Tags)
		{
			if (T == Tag) { return true; }
		}
		return false;
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



};
