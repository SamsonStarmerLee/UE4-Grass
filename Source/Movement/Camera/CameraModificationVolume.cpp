// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraModificationVolume.h"
#include <Movement\Camera\CameraActorInterface.h>

ACameraModificationVolume::ACameraModificationVolume() : Super()
{
	TransitionTime = 1.f;
}

void ACameraModificationVolume::NotifyActorBeginOverlap(AActor* Other)
{
	Super::NotifyActorBeginOverlap(Other);

	auto cameraActor = Cast<ICameraActorInterface>(Other);
	if (!cameraActor)
	{
		return;
	}

	// Set camera modification volume.
	cameraActor->SetCurrentCameraModificationVolume(this);
}

void ACameraModificationVolume::NotifyActorEndOverlap(AActor* Other)
{
	Super::NotifyActorEndOverlap(Other);

	auto cameraActor = Cast<ICameraActorInterface>(Other);
	if (!cameraActor)
	{
		return;
	}

	// Reset camera modification volume
	if (cameraActor->GetCurrentCameraModificationVolume() == this)
	{
		cameraActor->SetCurrentCameraModificationVolume(nullptr);
	}
}
