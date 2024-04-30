// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MOVE.h"
#include <Global/GlobalCharacter.h>
#include <AI/AICon.h>
#include <Global/GlobalEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

// 일단 써치 범위 바깥으로 이동하면
// Return 상태로 전환하는 것은 2가지 상황이 존재한다.
// 1. 그냥 플레이어가 너무 멀어져서 나는 돌아간다.
// 2. 내 원래자리(만들어진 순간에 자신의 위치.)에서 너무 말리 떨어졌다.

UBTTask_MOVE::UBTTask_MOVE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MOVE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::MOVE);

	StartTimer();

	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetGlobalCharacter(OwnerComp)->GetMovementComponent());

	if (nullptr != MoveCom)
	{
		MoveCom->MaxWalkSpeed = 200.0f;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_MOVE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (nullptr == TargetActor)
	{
		SetStateChange(OwnerComp, AIState::RETURN);
		return;
	}

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
	else 
	{
		if (true == IsStunCheck(OwnerComp))
		{
			SetStateChange(OwnerComp, AIState::STUN);
			return;
		}
	}


	{
		FVector TargetPos = TargetActor->GetActorLocation();
		FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		// 혹시라도 z축이 있을 가능성을 없애는게 보통입니다.
		TargetPos.Z = 0.0f;
		ThisPos.Z = 0.0f;

		FVector Dir = TargetPos - ThisPos;
		Dir.Normalize();

		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * DelataSeconds });
			GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else {
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}
	}



	{
		FVector PawnPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		FVector TargetPos = TargetActor->GetActorLocation();
		PawnPos.Z = 0.0f;
		TargetPos.Z = 0.0f;

		FVector Dir = TargetPos - PawnPos;

		GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
		//GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

		FVector OriginPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("OriginPos"));
		float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));
		float AttackRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));

		OriginPos.Z = 0.0f;
		FVector OriginDir = OriginPos - PawnPos;

		if (OriginDir.Size() >= SearchRange * 1.5f)
		{
			GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), nullptr);
			SetStateChange(OwnerComp, AIState::RETURN);
			int a = 0;
			return;
		}

		if (SearchRange < Dir.Size())
		{
			SetStateChange(OwnerComp, AIState::IDLE);
			return;
		}

		// 충분히 근접했다.
		if (AttackRange >= Dir.Size())
		{
			SetStateChange(OwnerComp, AIState::ATTACK);
			return;
		}
	}

	if (AIMoveCheck == true)
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

		//SetStateChange(OwnerComp, AIState::SLOWMOVE);
		AIMoveCheck = false;
	}
}

void UBTTask_MOVE::StartTimer()
{
	float Duration = 3.5f; // 2초의 지연 시간
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_MOVE::TimerExpired, Duration, false);
}

void UBTTask_MOVE::TimerExpired()
{
	// 타이머가 만료될 때 실행될 코드를 작성합니다.
	//UE_LOG(LogTemp, Warning, TEXT("타이머가 만료되었습니다!"));
	AIMoveCheck = true;
}