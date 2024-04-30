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
		// Ȥ�ö� z���� ���� ���ɼ��� ���ִ°� �����Դϴ�.
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

		// �ش� ������ ���� �ڷ� �̵��ϰ� ������ ����. ���� ����.
		if (SlowMoveRange >= Dir.Size())
		{
			FVector BDir = TargetPos + PawnPos;
			GetGlobalCharacter(OwnerComp)->AddMovementInput(BDir);
		}
		/*
		// Ư�������� �����ϸ� �¿�� ����.
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

		// �ش� �������� ������������ Ÿ�������� �̵��Ѵ�.
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

		// ����� �����ߴ�.
		//if (AttackRange >= Dir.Size())
		//{
		//	SetStateChange(OwnerComp, AIState::ATTACK);
		//	return;
		//}
	}

	if (AISlowMoveCheck == true)
	{
		// �� �Լ��� Ȯ��
		float Probabilities[] = { 0.8f, 0.2f };

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
		//SetStateChange(OwnerComp, AIState::MOVE);
		AISlowMoveCheck = false;
	}

}

void UBTTask_SLOWMOVE::StartTimer()
{
	float Duration = 4.0f; // 4���� ���� �ð�
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_SLOWMOVE::TimerExpired, Duration, false);
}

void UBTTask_SLOWMOVE::TimerExpired()
{
	// Ÿ�̸Ӱ� ����� �� ����� �ڵ带 �ۼ��մϴ�.
	//UE_LOG(LogTemp, Warning, TEXT("Ÿ�̸Ӱ� ����Ǿ����ϴ�!"));
	AISlowMoveCheck = true;
}