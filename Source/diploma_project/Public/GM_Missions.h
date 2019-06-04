// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Missions.generated.h"

UCLASS()
class DIPLOMA_PROJECT_API AGM_Missions : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGM_Missions();

	UPROPERTY(BlueprintReadOnly, Category = "GamePlay")
	int GateCount;

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void deincGateCount();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "GamePlay")
	void CompleteMission(bool bSucces);
	
};
