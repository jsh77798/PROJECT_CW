// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture.h"
#include "UpgradeCardData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct JTH_PPF_API FUpgradeCardData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FUpgradeCardData() {}
	~FUpgradeCardData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture* Card;
};
