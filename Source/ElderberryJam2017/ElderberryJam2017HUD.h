// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ElderberryJam2017HUD.generated.h"

UCLASS()
class AElderberryJam2017HUD : public AHUD
{
	GENERATED_BODY()

public:
	AElderberryJam2017HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

