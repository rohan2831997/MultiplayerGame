// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "AMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AAMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:

	AAMovingPlatform();
	void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere);
	float speed = 20.0f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	void ADDActiveTrigger();
	void RemoveActiveTrigger();

	FVector GlobalStart;
	FVector GlobalEnd;

private:
	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
	
};
