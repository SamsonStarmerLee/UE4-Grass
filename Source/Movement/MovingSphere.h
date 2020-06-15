// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "MovingSphere.generated.h"

UCLASS()
class MOVEMENT_API AMovingSphere : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	void UpdateState();

	void AdjustVelocity(const float DeltaTime);

	void ClearState();

	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void InputJump();

	// Movement functions
	FVector GetPosition();
	void Jump();
	bool GetGrounded();
	bool GetOnSteep();
	bool SnapToGround();
	void ProbeGround();

	// Input variables
	FVector input;

	// Visualization
	UMaterialInstanceDynamic* material;

	// Movement variables
	FVector velocity;
	bool desiredJump;
	uint32 jumpPhase;
	float minGroundDotProduct;
	FVector contactNormal;
	FVector steepNormal;
	uint32 groundContactCount;
	uint32 steepContactCount;
	uint32 stepsSinceLastGrounded;
	uint32 stepsSinceLastJump;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	float Skin = 52.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
	float GroundAcceleration = 1000.0f;

	UPROPERTY(EditAnywhere, meta = (UIMin = "0.0", UIMax = "90.0"))
	float maxGroundAngle = 30.0f;

	UPROPERTY(EditAnywhere, meta = (UIMin = "0.0", UIMax = "90.0"))
	float maxClimbableAngle = 50.0f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> GroundChannel;

	UPROPERTY(EditAnywhere)
	float AirAcceleration = 500.0f;

	UPROPERTY(EditAnywhere, meta = (UIMin = "0.0", UIMax = "1000.0"))
	float MaxSnapSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float JumpHeight = 200.0f;

	UPROPERTY(EditAnywhere)
	uint32 MaxAirJumps = 0;

	UPROPERTY(EditAnywhere)
	bool ShowDebugNormals;
};
