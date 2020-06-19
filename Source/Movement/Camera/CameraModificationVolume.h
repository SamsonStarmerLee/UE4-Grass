// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "CameraInfo.h"
#include "CameraModificationVolume.generated.h"

/**
 * Volume that modifies the camera of entering players.
 */
UCLASS()
class MOVEMENT_API ACameraModificationVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:
	ACameraModificationVolume();

	/** Sets the current modification volume. */
	virtual void NotifyActorBeginOverlap(AActor* Other) override;

	/** Resets the current applied camera modification. */
	virtual void NotifyActorEndOverlap(AActor* Other) override;

	/** Time until the modifications are fully applied, in seconds. */
	UPROPERTY(Category = CameraModifiers, BlueprintReadWrite, EditAnywhere)
	float TransitionTime;

	/** Value to add to the properties of any player camera entering the volume. */
	FCameraInfo Modifiers;
};
