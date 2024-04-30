// Fill out your copyright notice in the Description page of Project Settings.


#include "JTHUI/PlaySaveGame.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UPlaySaveGame::DataSave(ACharacter* Player)
{
	// ACharacter* Player = UGameplayStatics::GetPlayerCharacter(_World, 0);
	PlayerPos = Player->GetActorLocation();
	PlayerRot = Player->GetController()->GetControlRotation();
	PlayerScale = Player->GetActorScale();
}

void UPlaySaveGame::DataLoad(ACharacter* Player)
{
	// ACharacter* Player = UGameplayStatics::GetPlayerCharacter(_World, 0);
	Player->SetActorLocation(PlayerPos);
	Player->GetController()->SetControlRotation(PlayerRot);
	Player->SetActorScale3D(PlayerScale);
}
