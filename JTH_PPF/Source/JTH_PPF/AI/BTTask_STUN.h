// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BTTask_AIBase.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_STUN.generated.h"

/**
 * 
 */
UCLASS()
class JTH_PPF_API UBTTask_STUN : public UBTTask_AIBase
{
	GENERATED_BODY()

	    UBTTask_STUN();

		FTimerHandle TimerHandle;

		void StartTimer(bool Stuntype);

		void TimerExpired();

		void LS_TimerExpired();

		// 스턴종료상태를 확인한다.
		bool AIStunCheck = false;

		// 롱_스턴종료상태를 확인한다.
		bool LS_AIStunCheck = false;
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds);
};

