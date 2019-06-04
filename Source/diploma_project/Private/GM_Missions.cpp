// Fill out your copyright notice in the Description page of Project Settings.

#include "GM_Missions.h"
#include "CheckGate.h"
#include "Kismet/GameplayStatics.h"

AGM_Missions::AGM_Missions()
{
	TArray<AActor*> gates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckGate::StaticClass(), gates);

	GateCount = gates.Num();
}

void AGM_Missions::deincGateCount()
{
	GateCount--;

	if (GateCount == 0)
	{
		CompleteMission(true);
	}
}
