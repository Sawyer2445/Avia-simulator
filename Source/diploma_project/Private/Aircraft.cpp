// Fill out your copyright notice in the Description page of Project Settings.

#include "Aircraft.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GM_Missions.h"

// Sets default values
AAircraft::AAircraft()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Driver"));
	BoxComp->SetSimulatePhysics(true);
	RootComponent = BoxComp;
	PlaneComp = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Plane"));
	PlaneComp->SetupAttachment(BoxComp);
	ArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	ArmComp->SetupAttachment(PlaneComp);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(ArmComp);
}

// Called when the game starts or when spawned
void AAircraft::BeginPlay()
{
	Super::BeginPlay();

	Throt = (StartThrot / 100.0f) * MaxThrot;
}

// Called every frame
void AAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangingThrot();
	CameraRotating(DeltaTime);
	WorkOfForces();
}

// Called to bind functionality to input
void AAircraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Actions
	PlayerInputComponent->BindAction("ThrottleIncrease", IE_Pressed, this, &AAircraft::StartIncreaseThrottle);
	PlayerInputComponent->BindAction("ThrottleIncrease", IE_Released, this, &AAircraft::StopIncreaseThrottle);
	PlayerInputComponent->BindAction("ThrottleDecrease", IE_Pressed, this, &AAircraft::StartDeincreaseThrottle);
	PlayerInputComponent->BindAction("ThrottleDecrease", IE_Released, this, &AAircraft::StopDeincreaseThrottle);


	//Bind Axis
	PlayerInputComponent->BindAxis("PitchTurn", this, &AAircraft::TurnPitch);
	PlayerInputComponent->BindAxis("RollTurn", this, &AAircraft::TurnRoll);
	PlayerInputComponent->BindAxis("YawTurn", this, &AAircraft::TurnYaw);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AAircraft::PitchCamera);
	PlayerInputComponent->BindAxis("CameraYaw", this, &AAircraft::YawCamera);
}



void AAircraft::ChangingThrot()
{
	if (bThrottleUp)
	{
		if (Throt < MaxThrot)
		{
			Throt += MaxThrot / 100;
		}
	}

	if (bThrottleDown)
	{
		if (Throt > 0)
		{
			Throt -= MaxThrot / 100;
		}
	}
}

void AAircraft::WorkOfForces()
{
	/** Get velocity */
	Vel = GetVelocity();
	Vel = GetActorRotation().UnrotateVector(Vel);
	Vel /= 100.0f;
	Vel.X = FMath::Clamp(Vel.X, 0.0f, 10000000.0f);

	/** Calculate forces */
	FVector GravityForce = -1.0f * FVector(0.0f, 0.0f, PlaneMass * 10.0f);
	FVector ThrottleForce = BoxComp->GetForwardVector() * Throt;
	FVector LiftingForce = BoxComp->GetUpVector() * FMath::Square(Vel.X) * Lift;
	/** Set damping force using linar damping parametr */
	BoxComp->SetLinearDamping(Vel.X * Resist);
	
	/** Sum of forces and apply */
	FVector forces = GravityForce + ThrottleForce + LiftingForce;
	BoxComp->AddForce(forces, NAME_None, true);
}

void AAircraft::TurnPitch(float AxisValue)
{
	FVector Turn = FMath::Lerp(FVector(0.0f, 0.0f, 0.0f), AxisValue * AircontrolY * (BoxComp->GetRightVector()), 0.1);
	BoxComp->AddTorqueInDegrees(Turn, NAME_None, true);
}

void AAircraft::TurnRoll(float AxisValue)
{
	FVector Turn = AxisValue * AircontrolX * BoxComp->GetForwardVector();
	BoxComp->AddTorqueInDegrees(Turn, NAME_None, true);
}

void AAircraft::TurnYaw(float AxisValue)
{
	//2500.0f - aero
	FVector Turn = FMath::Lerp(FVector(0.0f, 0.0f, 0.0f), AxisValue * AircontrolZ * (BoxComp->GetUpVector()), 0.1);
	BoxComp->AddTorqueInDegrees(Turn, NAME_None, true);
}

void AAircraft::StartIncreaseThrottle()
{
	bThrottleUp = true;
}

void AAircraft::StopIncreaseThrottle()
{
	bThrottleUp = false;
}

void AAircraft::StartDeincreaseThrottle()
{
	bThrottleDown = true;
}

void AAircraft::StopDeincreaseThrottle()
{
	bThrottleDown = false;
}

void AAircraft::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void AAircraft::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void AAircraft::CameraRotating(float DeltaTime)
{
	AddControllerPitchInput(CameraInput.Y * DeltaTime * CameraRotationSpeed);
	AddControllerYawInput(CameraInput.X * DeltaTime * CameraRotationSpeed);
}