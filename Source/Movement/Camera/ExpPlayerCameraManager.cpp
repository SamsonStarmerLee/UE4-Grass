// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpPlayerCameraManager.h"

AExpPlayerCameraManager::AExpPlayerCameraManager() : Super()
{
	LineOfSightProbeSize = 12.f;
	LineOfSightProbeChannel = ECC_Camera;
}

void AExpPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);
}
