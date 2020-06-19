// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpPlayerController.h"
#include <Movement\Camera\ExpPlayerCameraManager.h>

AExpPlayerController::AExpPlayerController()
{
	PlayerCameraManager = CreateDefaultSubobject<AExpPlayerCameraManager>(TEXT("Exp Camera Manager"));
}
