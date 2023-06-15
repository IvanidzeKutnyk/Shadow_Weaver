// Copyright Epic Games, Inc. All Rights Reserved.

#include "Shadow_WeaverGameMode.h"
#include "Shadow_WeaverCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShadow_WeaverGameMode::AShadow_WeaverGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
