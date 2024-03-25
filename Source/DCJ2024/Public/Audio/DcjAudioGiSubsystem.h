// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DcjAudioGiSubsystem.generated.h"


//USTRUCT(BlueprintType)
//FAxCurrentLevel{
//
//}

/**
 * Audio manager subsystem for handling music, ambience
 */
UCLASS()
class DCJ2024_API UDcjAudioGiSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	//Used to determine when the player is in the menu or not
	UPROPERTY(BlueprintReadWrite, Category = "Admin")
	bool bIsMainMenu = true;
	
};
