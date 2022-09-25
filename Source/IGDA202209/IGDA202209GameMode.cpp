// Copyright Epic Games, Inc. All Rights Reserved.

#include "IGDA202209GameMode.h"
#include "IGDA202209Character.h"
#include "UObject/ConstructorHelpers.h"

AIGDA202209GameMode::AIGDA202209GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
