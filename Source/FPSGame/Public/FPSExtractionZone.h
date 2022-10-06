// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* DecalComponent;

	UPROPERTY(EditAnywhere)
	USoundBase* ObjectiveMissingSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ObjectiveObtainedSound;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
