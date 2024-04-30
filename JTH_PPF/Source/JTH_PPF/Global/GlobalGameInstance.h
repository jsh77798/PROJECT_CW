// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "ARGlobal.h"
#include "GlobalGameInstance.generated.h"

/**
 *
 */
UCLASS()
class JTH_PPF_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UGlobalGameInstance();
	~UGlobalGameInstance();

	TSubclassOf<UObject> GetSubClass(FName _Name);

	//UStaticMesh* GetMesh(FName _Name);

	struct FMonsterData* GetMonsterData(FName _Name);

	struct FPlayerCharacterData* GetPlayerCharacterData(FName _Name);

	struct FSaveLevelData* GetSavePlayerCharacterData(FName _Name);

	void GetGameData(int _Data, AActor* Owner);
	int SetGameData();
	int GameAtt = 0;
	AActor* _Owner = nullptr;

	const struct FItemData* GetRandomItemData();

	const struct FUpgradeCardData* GetCardData();

private:
	UPROPERTY()
		UDataTable* SubClassData;

	//UPROPERTY()
		//UDataTable* MeshDatas;

	UPROPERTY()
		UDataTable* MonsterDatas;

	UPROPERTY()
		UDataTable* PlayerCharacterDatas;

	UPROPERTY()
		UDataTable* SavePlayerCharacterDatas;

	UPROPERTY()
		UDataTable* ItemDatas;

	UPROPERTY()
		UDataTable* CardDatas;

		TArray<const struct FItemData*> ItemDataRandoms;

		TArray<const struct FUpgradeCardData*> CardDataRandoms;

	TArray<UStaticMesh*> Arrmesh;
};
