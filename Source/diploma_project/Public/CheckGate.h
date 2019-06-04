// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckGate.generated.h"


UCLASS()
class DIPLOMA_PROJECT_API ACheckGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckGate();

	/**return gate's state*/
	UFUNCTION(BlueprintPure, Category = "GateWorks")
	bool GetActive() const;

	/**set gate's state*/
	UFUNCTION(BlueprintCallable, Category = "GateWorks")
	void SetsActive(const bool newActive);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* GateMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;

	//** Called when aircraft overlaped gate*/
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/** True when gate is active, and false when gate not active*/
	bool bActive;
};
