// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController()))
		{
			if (SpectatorViewpointClass)
			{
				TArray<AActor*> ReturnedSpectatorViewpoints;
				UGameplayStatics::GetAllActorsOfClass(this, SpectatorViewpointClass, ReturnedSpectatorViewpoints);

				// Changes the instigator player's view target if one is found
				if (ReturnedSpectatorViewpoints.Num() > 0)
				{
					AActor* NewViewTarget = ReturnedSpectatorViewpoints[0];
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("SpectatorViewpointClass is a nullptr. Please update FPSGameMode with valid subclass. Cannot change spectating view target!"))
			}
		}
	}

	OnMissionCompleted(InstigatorPawn);
}
