// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActorInterface.h"
#include "Camera\PlayerCharacterInterface.h"
#include "MovingSphere.generated.h"

class ACameraModificationVolume;
class UExpSpringArmComponent;
class UCameraComponent;

UCLASS()
class MOVEMENT_API AMovingSphere : public APawn, public IPlayerCharacterInterface, public ICameraActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingSphere();

protected:
	ACameraModificationVolume* CurrentCameraVolume;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UExpSpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	void UpdateState();

	void AdjustVelocity(const float DeltaTime);

	void ClearState();

	// PlayerCharacterInterface
	bool GotMovementInput() const override;

	// CameraActorInterface
	virtual ACameraModificationVolume* GetCurrentCameraModificationVolume() override;
	virtual void SetCurrentCameraModificationVolume(ACameraModificationVolume* Volume) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	float Skin = 54.f;

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
	float AirAcceleration = 200.0f;

	UPROPERTY(EditAnywhere, meta = (UIMin = "0.0"))
	float ProbeDistance = 100.0f;

	UPROPERTY(EditAnywhere, meta = (UIMin = "0.0", UIMax = "1000.0"))
	float MaxSnapSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float JumpHeight = 200.0f;

	UPROPERTY(EditAnywhere)
	uint32 MaxAirJumps = 0;

	UPROPERTY(EditAnywhere)
	bool ShowDebugNormals;

	/** Camera turn rate in deg/sec. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float BaseTurnRate = 90.0f;

	/** Camera turn rate in deg/sec. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float BaseLookUpRate = 90.0f;
};
