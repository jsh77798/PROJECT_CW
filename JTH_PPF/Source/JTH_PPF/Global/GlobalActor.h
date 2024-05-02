// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Global/Data/SaveLevelData.h>
#include "GlobalActor.generated.h"

UCLASS()
class JTH_PPF_API AGlobalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobalActor();

	struct FSaveLevelData* SaveCurPlayerCharacterData;

	/*  상자 액터용  */
	UFUNCTION(BlueprintCallable)
	bool OpenCheck();

	/*  문 액터용  */
	UFUNCTION(BlueprintCallable)
	int GetDoorOpen();

	UFUNCTION(BlueprintCallable)
	void SetDoorOpen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName SaveName = "NONE";
};
