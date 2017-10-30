// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ElderberryJam2017GameMode.h"
#include "ElderberryJam2017HUD.h"
#include "ElderberryJam2017Character.h"
#include "UObject/ConstructorHelpers.h"

AElderberryJam2017GameMode::AElderberryJam2017GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/MyBlueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AElderberryJam2017HUD::StaticClass();
}
