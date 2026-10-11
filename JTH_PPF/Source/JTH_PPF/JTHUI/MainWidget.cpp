// Fill out your copyright notice in the Description page of Project Settings.


#include "JTHUI/MainWidget.h"
#include <Global/GlobalCharacter.h>
#include <AI/Monster.h>
#include <Global/GlobalGameInstance.h>
#include <Global/Data/UpgradeCardData.h>
#include "Engine/Texture.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryUserWidget.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Inven = Cast<UInventoryUserWidget>(GetWidgetFromName(TEXT("WBP_Inventory")));
	// Inven = Cast<UInventoryUserWidget>(GetWidgetFromName(TEXT("WBP_Status")));

	AllWidGet.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_Inventory"))));
	AllWidGet.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_Option"))));
	//AllWidGet.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_Status"))));

	FindBossCharacter();
}


void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!IsValid(BossCharacter) || BossCharacter->GetHP() <= 0.f)
	{
		BossHPOnOff = ESlateVisibility::Hidden;
	}
}

// 여기서 리턴하는 bool 값은 지금 상태가 바뀌었다는 AllHidden이 바뀌었다는것을 체크하는 bool 값이 된다.
bool UMainWidget::CheckAllWidGetHidden()
{
	bool AllHiddenCheck = true;

	for (size_t i = 0; i < AllWidGet.Num(); i++)
	{
		if (AllWidGet[i]->GetVisibility() == ESlateVisibility::Visible)
		{
			AllHiddenCheck = false;
		}
	}

	// false였는데 true가 되고
	// true였는데 false가 되는 상황이 오면
	if (AllHiddenCheck != AllHidden)
	{
		AllHidden = AllHiddenCheck;
		return true;
	}

	return false;
}

UTexture* UMainWidget::SetCardIma()
{
	bool Check = false;
	UTexture* Card = nullptr;
	UGlobalGameInstance* GameInstance = GetWorld()->GetGameInstance<UGlobalGameInstance>();
	for (size_t i = 0; i < 1; i++)
	{
		if (Check == false)
		{
			const struct FUpgradeCardData* CurCardData = GameInstance->GetCardData();
			Card = CurCardData->Card;
			Check = true;
		}
	}
	return Card;
}

float UMainWidget::SetMyHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _MyHP = 0;
	if (MyCharacter != nullptr) 
	{
		_MyHP = MyCharacter->MyHP;
	}
	return _MyHP;
}

float UMainWidget::SetMyMAXHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _MyMAXHP = 0;
	if (MyCharacter != nullptr)
	{
		_MyMAXHP = MyCharacter->MyMAXHP;
	}
	return _MyMAXHP;
}

float UMainWidget::SetMyCharacterHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _HP = 0;
	if (MyCharacter != nullptr) 
	{
		_HP = MyCharacter->PlayerHP;
	}
	return _HP;
}

float UMainWidget::SetMyCharacterMAXHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _MAXHP = 0;
	if (MyCharacter != nullptr) 
	{
		_MAXHP = MyCharacter->PlayerMAXHP;
	}
	return _MAXHP;
}

float UMainWidget::SetMyCharacterLEVELHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _LEVELHP = 0;
	if (MyCharacter != nullptr) 
	{
		_LEVELHP = MyCharacter->PlayerLEVELHP;
	}
	return _LEVELHP;
}

float UMainWidget::GetMyCharacterSaveLEVELHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _SaveLEVELHP = 0;
	if (MyCharacter != nullptr)
	{
		_SaveLEVELHP = MyCharacter->UiPlayerLEVELHP;
	}
	return _SaveLEVELHP;
}

void UMainWidget::SetMyCharacterSaveLEVELHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyCharacter->UiPlayerLEVELHP += 1;
}

float UMainWidget::SetMyCharacterDAMAGE()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _DAMAGE = 0; 
	if (MyCharacter != nullptr) 
	{
		_DAMAGE = MyCharacter->PlayerDAMAGE;
	}
	return _DAMAGE;
}

void UMainWidget::SetDAMAGE(int DamageUp)
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyCharacter->PlayerDAMAGE += DamageUp;
	
}

float UMainWidget::SetMyCharacterARMOR()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _ARMOR = 0;
	if (MyCharacter != nullptr) 
	{
		_ARMOR = MyCharacter->PlayerARMOR;
	}
	return _ARMOR;
}

void UMainWidget::SetARMOR(int ARMORUp)
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyCharacter->PlayerARMOR += ARMORUp;
}

void UMainWidget::SetMOVE(int MOVEUp)
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyCharacter->PlayerMOVE += MOVEUp;
}

void UMainWidget::SetSTUN_DAMAGE(int STUN_DAMAGEUp)
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyCharacter->PlayerSTUNDAMAGE += STUN_DAMAGEUp;
}

float UMainWidget::SetMyCharacterKey()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _Key = 0;
	if (MyCharacter != nullptr) 
	{
		_Key = MyCharacter->Key;
	}
	return _Key;
}

void UMainWidget::FindBossCharacter()
{
	BossCharacter = nullptr;

	TArray<AActor*> Monsters;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		AMonster::StaticClass(),
		Monsters
	);

	for (AActor* Actor : Monsters)
	{
		AMonster* Monster = Cast<AMonster>(Actor);

		if (!IsValid(Monster))
		{
			continue;
		}

		// DataName이 "Boss"인 몬스터만 반환하는 기존 함수
		AMonster* Boss = Monster->GetBossCharacter();

		if (IsValid(Boss))
		{
			BossCharacter = Boss;
			BossHPOnOff = IsValid(BossCharacter)
				? ESlateVisibility::Visible
				: ESlateVisibility::Hidden;
			break;
		}
	}
}

void UMainWidget::SetBossCharacter(AMonster* InBoss)
{
	BossCharacter = IsValid(InBoss)
		? InBoss->GetBossCharacter()
		: nullptr;

	BossHPOnOff = IsValid(BossCharacter)
		? ESlateVisibility::Visible
		: ESlateVisibility::Hidden;
}

float UMainWidget::SetBossHP()
{
	if (!IsValid(BossCharacter))
	{
		return 0.f;
	}

	return BossCharacter->GetHP();
}

float UMainWidget::SetBossMAXHP()
{
	if (!IsValid(BossCharacter))
	{
		return 0.f;
	}

	return BossCharacter->GetMAXHP();
}

/*
bool UMainWidget::TripleCardCheck(UTexture Card1,UTexture Card2,UTexture Card3)
{
	FString Card01 = Card1.GetDefaultConfigFilename();
	FString Card02 = Card2.GetDefaultConfigFilename();
	FString Card03 = Card3.GetDefaultConfigFilename();

	if (Card01 == Card02 && Card01 == Card03)
	{
		return true;
	}
	return false;
}
*/
