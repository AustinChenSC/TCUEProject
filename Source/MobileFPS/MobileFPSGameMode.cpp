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
