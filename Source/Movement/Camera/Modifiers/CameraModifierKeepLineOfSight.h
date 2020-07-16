// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement\Camera\ExpCameraModifier.h"
#include "CameraModifierKeepLineOfSight.generated.h"

/**
 * Uses camera "whiskers" to probe into the environment and swings
 * the camera away from obstacles before the occlude the character.
 */
UCLASS(BlueprintType, Blueprintable)
class MOVEMENT_API UCameraModifierKeepLineOfSight : public UExpCameraModifier
{
	GENERATED_BODY()
	
public:
	UCameraModifierKeepLineOfSight();

	virtual bool ProcessViewRotation(class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot) override;

	virtual bool ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV) override;

	/** How far away from the current camera angle we should look for potential obstacles. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float MaximumAngleInRadians;

	/** How precisely we should preemtively look for obstacles (the angle between whiskers). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float StepSizeInRadians;

	/** Rate at which the camera should follow the turning character, in radians per second. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float RotationSpeed;

	/** Collision channel of the query probe. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		TEnumAsByte<ECollisionChannel> LineOfSightProbeChannel;

private:
	/** Checks whether 'To' can be seen from 'From', with respect to ProbeSize and ProbeChannel. */
	bool IsInLineOfSight(const FVector& From, const FVector& To) const;

	/** Rotates InOutViewLocation and InOutViewRotation around TargetLocation by AngleRadians. */
	void RotateAroundLocation(
		const FVector& TargetLocation, FVector& InOutViewLocation, FRotator& InOutViewRotation, const float AngleInRadians);
};
