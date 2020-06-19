// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ExpPlayerCameraManager.generated.h"

/**
 * Defines the final view properties for the camera.
 */
UCLASS()
class MOVEMENT_API AExpPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AExpPlayerCameraManager();

	/** Radius of the query probe for verifying line of sight between camera and view target (in cm). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float LineOfSightProbeSize;

	/** Collision channel of the query probe for verifying line of sight between camera nad view target. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TEnumAsByte<ECollisionChannel> LineOfSightProbeChannel;

protected:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
