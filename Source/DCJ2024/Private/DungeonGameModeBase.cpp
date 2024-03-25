// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameModeBase.h"

void ADungeonGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{

	Super::InitGame(MapName, Options, ErrorMessage);

	InitGameDelegate.Broadcast();
}
