// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AI_PatrolPoint.h"
#include "MobileFPSGameMode.generated.h"


UCLASS(minimalapi)
class AMobileFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMobileFPSGameMode();

	/** Sort Array */
	UFUNCTION(BlueprintCallable)
	TArray<int32> SortIntArray(TArray<int32> newArray);

	/** Get an amount of int data */
	UFUNCTION(BlueprintCallable)
	TArray<int32> GetSomeDataFromOldArray(int32 number, TArray<int32> oldArray);

	/** Transform seconds to minutes and seconds (returns TArray)*/
	UFUNCTION(BlueprintCallable)
	TArray<int32> TransformSecondsToMinsAndSecs(int32 seconds);

protected:

	/** Set Strings by Ints of Mapping data */
	UFUNCTION(BlueprintCallable)
	TArray<FString> SetRankingValuesByKeys(TMap<int32, FString> rankingListMap, TArray<int32> keyArray);

};



