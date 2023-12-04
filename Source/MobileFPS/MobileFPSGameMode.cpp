// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileFPSGameMode.h"
#include "MobileFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMobileFPSGameMode::AMobileFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/Characters/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;



}

TArray<int32> AMobileFPSGameMode::SortIntArray(TArray<int32> newArray)
{
	newArray.Sort();
	return TArray<int32>(newArray);
}

void AMobileFPSGameMode::GetSomeDataFromOldArray(int32 number, TArray<int32>& newArray, TArray<int32> oldArray)
{
	if (oldArray.Num() < number) {
		newArray = oldArray;
	}
	else {
		for (int32 index = 0; index <number; index++) {
			newArray.Push(oldArray[index]);
		}
	}
}

void AMobileFPSGameMode::SetRankingValuesByKeys(TMap<int32, FString> rankingListMap, TArray<int32> keyArray, TArray<FString>& valueArray)
{
	for (int32 index = 0; index < keyArray.Num();index++) {
		valueArray.Push(*rankingListMap.Find(keyArray[index]));
	}
}
