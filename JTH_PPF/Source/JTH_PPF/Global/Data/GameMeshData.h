#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "GameMeshData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct JTH_PPF_API FGameMeshData : public FTableRowBase
{
	GENERATED_BODY()

		FGameMeshData() {}
	~FGameMeshData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UStaticMesh* Mesh;
};
