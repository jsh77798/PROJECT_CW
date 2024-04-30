#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "SubClassData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct JTH_PPF_API FSubClassData : public FTableRowBase
{
	GENERATED_BODY()

		FSubClassData() {}
	~FSubClassData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<UObject> Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UStaticMesh* Mesh;
};
