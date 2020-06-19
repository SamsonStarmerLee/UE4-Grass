// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraInfo.generated.h"

/** Common camera properties for a camera. */
USTRUCT(BlueprintType)
struct FCameraInfo
{
	GENERATED_BODY()

    /** The field of view (in degrees) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
        float FOV;

    /** Distance between the camera and the view target, in cm. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
        float SpringArmLength;

    /** Compares both camera property sets for equality. */
    bool Equals(const FCameraInfo& Other) const;

    /** Whether this property set modifies the camera at all. */
    bool IsZero() const;
};

///** Distance in which the Depth of Field effect should be sharp, in unreal units (cm) */
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
//    float DepthOfFieldFocalDistance;

///** Artificial region where all content is in focus, starting after DepthOfFieldFocalDistance, in unreal units  (cm) */
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
//    float DepthOfFieldFocalRegion;

///** To define the width of the transition region next to the focal region on the near side (cm) */
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
//    float DepthOfFieldNearTransitionRegion;

///** To define the width of the transition region next to the focal region on the near side (cm) */
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
//    float DepthOfFieldFarTransitionRegion;

///** Gaussian only: Maximum size of the Depth of Field blur (in percent of the view width) (note: performance cost scales with size) */
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
//    float DepthOfFieldNearBlurSize;

///** Gaussian only: Maximum size of the Depth of Field blur (in percent of the view width) (note: performance cost scales with size) */
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
//    float DepthOfFieldFarBlurSize;