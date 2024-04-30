// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/AICharacter.h"
#include <Global/GlobalEnums.h>
#include <Global/Data/MonsterData.h>
#include <Global/Data/PlayerCharacterData.h>
#include "Monster.generated.h"

/**
 *
 */
UCLASS()
class JTH_PPF_API AMonster : public AAICharacter
{
	GENERATED_BODY()

public:
	AMonster();
	/*
	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName AttDataName = "NONE";

	struct FPlayerCharacterData* CurPlayerCharacterData;
	*/
	int MonsterATT = 0;
	float MonsterHP = 0;
	float MonsterMAXHP = 0;
	float MonsterSTUNHP = 0;

	const struct FMonsterData* CurMonsterData;

	void BeginPlay() override;

	void Destroyed() override;

private:
	UFUNCTION(BlueprintCallable)
	void SetCollision(bool _MonsterAttCollision);

	UFUNCTION(BlueprintCallable)
	bool GetCollision();

	UFUNCTION(BlueprintCallable)
	void Big_SetCollision(bool _Big_MonsterAttCollision);

	UFUNCTION(BlueprintCallable)
	bool Big_GetCollision();

	UPROPERTY(Category = "Monster", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool MonsterAttCollision = false;

	UPROPERTY(Category = "Monster", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool Big_MonsterAttCollision = false;

	UPROPERTY(Category = "Monster", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName DataName = "NONE";

	//UPROPERTY(Category = "Monster", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		//class UMiniMapComponent* MiniMap;

	UFUNCTION()
	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
