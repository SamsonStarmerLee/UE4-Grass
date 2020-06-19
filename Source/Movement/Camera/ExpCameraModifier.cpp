// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraInfo.h"
#include "ExpCameraModifier.h"
#include <Movement\Camera\ExpSpringArmComponent.h>

UExpCameraModifier::UExpCameraModifier() 
	: Super(),
	Current(FCameraInfo()),
	Target(FCameraInfo())
{
}

bool UExpCameraModifier::ProcessViewRotation(AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot)
{
	Super::ProcessViewRotation(ViewTarget, DeltaTime, OutViewRotation, OutDeltaRot);

	if (!IsValid(ViewTarget))
	{
		return false;
	}

	APawn* pawn = Cast<APawn>(ViewTarget);
	if (!IsValid(pawn))
	{
		return false;
	}

	APlayerController* playerController = Cast<APlayerController>(pawn->Controller);
	if (!IsValid(playerController))
	{
		return false;
	}

	if (!playerController->RotationInput.IsNearlyZero(THRESH_QUAT_NORMALIZED))
	{
		// Reset cooldown.
		CooldownRemaining = CooldownAfterInput;
		return false;
	}

	if (PlayerHasRecentlyChangedCamera())
	{
		// Tick cooldown and remain player-controlled.
		CooldownRemaining -= DeltaTime;
		return false;
	}

	// TODO: Why are all returns false?
	return false;
}

FCameraInfo UExpCameraModifier::GetCurrentModifiers() const
{
	return Current;
}

FCameraInfo UExpCameraModifier::GetTargetModifiers() const
{
	return Target;
}

void UExpCameraModifier::ApplyTransition(const FCameraInfo CameraInfo, const float TransitionTime, FMinimalViewInfo& InOutPOV, const float DeltaTime)
{
	if (!Target.Equals(CameraInfo))
	{
		Current = Target;
		Target = CameraInfo;

		if (RemainingTransitionTime > 0.f)
		{
			// New transition started before old was finished. Play transition backwards without flipping.
			// TODO: What?
			RemainingTransitionTime = TotalTransitionTime - RemainingTransitionTime;
		}
	}

	if (Current.Equals(Target))
	{
		// No changes.
		ApplyCameraInfo(Current, 1.0f, InOutPOV);
		return;
	}

	// Three cases:
	// 1. Current is zero, Target is not zero -> Apply new mods.
	// 2. Current is not zero, Target is zero -> Stop applying mods.
	// 3. Both are non-zero. Transition from current to new mods.
	// TODO(np): Handle Case 3: Need transition from current modifiers to new modifiers.

	float applicationFactor = 0.f;
	FCameraInfo modsToApply;

	// Case 1: New mods.
	if (!Target.IsZero())
	{
		modsToApply = Target;

		if (RemainingTransitionTime <= 0.f)
		{
			// Start transition timer.
			TotalTransitionTime = TransitionTime;
			RemainingTransitionTime = TotalTransitionTime;
		}
		else
		{
			// Tick
			RemainingTransitionTime -= DeltaTime;

			if (RemainingTransitionTime <= 0.f)
			{
				// Finished
				Current = Target;
				applicationFactor = 1.f;
			}
			else
			{
				applicationFactor = 1 - (RemainingTransitionTime / TotalTransitionTime);
			}
		}
	}
	// Case 2: Stop mods.
	else
	{
		modsToApply = Current;

		if (RemainingTransitionTime <= 0.f)
		{
			// Restart
			RemainingTransitionTime = TotalTransitionTime;
			applicationFactor = 1.f;
		}
		else
		{
			// Tick
			RemainingTransitionTime -= DeltaTime;

			if (RemainingTransitionTime <= 0.f)
			{
				// Finished
				Current = Target;
				applicationFactor = 0.f;
			}
			else
			{
				// Gradually decrease the influence of previous mods.
				applicationFactor = RemainingTransitionTime / TotalTransitionTime;
			}
		}
	}
	//TODO: Case 3

	ApplyCameraInfo(modsToApply, applicationFactor, InOutPOV);
}

bool UExpCameraModifier::PlayerHasRecentlyChangedCamera() const
{
	return CooldownRemaining > 0;
}

void UExpCameraModifier::ApplyCameraInfo(const FCameraInfo& CameraInfo, const float Factor, FMinimalViewInfo& InOutPOV)
{
	AActor* viewTarget = GetViewTarget();
	if (!IsValid(viewTarget))
	{
		return;
	}

	// Apply FOV
	float appliedFOV = CameraInfo.FOV * Factor;
	InOutPOV.FOV = InOutPOV.FOV + appliedFOV;

	TArray<USceneComponent*> children;
	viewTarget->GetRootComponent()->GetChildrenComponents(true, children);

	// Apply spring arm length.
	// TODO: Access spring arm some other way.
	for (int i = 0; i < children.Num(); ++i)
	{
		auto springArmComponent = Cast<UExpSpringArmComponent>(children[i]);

		if (IsValid(springArmComponent))
		{
			springArmComponent->TargetArmLengthModifer += CameraInfo.SpringArmLength * Factor;
			break;
		}
	}
}
 