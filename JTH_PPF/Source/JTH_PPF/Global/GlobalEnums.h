#pragma once

#include "CoreMinimal.h"

// 애니메이션에 집중할거냐
// 캐릭터에 집중할 거냐?

// 몬스터와 플레이어가 정말 모든 애니메이션 상태에 대해서 공유가 가능하냐를 생각해보고
// 불가능하다면 Enum은 사용이 안된다.


UENUM(BlueprintType)
enum class AIState : uint8
{
	NONE UMETA(DisplayName = "GBNONE"),
	IDLE UMETA(DisplayName = "GBIDLE"),
	MOVE UMETA(DisplayName = "GBMOVE"),
	RETURN UMETA(DisplayName = "GBRETURN"),
	PATROL UMETA(DisplayName = "GBPATROL"),
	ATTACK UMETA(DisplayName = "GBATTACK"),
	DEATH UMETA(DisplayName = "GBDEATH"),
	STUN UMETA(DisplayName = "GBSTUN"),
	SLOWMOVE UMETA(DisplayName = "GBSLOWMOVE"),
	ATTACK02 UMETA(DisplayName = "GBATTACK02"),   // Sub 여기부터 서브 애니메이션 이넘
	STUN02 UMETA(DisplayName = "GBSTUN02"),
	REST UMETA(DisplayName = "GBREST"),
};

UENUM(BlueprintType)
enum class ItemType : uint8
{
	NONE UMETA(DisplayName = "NONEITEM"),
	ARMOR UMETA(DisplayName = "AROMR"),
	WEAPON UMETA(DisplayName = "WEAPON"),
	POSTION UMETA(DisplayName = "POTION"),
	
};
