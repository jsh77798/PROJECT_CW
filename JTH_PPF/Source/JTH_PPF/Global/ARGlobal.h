// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ARGlobal.generated.h"

/**
 *
 */
UCLASS()
class JTH_PPF_API UARGlobal : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FRandomStream MainRandom;

	UFUNCTION(BlueprintCallable, Category = "ARGlobal")
		static void ARDebugTextInit();

	//����� �ؽ�Ʈ�� ������ ���ؼ� ȭ�鿡 �ѷ��ִ� �Լ�.
	UFUNCTION(BlueprintCallable, Category = "ARGlobal", meta = (DefaultToSelf = "_Object"))
		static void ARDebugTextPrint(class AActor* _Object, const FString& _Text);

	static class UGlobalDebugUserWidget* DebugWidget;
};
