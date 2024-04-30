#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "ActorSubClassData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct JTH_PPF_API FActorSubClassData : public FTableRowBase
{
	GENERATED_BODY()

		FActorSubClassData() {}
	~FActorSubClassData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<AActor> Objects;
};
