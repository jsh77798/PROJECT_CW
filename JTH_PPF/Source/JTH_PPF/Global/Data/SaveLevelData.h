#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include <AI/AIEnum.h>
#include "SaveLevelData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct JTH_PPF_API FSaveLevelData : public FTableRowBase
{
	GENERATED_BODY()

	FSaveLevelData() {}
	~FSaveLevelData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_EXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_MAXEXP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_GetEXP = 40;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_LEVELHP = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_UiLEVELHP = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_ATT = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_DEF = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_STUN = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_MOVE = 350;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float S_KEY = 0;

};