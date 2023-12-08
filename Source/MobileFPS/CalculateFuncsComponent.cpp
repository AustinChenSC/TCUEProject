// Fill out your copyright notice in the Description page of Project Settings.


#include "CalculateFuncsComponent.h"

// Sets default values for this component's properties
UCalculateFuncsComponent::UCalculateFuncsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


TArray<int32> UCalculateFuncsComponent::SortIntArray(TArray<int32> newArray)
{
	if (newArray.IsEmpty()) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("-----------newArray Is Empty!----------"));
	}

	newArray.Sort([](int32 A, int32 B)->bool {return A > B; });
	return newArray;
}

TArray<int32> UCalculateFuncsComponent::GetSomeDataFromOldArray(int32 number, TArray<int32> oldArray)
{
	TArray<int32> newArray;
	if (oldArray.Num() < number) {
		newArray = oldArray;
	}
	else {
		for (int32 index = 0; index < number; index++) {
			newArray.Push(oldArray[index]);
		}
	}
	return newArray;
}

TArray<int32> UCalculateFuncsComponent::TransformSecondsToMinsAndSecs(int32 seconds)
{
	TArray<int32> timeArray{ seconds / 60, seconds % 60 };
	return timeArray;
}

TArray<FString> UCalculateFuncsComponent::SetRankingValuesByKeys(TMap<int32, FString> rankingListMap, TArray<int32> keyArray)
{
	TArray<FString> valueArray;
	if (rankingListMap.IsEmpty()) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("-----------rankingListMap Is Empty!----------"));
	}
	for (int32 index = 0; index < keyArray.Num(); index++) {
		valueArray.Push(*rankingListMap.Find(keyArray[index]));
	}
	return valueArray;
}

