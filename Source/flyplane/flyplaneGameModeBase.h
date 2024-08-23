// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "flyplaneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLYPLANE_API AflyplaneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Points;
};
