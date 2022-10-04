// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"

#include "FPSCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	RootComponent = StaticMeshComponent;
	SphereComponent->SetupAttachment(StaticMeshComponent);

	// No collision on the StaticMeshComponent
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Setting the SphereComponent to query only and only allowing it to overlap with the Pawn channel
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSObjectiveActor::OnOverlapCosmetics() const
{
	if (OverlapFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapFX, GetActorLocation());
	}
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Once our actor overlaps with another actor, we just fire our cosmetic logic
	OnOverlapCosmetics();

	if (AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor))
	{
		Character->bIsCarryingObjective = true;
		Destroy();
	}
}

