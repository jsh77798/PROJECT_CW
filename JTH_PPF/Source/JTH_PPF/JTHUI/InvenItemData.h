// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Global/Data/ItemData.h>
#include "InvenItemData.generated.h"

/**
 * 
 */
UCLASS()
class JTH_PPF_API UInvenItemData : public UObject
{
	GENERATED_BODY()

public:
	// ½ÇÁ¦ À§Á¬
	class UInvenItemSlot* Widget;
	int Count = 1;
	const FItemData* Data;
	
};
