// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AxPlayerSource.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DCJ2024_API UAxPlayerSource : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAxPlayerSource();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//Sounds for heartbeat and breath
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* PlayerBodySounds;

private:
	AActor* AsPlayerCharacter;
		
};
