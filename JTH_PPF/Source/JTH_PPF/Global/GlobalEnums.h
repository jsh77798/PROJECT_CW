#pragma once

#include "CoreMinimal.h"

// �ִϸ��̼ǿ� �����Ұų�
// ĳ���Ϳ� ������ �ų�?

// ���Ϳ� �÷��̾ ���� ��� �ִϸ��̼� ���¿� ���ؼ� ������ �����ϳĸ� �����غ���
// �Ұ����ϴٸ� Enum�� ����� �ȵȴ�.


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
	ATTACK02 UMETA(DisplayName = "GBATTACK02"),   // Sub ������� ���� �ִϸ��̼� �̳�
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
