// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_STUN.h"

UBTTask_STUN::UBTTask_STUN()
{
	// �� �����Ӹ��� �����ض�
	bNotifyTick = true;
	// ������ ���� �ѹ� �����ض�.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_STUN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (GetGlobalCharacter(OwnerComp)->GetLongStunCheck() != true)
	{
		StartTimer(false);
		GetGlobalCharacter(OwnerComp)->SetAniState(UBTTask_AIBase::GetAiState(OwnerComp));
	}
	else 
	{
		StartTimer(true);
	    GetGlobalCharacter(OwnerComp)->SetAniState(AIState::STUN02);
	}
	
	return EBTNodeResult::Type::InProgress;
}


void UBTTask_STUN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	if (true == IsDeathCheck(OwnerComp))
	{
		SetStateChange(OwnerComp, AIState::DEATH);
		return;
	}
	
	//if (true == IsLongStunCheck(OwnerComp))
	//{
	//	SetStateChange(OwnerComp, AIState::STUN);
	//	return;
	//}
	

	if (AIStunCheck == true)
	{
		AIStunCheck = false;

		GetGlobalCharacter(OwnerComp)->SetStunCheck(false);

		SetStateChange(OwnerComp, AIState::IDLE);
	}
	if (LS_AIStunCheck == true)
	{
		LS_AIStunCheck = false;
		LongStun = false;

		GetGlobalCharacter(OwnerComp)->SetStunCheck(false);
		GetGlobalCharacter(OwnerComp)->SetLongStunCheck(false);

		SetStateChange(OwnerComp, AIState::IDLE);
	}

}

void UBTTask_STUN::StartTimer(bool LongStuntype)
{
	if (LongStuntype == false)
	{
		// ���ϻ��� Ÿ�̸� 
		float Duration = 0.5f;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_STUN::TimerExpired, Duration, false);
	}
	if (LongStuntype == true)
	{
		// ��_���ϻ��� Ÿ�̸�
		float Duration = 3.5f; // n���� ���� �ð�
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_STUN::LS_TimerExpired, Duration, false);
	}
}

void UBTTask_STUN::TimerExpired()
{
	// Ÿ�̸Ӱ� ����� �� ����� �ڵ带 �ۼ��մϴ�.
	UE_LOG(LogTemp, Warning, TEXT("Ÿ�̸Ӱ� ����Ǿ����ϴ�!"));
	AIStunCheck = true;
}

void UBTTask_STUN::LS_TimerExpired()
{
	// Ÿ�̸Ӱ� ����� �� ����� �ڵ带 �ۼ��մϴ�.
	UE_LOG(LogTemp, Warning, TEXT("Ÿ�̸Ӱ� ����Ǿ����ϴ�!"));
	LS_AIStunCheck = true;
}