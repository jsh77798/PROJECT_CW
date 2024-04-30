// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_AIBase.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MOVE.generated.h"

/**
 *
 */
UCLASS()
class JTH_PPF_API UBTTask_MOVE : public UBTTask_AIBase
{
	GENERATED_BODY()

		UBTTask_MOVE();

		FTimerHandle TimerHandle;

		void StartTimer();

		void TimerExpired();

		// 종료상태를 확인한다.
		bool AIMoveCheck = false;

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds);
};
