// Fill out your copyright notice in the Description page of Project Settings.

#include "Movement\Camera\ExpPlayerCameraManager.h"
#include "CameraModifierKeepLineOfSight.h"

UCameraModifierKeepLineOfSight::UCameraModifierKeepLineOfSight()
    : Super()
{
    MaximumAngleInRadians = PI / 2;
    StepSizeInRadians = 0.1f;
    RotationSpeed = 1.0f;
    LineOfSightProbeChannel = ECC_Camera;
}

bool UCameraModifierKeepLineOfSight::ProcessViewRotation(
    class AActor* ViewTarget, 
    float DeltaTime,
    FRotator& OutViewRotation, 
    FRotator& OutDeltaRot)
{
    Super::ProcessViewRotation(ViewTarget, DeltaTime, OutViewRotation, OutDeltaRot);

    if (PlayerHasRecentlyChangedCamera())
    {
        return false;
    }

    const FVector desiredLocation = CameraOwner->GetCameraLocation();
    const FRotator desiredRotation = CameraOwner->GetCameraRotation();

    const FVector targetLocation = GetViewTarget()->GetActorLocation() + FVector::UpVector * 50.0f;

    float desiredAngleRads = 0.0f;
    float checkAngleRads = 0.0f;

    // Check from the left. Start very close to the actual camera angle:
    // This is the most severe case, in which we might need to make a big swing away.
    checkAngleRads = -StepSizeInRadians;

    while (checkAngleRads >= -MaximumAngleInRadians)
    {
        FVector testLocation = desiredLocation;
        FRotator testRotation = desiredRotation;

        RotateAroundLocation(targetLocation, testLocation, testRotation, checkAngleRads);

        // Check if LOS blocked.
        if (!IsInLineOfSight(targetLocation, testLocation))
        {
            // We found an obstacle for this angle.
            // The smaller the absolute value of CheckAngleInRadians,
            // the closer the obstacle, and the further we need to swing away.
            desiredAngleRads += checkAngleRads + MaximumAngleInRadians;
            break;
        }

        // Look further.
        checkAngleRads -= StepSizeInRadians;
    }

    // Check from the right
    checkAngleRads = StepSizeInRadians;

    while (checkAngleRads <= MaximumAngleInRadians)
    {
        FVector testLocation = desiredLocation;
        FRotator testRotation = desiredRotation;

        RotateAroundLocation(targetLocation, testLocation, testRotation, checkAngleRads);

        // Check if LOS is blocked.
        if (!IsInLineOfSight(targetLocation, testLocation))
        {
            desiredAngleRads += checkAngleRads - MaximumAngleInRadians;
            break;
        }

        // Look further.
        checkAngleRads += StepSizeInRadians;
    }

    // Apply any rotation.
    const float appliedAngleInRadians =
        FMath::Clamp(desiredAngleRads, -RotationSpeed * DeltaTime, RotationSpeed * DeltaTime);

    OutDeltaRot.Yaw += FMath::RadiansToDegrees(appliedAngleInRadians);

    return false;
}

bool UCameraModifierKeepLineOfSight::ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV)
{
    Super::ModifyCamera(DeltaTime, InOutPOV);
    return false;
}

bool UCameraModifierKeepLineOfSight::IsInLineOfSight(const FVector& From, const FVector& To) const
{
    UWorld* world = GetWorld();
    if (!IsValid(world))
    {
        return false;
    }

    AExpPlayerCameraManager* cameraManager = Cast<AExpPlayerCameraManager>(CameraOwner);
    if (!IsValid(cameraManager))
    {
        return false;
    }

    FCollisionQueryParams queryParams(SCENE_QUERY_STAT(SpringArm), false, GetViewTarget());
    FHitResult result;
    
    world->SweepSingleByChannel(
        result, 
        From, 
        To, 
        FQuat::Identity, LineOfSightProbeChannel,
        FCollisionShape::MakeSphere(cameraManager->LineOfSightProbeSize), 
        queryParams);

    return !result.bBlockingHit;
}

void UCameraModifierKeepLineOfSight::RotateAroundLocation(
    const FVector& TargetLocation, 
    FVector& InOutViewLocation, 
    FRotator& InOutViewRotation, 
    const float AngleInRadians)
{
    // Add angle.
    FRotator newRotation = InOutViewRotation;
    newRotation.Yaw += FMath::RadiansToDegrees(AngleInRadians);
    InOutViewRotation = newRotation;

    // Rotate test location around pawn.
    FVector newLocation = InOutViewLocation;

    const float angleSin = FMath::Sin(AngleInRadians);
    const float angleCos = FMath::Cos(AngleInRadians);

    // Translate point to origin.
    newLocation.X -= TargetLocation.X;
    newLocation.Y -= TargetLocation.Y;

    // Rotate point
    const float rotatedX = newLocation.X * angleCos - newLocation.Y * angleSin;
    const float rotatedY = newLocation.X * angleSin + newLocation.Y * angleCos;

    // Translate point back.
    newLocation.X = rotatedX + TargetLocation.X;
    newLocation.Y = rotatedY + TargetLocation.Y;    

    InOutViewLocation = newLocation;
}
