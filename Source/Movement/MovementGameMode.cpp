// Copyright Epic Games, Inc. All Rights Reserved.

#include "MovementGameMode.h"
#include "MovementCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMovementGameMode::AMovementGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/MovingSphere"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
