// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "parkGameMode.h"
#include "parkCharacter.h"
#include "UObject/ConstructorHelpers.h"

AparkGameMode::AparkGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
