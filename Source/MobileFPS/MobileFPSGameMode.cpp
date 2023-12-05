// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileFPSGameMode.h"
#include "MobileFPSCharacter.h"
#include <algorithm>
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
	if (newArray.IsEmpty()) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("-----------newArray Is Empty!----------"));
	}
	
	newArray.Sort([](int32 A, int32 B)->bool {return A > B; });
	return newArray;
}

TArray<int32> AMobileFPSGameMode::GetSomeDataFromOldArray(int32 number,  TArray<int32> oldArray)
{
	TArray<int32> newArray;
	if (oldArray.Num() < number) {
		newArray = oldArray;
	}
	else {
		for (int32 index = 0; index <number; index++) {
			newArray.Push(oldArray[index]);
		}
	}
	return newArray;
}

TArray<int32> AMobileFPSGameMode::TransformSecondsToMinsAndSecs(int32 seconds)
{
	TArray<int32> timeArray{ seconds / 60, seconds % 60 };
	return timeArray;
}

TArray<FString> AMobileFPSGameMode::SetRankingValuesByKeys(TMap<int32, FString> rankingListMap, TArray<int32> keyArray)
{
	TArray<FString> valueArray;
	if (rankingListMap.IsEmpty()) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("-----------rankingListMap Is Empty!----------"));
	}
	for (int32 index = 0; index < keyArray.Num();index++) {
		valueArray.Push(*rankingListMap.Find(keyArray[index]));
	}
	return valueArray;
}
