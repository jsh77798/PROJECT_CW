// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SLOWMOVE.h"
#include <Global/GlobalCharacter.h>
#include <AI/AICon.h>
#include <Global/GlobalEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_SLOWMOVE::UBTTask_SLOWMOVE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_SLOWMOVE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::SLOWMOVE);

	StartTimer();

	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetGlobalCharacter(OwnerComp)->GetMovementComponent());

	if (nullptr != MoveCom)
	{
		MoveCom->MaxWalkSpeed = 110.0f;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_SLOWMOVE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
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

		//GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
		//GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

		FVector OriginPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("OriginPos"));
		float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));
		float AttackRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));
		float SlowMoveRange = 450.0f;

		// 해당 범위에 들어가면 뒤로 이동하고 주위를 돈다. 간을 본다.
		if (SlowMoveRange >= Dir.Size())
		{
			FVector BDir = TargetPos + PawnPos;
			GetGlobalCharacter(OwnerComp)->AddMovementInput(BDir);
		}
		/*
		// 특정범위에 도달하면 좌우로 돈다.
		if (SlowMoveRange == Dir.Size())
		{
			FVector YDir;
			int RandomNum =GetGlobalCharacter(OwnerComp)->MyRandom(0, 1);
			switch (RandomNum) 
			{
			case 0:
			    YDir.X = 55.0f;
				break;
			case 1:
				YDir.X = -55.0f;
				break;
			}

			FVector BDir = TargetPos + PawnPos + YDir.X;
			GetGlobalCharacter(OwnerComp)->AddMovementInput(BDir);
		}
		*/

		// 해당 범위에서 떨어져있으면 타겟쪽으로 이동한다.
		if (SlowMoveRange < Dir.Size())
		{
			GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
		}

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
		//if (AttackRange >= Dir.Size())
		//{
		//	SetStateChange(OwnerComp, AIState::ATTACK);
		//	return;
		//}
	}

	if (AISlowMoveCheck == true)
	{
		// 각 함수의 확률
		float Probabilities[] = { 0.8f, 0.2f };

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
		//SetStateChange(OwnerComp, AIState::MOVE);
		AISlowMoveCheck = false;
	}

}

void UBTTask_SLOWMOVE::StartTimer()
{
	float Duration = 4.0f; // 4초의 지연 시간
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_SLOWMOVE::TimerExpired, Duration, false);
}

void UBTTask_SLOWMOVE::TimerExpired()
{
	// 타이머가 만료될 때 실행될 코드를 작성합니다.
	//UE_LOG(LogTemp, Warning, TEXT("타이머가 만료되었습니다!"));
	AISlowMoveCheck = true;
}