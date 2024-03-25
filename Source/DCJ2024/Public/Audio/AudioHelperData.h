#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


//Include Me :)
#include "AudioHelperData.generated.h"

//used for sending player specific messages
USTRUCT(BlueprintType)
struct FAxSendMsg_PlyrSfx
{
    GENERATED_BODY()

    // Struct members
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ax Send Gpm Player Sfx")
    int32 Int = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ax Send Gpm Player Sfx")
    float Float = 0.f;

};