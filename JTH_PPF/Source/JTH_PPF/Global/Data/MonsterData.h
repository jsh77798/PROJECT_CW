#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include <Global/GlobalEnums.h>
#include "MonsterData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct JTH_PPF_API FMonsterData : public FTableRowBase
{
	GENERATED_BODY()

		FMonsterData() {}
	~FMonsterData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MAXHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float STUNHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ATT;
		// 오버렙 됬을 때 내가 받는 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UBehaviorTree* AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TMap<AIState, class UAnimMontage*> MapAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float SearchRange = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float AttackRange = 200.0f;
};

