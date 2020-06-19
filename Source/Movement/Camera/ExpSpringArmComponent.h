// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ExpSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENT_API UExpSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
	
public:
	UExpSpringArmComponent();

	/** Natural length of the spring arm when there are no collisions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float BaseTargetArmLength;

	/** Value to add to the target arm length, e.g. caused by camera modifiers. */
	float TargetArmLengthModifer;

protected:
	virtual void UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime) override;
};
