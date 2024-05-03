// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster.h"
#include <Global/GlobalGameInstance.h>
#include "Kismet/GameplayStatics.h"
#include <Global/Data/MonsterData.h>
#include "Global/ProjectTile.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include <UIEX/MiniMapComponent.h>

AMonster::AMonster()
{
	/*MiniMap = CreateDefaultSubobject<UMiniMapComponent>(TEXT("MiniMapComponent"));
	MiniMap->SetupAttachment(RootComponent);
	MiniMap->MiniMapInit(this);*/
}

void AMonster::BeginPlay()
{
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	

	if (nullptr != Inst)
	{
		CurMonsterData = Inst->GetMonsterData(DataName);

		SetAllAnimation(CurMonsterData->MapAnimation);
		SetAniState(AIState::DEATH);
	}
	MonsterATT = CurMonsterData->ATT;
	MonsterHP = CurMonsterData->HP;
	MonsterMAXHP = CurMonsterData->MAXHP;
	MonsterSTUNHP = CurMonsterData->STUNHP;
	Damage(MonsterATT);
	MainHP(MonsterHP);
	MainMAXHP(MonsterMAXHP);
	MainSTUNHP(MonsterSTUNHP);

	Super::BeginPlay();
	/*
	if (nullptr != Inst)
	{
		CurPlayerCharacterData = Inst->GetPlayerCharacterData(AttDataName);
	}
	MonsterATT = CurPlayerCharacterData->ATT;
	Damage(MonsterATT);
	*/
	GetGlobalAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &AMonster::AnimNotifyBegin);

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIState"), static_cast<uint8>(AIState::IDLE));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), CurMonsterData->SearchRange);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), CurMonsterData->AttackRange);
	FVector Pos = GetActorLocation();
	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), Pos);
}

void AMonster::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	TSubclassOf<UObject> Effect = Inst->GetSubClass(TEXT("Effect"));

	TSubclassOf<UObject> RangeAttack = Inst->GetSubClass(TEXT("MonsterRangeAttack"));

	if (NotifyName == TEXT("MAttStart"))
	{
		SetCollision(true);
	}

	if (NotifyName == TEXT("MAttEnd"))
	{
		SetCollision(false);
	}

	if (NotifyName == TEXT("Big_MAttStart"))
	{
		Big_SetCollision(true);
	}

	if (NotifyName == TEXT("Big_MAttEnd"))
	{
		Big_SetCollision(false);
	}
	/*
	if (nullptr != Effect)
	{
		FTransform Trans;
		FVector Pos;
		TArray<UActorComponent*> MeshEffects = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("MonsterEffect"));
		TArray<UActorComponent*> StaticMeshs = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("MonsterMesh"));

		USceneComponent* EffectCom = Cast<USceneComponent>(MeshEffects[0]);
		Pos = EffectCom->GetComponentToWorld().GetLocation();

		// 이펙트 만들기
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(Effect);
			
			Actor->SetActorLocation(Pos);
			Actor->SetActorRotation(GetActorRotation());
			Actor->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
		}

		// 발사체 만들기
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(RangeAttack);

			AProjectTile* ProjectTile = Cast<AProjectTile>(Actor);

			ProjectTile->SetActorLocation(Pos);
			ProjectTile->SetActorRotation(GetActorRotation());
			ProjectTile->GetSphereComponent()->SetCollisionProfileName(TEXT("MonsterAttack"), true);
		}
	}
	*/
}

void AMonster::SetCollision(bool _MonsterAttCollision)
{
	MonsterAttCollision = _MonsterAttCollision;
}

bool AMonster::GetCollision() 
{
	return MonsterAttCollision;
}

void AMonster::Big_SetCollision(bool _Big_MonsterAttCollision)
{
	Big_MonsterAttCollision = _Big_MonsterAttCollision;
}

bool AMonster::Big_GetCollision()
{
	return Big_MonsterAttCollision;
}

void AMonster::Destroyed()
{
	Super::Destroyed();

	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	// 몬스터를 처치하면 킬카운트를 올린다.
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter != nullptr) 
	{
		MyCharacter->KillCount += 1;
	}

	if (nullptr == Inst)
	{
		return;
	}

	TSubclassOf<UObject> Item = Inst->GetSubClass(TEXT("Item"));

	for (size_t i = 0; i < 1; i++)
	{
		FVector RandomPos;

		RandomPos.X = UARGlobal::MainRandom.FRandRange(-100, 100);
		RandomPos.Y = UARGlobal::MainRandom.FRandRange(-100, 100);

		AActor* Actor = GetWorld()->SpawnActor<AActor>(Item);
		if(Actor != nullptr)
		{
			// 몬스터 입장에서는 그냥 아이템인지도 알필요가 없고
			// 그냥 내가 죽을때 어떤 액터를 만들뿐이다.
			Actor->Tags.Add(TEXT("Item"));
			Actor->SetActorLocation(GetActorLocation() + RandomPos);
		}
	}

}