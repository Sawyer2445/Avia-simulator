// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckGate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Aircraft.h"
#include "GM_Missions.h"

// Sets default values
ACheckGate::ACheckGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	RootComponent = GateMesh;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACheckGate::HandleOverlap);

	bActive = true;
}

bool ACheckGate::GetActive() const
{
	return bActive;
}

void ACheckGate::SetsActive(bool const newActive)
{
	bActive = newActive;
}

// Called when the game starts or when spawned
void ACheckGate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckGate::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
		
		AGM_Missions* g = Cast<AGM_Missions>(GetWorld()->GetAuthGameMode());
		if (g)
		{
			g->deincGateCount();
			
		}
		Destroy();	
}

