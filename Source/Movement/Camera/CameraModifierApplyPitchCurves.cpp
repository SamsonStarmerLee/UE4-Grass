// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraModifierApplyPitchCurves.h"
#include "Camera/CameraTypes.h"
#include "ExpPlayerCameraManager.h"

bool UCameraModifierApplyPitchCurves::ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV)
{
	Super::ModifyCamera(DeltaTime, InOutPOV);

	AExpPlayerCameraManager* cameraManager = Cast<AExpPlayerCameraManager>(CameraOwner);
	if (!IsValid(cameraManager))
	{
		return false;
	}

	// Get camera location and rotation.
	const FVector cameraLocation = InOutPOV.Location;
	const FRotator cameraRotation = InOutPOV.Rotation;

	// Apply curves.
	const float pitchToDistance = IsValid(PitchToDistanceCurve) ? PitchToDistanceCurve->GetFloatValue(cameraRotation.Pitch) : 0.0f;
	const float pitchToFov = IsValid(PitchToFOVCurve) ? PitchToFOVCurve->GetFloatValue(cameraRotation.Pitch) : 0.0f;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(pitchToFov));

	// Drive camera away based on evaluated curve.
	const FVector desiredLocation =
		cameraLocation - cameraRotation.RotateVector(FVector::ForwardVector) * pitchToDistance;

	FVector newLocation;
	FCollisionQueryParams queryParams(SCENE_QUERY_STAT(SpringArm), false, GetViewTarget());
	FHitResult result;

	// Sweep toward the newly calculated position to check for obstacles.
	GetWorld()->SweepSingleByChannel(
		result, 
		GetViewTarget()->GetActorLocation() + FVector::UpVector * 50.0f,
		desiredLocation,
		FQuat::Identity,
		cameraManager->LineOfSightProbeChannel,
		FCollisionShape::MakeSphere(cameraManager->LineOfSightProbeSize),
		queryParams);

	newLocation = result.bBlockingHit ? result.Location : desiredLocation;
	InOutPOV.Location = newLocation;
	InOutPOV.FOV += pitchToFov;
	return false;
}