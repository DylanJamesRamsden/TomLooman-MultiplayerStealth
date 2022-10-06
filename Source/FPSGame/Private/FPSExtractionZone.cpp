// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"

#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));

	DecalComponent->SetupAttachment(RootComponent);

	BoxComponent->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	DecalComponent->DecalSize = FVector(200.0f, 200.0f, 200.0f);

	BoxComponent->bHiddenInGame = false;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	DecalComponent->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSExtractionZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor))
	{
		if (Character->bIsCarryingObjective)
		{
			if (AFPSGameMode* GM = GetWorld()->GetAuthGameMode<AFPSGameMode>())
			{
				GM->CompleteMission(Character);

				if (ObjectiveObtainedSound)
				{
					UGameplayStatics::PlaySound2D(GetWorld(), ObjectiveObtainedSound);
				}
			}
		}
		else
		{
			if (ObjectiveMissingSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), ObjectiveMissingSound);
			}
		}
	}
}

