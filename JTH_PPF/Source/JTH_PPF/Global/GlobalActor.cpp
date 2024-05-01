// Fill out your copyright notice in the Description page of Project Settings.

#include "Global/GlobalActor.h"
#include "Global/GlobalCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGlobalActor::AGlobalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGlobalActor::OpenCheck() 
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// 킬카운트와 같다면 true 반환
	if (MyCharacter->KillCount == 2)
	{
		return true;
	}
	return false;

}

