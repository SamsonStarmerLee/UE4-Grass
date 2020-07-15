// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "CameraModifierApplyPitchCurves.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENT_API UCameraModifierApplyPitchCurves : public UCameraModifier
{
	GENERATED_BODY()

public:
	virtual bool ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV) override;

private:
	/** Curve to convert changes in pitch to changes in camera distance. */
	UPROPERTY(Category = Camera, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* PitchToDistanceCurve;

	/** Curve to convert changes in pitch to changes in field of view. */
	UPROPERTY(Category = Camera, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* PitchToFOVCurve;
	
};
