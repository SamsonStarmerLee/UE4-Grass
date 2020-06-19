// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpSpringArmComponent.h"

UExpSpringArmComponent::UExpSpringArmComponent() : Super()
{
	// Enable camera controls.
	//bUsePawnControlRotation = true;

	// Set reasonable default values for camera distance and perspective.
	BaseTargetArmLength = 500.f;
	SocketOffset = FVector(0.f, 40.f, 40.f);

	// Enable camera lag.
	bEnableCameraLag = true;
	CameraLagSpeed = 5.f;
}

void UExpSpringArmComponent::UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime)
{
	TargetArmLength = BaseTargetArmLength + TargetArmLengthModifer;
	Super::UpdateDesiredArmLocation(bDoTrace, bDoLocationLag, bDoRotationLag, DeltaTime);
	TargetArmLengthModifer = 0.f;
}
