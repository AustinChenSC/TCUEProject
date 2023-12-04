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

protected:
	/** Sort Array */
	UFUNCTION(BlueprintCallable)
	TArray<int32> SortIntArray(TArray<int32> newArray);

	/** Get an amount of int data */
	UFUNCTION(BlueprintCallable)
	void GetSomeDataFromOldArray(int32 number, TArray<int32>& newArray, TArray<int32> oldArray);

	/** Set Strings by Ints of Mapping data */
	UFUNCTION(BlueprintCallable)
	void SetRankingValuesByKeys(TMap<int32, FString> rankingListMap, TArray<int32> keyArray, TArray<FString>& valueArray);
};



