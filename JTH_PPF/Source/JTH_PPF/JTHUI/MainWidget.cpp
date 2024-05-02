// Fill out your copyright notice in the Description page of Project Settings.


#include "JTHUI/MainWidget.h"
#include <Global/GlobalCharacter.h>
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

	
}


void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	


	// //PlayerHPe();
	// �⺻���� �̵��̳� �̷� �ý�����ü�� �ٸ��ٴ°��� ����ؾ� �Ѵ�.
	// Inven->SetPositionInViewport({100, 100});
	// Inven->SetAnchorsInViewport();
}

// ���⼭ �����ϴ� bool ���� ���� ���°� �ٲ���ٴ� AllHidden�� �ٲ���ٴ°��� üũ�ϴ� bool ���� �ȴ�.
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

	// false���µ� true�� �ǰ�
	// true���µ� false�� �Ǵ� ��Ȳ�� ����
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
	int _MyHP = MyCharacter->MyHP;
	return _MyHP;
}

float UMainWidget::SetMyMAXHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _MyMAXHP = MyCharacter->MyMAXHP;
	return _MyMAXHP;
}

float UMainWidget::SetMyCharacterHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _HP = MyCharacter->PlayerHP;
	return _HP;
}

float UMainWidget::SetMyCharacterMAXHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _MAXHP = MyCharacter->PlayerMAXHP;
	return _MAXHP;
}

float UMainWidget::SetMyCharacterLEVELHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _LEVELHP = MyCharacter->PlayerLEVELHP;
	return _LEVELHP;
}

float UMainWidget::GetMyCharacterSaveLEVELHP()
{
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int _SaveLEVELHP = MyCharacter->UiPlayerLEVELHP;
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
	int _DAMAGE = MyCharacter->PlayerDAMAGE;
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
	int _ARMOR = MyCharacter->PlayerARMOR;
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
	int _Key = MyCharacter->Key;
	return _Key;
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
