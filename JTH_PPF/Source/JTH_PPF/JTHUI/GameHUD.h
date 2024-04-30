// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JTHUI/MainWidget.h"
#include "GameHUD.generated.h"


/**
 * 
 */
UCLASS()
class JTH_PPF_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	AGameHUD();
	~AGameHUD();


	UFUNCTION(BlueprintCallable)
	UMainWidget* GetMainWidget()
	{
		return MainWidget;
	}

protected:
	void BeginPlay() override;
	void Tick(float _Delta) override;

private:
	

	UMainWidget* MainWidget = nullptr; 
};
