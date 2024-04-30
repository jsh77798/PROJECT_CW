#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include <AI/AIEnum.h>
#include "PlayerCharacterData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct JTH_PPF_API FPlayerCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	FPlayerCharacterData() {}
	~FPlayerCharacterData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MAXHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float LEVELHP = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ATT = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<ESound, USoundWave*> MapSound;
};