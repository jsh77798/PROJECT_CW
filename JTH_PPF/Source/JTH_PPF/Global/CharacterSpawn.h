// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Global/Data/SaveLevelData.h>
#include "CharacterSpawn.generated.h"

UCLASS()
class JTH_PPF_API ACharacterSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterSpawn();

	struct FSaveLevelData* SaveCurPlayerCharacterData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName SaveName = "Save";

	UFUNCTION(BlueprintCallable)
	int SpawnNum();

	UFUNCTION(BlueprintCallable)
	void SetSpawnNum(int LevelNum);
};
