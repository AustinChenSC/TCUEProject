// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CalculateFuncsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEFPS_API UCalculateFuncsComponent : public UActorComponent
{
	GENERATED_BODY()
	UCalculateFuncsComponent();
public:	
	/** Sort Array */
	UFUNCTION(BlueprintCallable)
	TArray<int32> SortIntArray(TArray<int32> newArray);

	/** Get an amount of int data */
	UFUNCTION(BlueprintCallable)
	TArray<int32> GetSomeDataFromOldArray(int32 number, TArray<int32> oldArray);

	/** Transform seconds to minutes and seconds (returns TArray)*/
	UFUNCTION(BlueprintCallable)
	TArray<int32> TransformSecondsToMinsAndSecs(int32 seconds);

	/** Set Strings by Ints of Mapping data */
	UFUNCTION(BlueprintCallable)
	TArray<FString> SetRankingValuesByKeys(TMap<int32, FString> rankingListMap, TArray<int32> keyArray);

		
};
