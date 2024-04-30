// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ATTACK.h"
#include <random>

UBTTask_ATTACK::UBTTask_ATTACK()
{
	// 매 프레임마다 실행해라
	bNotifyTick = true;
	// 끝나는 순간 한번 실행해라.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_ATTACK::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 공격시작시 스턴체크를 false로 전환한다.
	GetGlobalCharacter(OwnerComp)->SetStunCheck(false);

	/*////////////////랜덤으로 공격 애니메이션 실행////////////////*/
	// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
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
		// 각 함수의 확률
		float Probabilities[] = { 0.7f, 0.3f };

		// 0부터 1 사이의 랜덤한 숫자 생성
		float RandomNumber = FMath::FRand();

		// 누적 확률
		float AccumulatedProbability = 0.0f;

		// 선택된 함수 인덱스
		int SelectedIndex = -1;

		// 각 함수의 확률을 고려하여 랜덤으로 선택된 함수 인덱스 결정
		for (int i = 0; i < 2; ++i)
		{
			AccumulatedProbability += Probabilities[i];
			if (RandomNumber <= AccumulatedProbability)
			{
				SelectedIndex = i;
				break;
			}
		}

		// 선택된 함수 실행
		switch (SelectedIndex)
		{
		case 0:
			SetStateChange(OwnerComp, AIState::MOVE);
			break;
		case 1:
			SetStateChange(OwnerComp, AIState::SLOWMOVE);
			break;
		default:
			// 예외 처리
			break;
		}
	}
}