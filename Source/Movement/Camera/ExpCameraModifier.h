// Fill out your copyright notice in the Description page of Project Settings.

// All based on: https://github.com/DaedalicEntertainment/third-person-camera/blob/e77b7f4847d95f675ab5e339417386a8a3583680/Source/ThirdPersonCamera/Camera/HoatCameraModifier.h

#pragma once

#include "CoreMinimal.h"
#include "CameraInfo.h"
#include "Camera/CameraModifier.h"
#include "ExpCameraModifier.generated.h"

/** 
* An expanded version of UCameraModifier, for applying effects over time. 
* Is designed to handle the player overriding the modification. 
**/
UCLASS(BlueprintType, Blueprintable)
class MOVEMENT_API UExpCameraModifier : public UCameraModifier
{
	GENERATED_BODY()

public:
	UExpCameraModifier();

	virtual bool ProcessViewRotation(class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot) override;

	/** The camera modifiers currently being applied. */
	FCameraInfo GetCurrentModifiers() const;

	/** The camera modifiers currently being transitioned to. */
	FCameraInfo GetTargetModifiers() const;

	/** Player input overrides automatic camera modidication for this timeframe, in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CooldownAfterInput;

protected:
	/**
	* Applies the specified camera properties, starting a transition if required.
	* 
	* @param CameraInfo Camera properties to apply. Will start a new transition if the specified properties are different from the previous call. May be zero, in which case we'll be transitioning back.
	* @param TransitionTime Time until complete transition, in seconds. You may pass zero if the transition started in an earlier frame.
	* @param InOutPOV Camera point of view being modified.
	* @param DeltaTime Time since the last application of this modifier, in seconds.
	*/
	void ApplyTransition(const FCameraInfo CameraInfo, const float TransitionTime, struct FMinimalViewInfo& InOutPOV, const float DeltaTime);

	/** Whether the player has recently changed the camera.*/
	bool PlayerHasRecentlyChangedCamera() const;

private:
	void ApplyCameraInfo(const FCameraInfo& CameraInfo, const float Factor, struct FMinimalViewInfo& InOutPOV);
		
	FCameraInfo Current;
	FCameraInfo Target;
	float TotalTransitionTime;
	float RemainingTransitionTime;

	/** Cooldown before re-enabling automatic adjustment, in seconds. */
	float CooldownRemaining;
};
 