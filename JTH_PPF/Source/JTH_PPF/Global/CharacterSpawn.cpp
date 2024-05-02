// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CharacterSpawn.h"
#include "Global/GlobalGameInstance.h"

// Sets default values
ACharacterSpawn::ACharacterSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ACharacterSpawn::SpawnNum() 
{
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();
	if (nullptr != Inst)
	{
		SaveCurPlayerCharacterData = Inst->GetSavePlayerCharacterData(SaveName);
	}

	int LevelNum = SaveCurPlayerCharacterData->S_CharacterSpawn;
	return LevelNum;
}

void ACharacterSpawn::SetSpawnNum(int LevelNum)
{
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();
	if (nullptr != Inst)
	{
		SaveCurPlayerCharacterData = Inst->GetSavePlayerCharacterData(SaveName);
	}

	SaveCurPlayerCharacterData->S_CharacterSpawn = LevelNum;
}
