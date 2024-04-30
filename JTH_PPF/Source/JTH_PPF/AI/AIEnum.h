#pragma once

#include "CoreMinimal.h"

// 애니메이션에 집중할거냐
// 캐릭터에 집중할 거냐?

// 몬스터와 플레이어가 정말 모든 애니메이션 상태에 대해서 공유가 가능하냐를 생각해보고
// 불가능하다면 Enum은 사용이 안된다.


UENUM(BlueprintType)
enum class AIAniState : uint8
{
	None UMETA(DisplayName = "AINone"),
	Idle UMETA(DisplayName = "AIIDLE"),
	LeftMove UMETA(DisplayName = "AILFTM"),
	RightMove UMETA(DisplayName = "AIRGTM"),
	ForwardMove UMETA(DisplayName = "AIFWDM"),
	BackwardMove UMETA(DisplayName = "AIBKWM"),
	Jump UMETA(DisplayName = "AIJUMP"),
	Rull UMETA(DisplayName = "AIRULL"),
	Attack UMETA(DisplayName = "AIATTACK"),
	Attack02 UMETA(DisplayName = "AIATTACK02"),
	Attack03 UMETA(DisplayName = "AIATTACK03"),
	RiverAttack UMETA(DisplayName = "AIRIVERATTACK"),
	Start UMETA(DisplayName = "AISTART"),
	Stun UMETA(DisplayName = "AISTUN"),
	Stun02 UMETA(DisplayName = "AISTUN02"),
	Death UMETA(DisplayName = "AIDEATH"),
};

UENUM(BlueprintType)
enum class ESound : uint8
{
	NONE UMETA(DisplayName = "SNONE"),
	SOUND01 UMETA(DisplayName = "SOUND01"),
	SOUND02 UMETA(DisplayName = "SOUND02"),
	SOUND03 UMETA(DisplayName = "SOUND03"),
	SOUND04 UMETA(DisplayName = "SOUND04"),
	SOUND05 UMETA(DisplayName = "SOUND05"),
	SOUND06 UMETA(DisplayName = "SOUND06"),
	SOUND_Attack_Hit UMETA(DisplayName = "SOUND_Attack_Hit"),
	SOUND_Damage_Hit UMETA(DisplayName = "SOUND_Damage_Hit"),
	SOUND_LevelHPDown UMETA(DisplayName = "SOUND_LevelHPDown"),
	SOUND_ExpUp UMETA(DisplayName = "SOUND_ExpUp"),
	SOUND_Stun UMETA(DisplayName = "SOUND_Stun"),
	SOUND_KeyUp UMETA(DisplayName = "SOUND_KeyUp"),
};


