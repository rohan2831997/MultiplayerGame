// Fill out your copyright notice in the Description page of Project Settings.


#include "AMovingPlatform.h"

AAMovingPlatform::AAMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AAMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStart = GetActorLocation();
	GlobalEnd = GetTransform().TransformPosition(TargetLocation);
}

void AAMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
			float JourneyLength = (GlobalEnd - GlobalStart).Size();
			float JourneyCovered = (GlobalStart - Location).Size();

			if (JourneyLength < +JourneyCovered)
			{
				FVector temp = GlobalStart;
				GlobalStart = GlobalEnd;
				GlobalEnd = temp;
			}

			FVector Direction = (GlobalEnd - GlobalStart).GetSafeNormal();

			Location += speed * DeltaTime * Direction;
			SetActorLocation(Location);
		}
	}
}

void AAMovingPlatform::ADDActiveTrigger()
{
	ActiveTriggers++;
}

void AAMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0) ActiveTriggers--;
}
