// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Aircraft.generated.h"

UCLASS()
class DIPLOMA_PROJECT_API AAircraft : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAircraft();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void ChangingThrot();
	virtual void WorkOfForces();
	virtual void CameraRotating(float DeltaTime);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Main components */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent * BoxComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UPoseableMeshComponent * PlaneComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* ArmComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent * CameraComp;


	
	/**
	 * Plane properties
	 */

	/** Pitch */
	UPROPERTY(EditDefaultsOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float AircontrolY = 2500.0f;

	/** Roll */
	UPROPERTY(EditDefaultsOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float AircontrolX = 2500.0f;

	/** Yaw */
	UPROPERTY(EditDefaultsOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float AircontrolZ = 2500.0f;

	/** Mass */
	UPROPERTY(EditDefaultsOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float PlaneMass;

	/** Max throttle value */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float MaxThrot; 
	
	/** Actual throttle value */
	UPROPERTY(BlueprintReadOnly, Category = "Fly Settings")
	float Throt = 0;

	/** Start value of throttle in percents  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fly Settings", meta = (ClampMin = "0", ClampMax = "100"))
	float StartThrot;

	/** Resistance coefficient */
	UPROPERTY(EditDefaultsOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float Resist;

	/** Resistance coefficient */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float AngularDemp;

	/** Coefficient of lift force */
	UPROPERTY(EditDefaultsOnly, Category = "Fly Settings", meta = (ClampMin = "0"))
	float Lift;

	
	/*
	Input functions 
	*/

	/** Rotationt input */
	virtual void TurnPitch(float AxisValue);
	virtual void TurnRoll(float AxisValue);
	virtual void TurnYaw(float AxisValue);

	/** Throttle input */
	virtual void StartIncreaseThrottle();
	virtual void StopIncreaseThrottle();
	virtual void StartDeincreaseThrottle();
	virtual void StopDeincreaseThrottle();
	bool bThrottleUp;
	bool bThrottleDown;
	
	/** Camera input */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Settings")
	float CameraRotationSpeed;
	FVector2D CameraInput;
	virtual void PitchCamera(float AxisValue);
	virtual void YawCamera(float AxisValue);
	
public:
	/** Plane's local velocity in cm/s (units/s) */
	UPROPERTY(BlueprintReadOnly, Category = "Fly Info")
	FVector Vel;
};
