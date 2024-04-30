// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"
#include <Global/Data/GameMeshData.h>
#include <Global/Data/SubClassData.h>
#include <Global/Data/ItemData.h>
#include <Global/Data/MonsterData.h>
#include <Global/Data/PlayerCharacterData.h>
#include <Global/Data/SaveLevelData.h>
#include <Global/Data/UpgradeCardData.h>
#include "ARGlobal.h"

UGlobalGameInstance::UGlobalGameInstance()
{
	/* {
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/Global/Data/DT_GameMeshData.DT_GameMeshData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			MeshDatas = DataTable.Object;

			TArray<FName> ArrayName = MeshDatas->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{
				FGameMeshData* FindTable = MeshDatas->FindRow<FGameMeshData>(ArrayName[i], ArrayName[i].ToString());

				int a = 0;
			}
		}
	}*/

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/GamePlayeBluePrint/GlobalDataTable/DT_ItemData.DT_ItemData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			ItemDatas = DataTable.Object;

			TArray<FName> ArrayName = ItemDatas->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{
				FItemData* ItemData = ItemDatas->FindRow<FItemData>(ArrayName[i], ArrayName[i].ToString());
				ItemDataRandoms.Add(ItemData);
			}
		}
	}

	{
		FString DataPath = ("/Script/Engine.DataTable'/Game/BluePrint/GamePlayeBluePrint/GlobalDataTable/DT_CardData.DT_CardData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			CardDatas = DataTable.Object;

			TArray<FName> ArrayName = CardDatas->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{
				FUpgradeCardData* CardData = CardDatas->FindRow<FUpgradeCardData>(ArrayName[i], ArrayName[i].ToString());
				CardDataRandoms.Add(CardData);
			}
		}
	}


	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/GamePlayeBluePrint/PlayerCharacter/DT_SubClassData.DT_SubClassData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			SubClassData = DataTable.Object;
		}
	}

	{

		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/GamePlayeBluePrint/Monster/DT_MonsterData.DT_MonsterData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			MonsterDatas = DataTable.Object;
		}
		
	}

	{

		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/GamePlayeBluePrint/PlayerCharacter/CharacterData.CharacterData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			PlayerCharacterDatas = DataTable.Object;
		}

	}

	{

		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/GamePlayeBluePrint/PlayerCharacter/SaveLevelData.SaveLevelData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			SavePlayerCharacterDatas = DataTable.Object;
		}

	}

	UARGlobal::MainRandom.GenerateNewSeed();
}
UGlobalGameInstance::~UGlobalGameInstance()
{

}

const struct FItemData* UGlobalGameInstance::GetRandomItemData()
{
	if (true == ItemDataRandoms.IsEmpty())
	{
		return nullptr;
	}

	return ItemDataRandoms[UARGlobal::MainRandom.RandRange(0, ItemDataRandoms.Num() - 1)];
}

const struct FUpgradeCardData* UGlobalGameInstance::GetCardData()
{
	if (true == CardDataRandoms.IsEmpty())
	{
		return nullptr;
	}


	return CardDataRandoms[UARGlobal::MainRandom.RandRange(0, CardDataRandoms.Num() - 1)];
}


TSubclassOf<UObject> UGlobalGameInstance::GetSubClass(FName _Name)
{
	if (nullptr == SubClassData)
	{
		return nullptr;
	}

	FSubClassData* FindTable = SubClassData->FindRow<FSubClassData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->Object;

}

/*UStaticMesh* UGlobalGameInstance::GetMesh(FName _Name)
{
	if (nullptr == MeshDatas)
	{
		return nullptr;
	}

	FGameMeshData* FindTable = MeshDatas->FindRow<FGameMeshData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->Mesh;
}*/


FMonsterData* UGlobalGameInstance::GetMonsterData(FName _Name)
{
	if (nullptr == MonsterDatas)
	{
		return nullptr;
	}

	FMonsterData* FindTable = MonsterDatas->FindRow<FMonsterData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

FPlayerCharacterData* UGlobalGameInstance::GetPlayerCharacterData(FName _Name)
{
	if (nullptr == PlayerCharacterDatas)
	{
		return nullptr;
	}

	FPlayerCharacterData* FindTable = PlayerCharacterDatas->FindRow<FPlayerCharacterData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

FSaveLevelData* UGlobalGameInstance::GetSavePlayerCharacterData(FName _Name)
{
	if (nullptr == SavePlayerCharacterDatas)
	{
		return nullptr;
	}

	FSaveLevelData* FindTable = SavePlayerCharacterDatas->FindRow<FSaveLevelData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

void UGlobalGameInstance::GetGameData(int _Data, AActor* Owner)
{
	GameAtt = _Data;
}

int UGlobalGameInstance::SetGameData()
{
	GameAtt = 20;
	
	return GameAtt;
}
