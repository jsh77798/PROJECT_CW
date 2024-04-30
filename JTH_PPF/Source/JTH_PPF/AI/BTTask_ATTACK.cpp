// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ATTACK.h"
#include <random>

UBTTask_ATTACK::UBTTask_ATTACK()
{
	// �� �����Ӹ��� �����ض�
	bNotifyTick = true;
	// ������ ���� �ѹ� �����ض�.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_ATTACK::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// ���ݽ��۽� ����üũ�� false�� ��ȯ�Ѵ�.
	GetGlobalCharacter(OwnerComp)->SetStunCheck(false);

	/*////////////////�������� ���� �ִϸ��̼� ����////////////////*/
	// �õ尪�� ��� ���� random_device ����.
	std::random_device rd;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 gen(rd());

	// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	std::uniform_int_distribution<int> dis(0, 1);

	if (0 == dis(gen)) 
	{
	    GetGlobalCharacter(OwnerComp)->SetAniState(UBTTask_AIBase::GetAiState(OwnerComp));
	}
	else
	{
	    GetGlobalCharacter(OwnerComp)->SetAniState(AIState::ATTACK02);
	}


	return EBTNodeResult::Type::InProgress;
}

void UBTTask_ATTACK::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	if (true == IsDeathCheck(OwnerComp))
	{
		SetStateChange(OwnerComp, AIState::DEATH);
		return;
	}

	if (true == IsLongStunCheck(OwnerComp))
	{
		SetStateChange(OwnerComp, AIState::STUN);
		return;
	}

	UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(UBTTask_AIBase::GetAiState(OwnerComp));
	float Time = Montage->CalculateSequenceLength();

	if (Time <= GetStateTime(OwnerComp))
	{
		// �� �Լ��� Ȯ��
		float Probabilities[] = { 0.7f, 0.3f };

		// 0���� 1 ������ ������ ���� ����
		float RandomNumber = FMath::FRand();

		// ���� Ȯ��
		float AccumulatedProbability = 0.0f;

		// ���õ� �Լ� �ε���
		int SelectedIndex = -1;

		// �� �Լ��� Ȯ���� ����Ͽ� �������� ���õ� �Լ� �ε��� ����
		for (int i = 0; i < 2; ++i)
		{
			AccumulatedProbability += Probabilities[i];
			if (RandomNumber <= AccumulatedProbability)
			{
				SelectedIndex = i;
				break;
			}
		}

		// ���õ� �Լ� ����
		switch (SelectedIndex)
		{
		case 0:
			SetStateChange(OwnerComp, AIState::MOVE);
			break;
		case 1:
			SetStateChange(OwnerComp, AIState::SLOWMOVE);
			break;
		default:
			// ���� ó��
			break;
		}
	}
}