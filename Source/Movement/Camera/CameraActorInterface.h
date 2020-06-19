// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraModificationVolume.h"
#include "CameraActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCameraActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MOVEMENT_API ICameraActorInterface
{
	GENERATED_BODY()

public:
	virtual ACameraModificationVolume* GetCurrentCameraModificationVolume() = 0;

	virtual void SetCurrentCameraModificationVolume(ACameraModificationVolume* Volume) = 0;
};