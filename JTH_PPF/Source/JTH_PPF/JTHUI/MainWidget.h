// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "AI/AIPlayerCharacter.h"
//#include "Global/GlobalCharacter.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class JTH_PPF_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	UTexture* SetCardIma();

	UFUNCTION(BlueprintCallable)
	float SetMyCharacterHP();

	UFUNCTION(BlueprintCallable)
	float SetMyCharacterMAXHP();

	UFUNCTION(BlueprintCallable)
	float SetMyCharacterLEVELHP();

	UFUNCTION(BlueprintCallable)
	float GetMyCharacterSaveLEVELHP();

	UFUNCTION(BlueprintCallable)
	void SetMyCharacterSaveLEVELHP();

	UFUNCTION(BlueprintCallable)
	float SetMyCharacterDAMAGE();

	UFUNCTION(BlueprintCallable)
	void SetDAMAGE(int DamageUp);

	UFUNCTION(BlueprintCallable)
	float SetMyCharacterARMOR();

	UFUNCTION(BlueprintCallable)
	void SetARMOR(int ARMORUp);

	UFUNCTION(BlueprintCallable)
	void SetMOVE(int MOVEUp);

	UFUNCTION(BlueprintCallable)
	void SetSTUN_DAMAGE(int STUN_DAMAGEUp);

	UFUNCTION(BlueprintCallable)
	float SetMyCharacterKey();

	/*
	UFUNCTION(BlueprintCallable)
	bool TripleCardCheck(UTexture Card1, UTexture Card2, UTexture Card3);
	*/

	/*
	class AAIPlayerCharacter* CurPlayerCharacter;

	int GetHP()
	{
		return PlayHP;
	}

	int GetMAXHP()
	{
		return PlayMAXHP;
	}
	가져온 Hp를 여기서 저장
	*/
	
	UFUNCTION(BlueprintCallable)
	bool CheckAllWidGetHidden();

	UFUNCTION(BlueprintCallable)
	void SetOptionOnOffSwitch()
	{
		OptionOnOff = OptionOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}
	/*
	void SetStatusWindowOnOffSwitch()
	{
		StatusWindowOnOff = StatusWindowOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}*/

	void SetInventoryOnOffSwitch()
	{
		InventoryOnOff = InventoryOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetCardOnOffSwitch()
	{
		CardOnOff = CardOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	void SetTripleCardOnOffSwitch()
	{
		TripleCardOnOff = TripleCardOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}
	


	/*UFUNCTION(BlueprintCallable)
	void PlayerHPe();
	
	class AAIPlayerCharacter* GetAIPlayerCharacter()
	{
		AIPlayerCharacter;
	}*/

protected:
	
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	/*
	* 
	*  playercharacter에서 hp 가져오는 식
	void PlayerHP();

	virtual void MainHP(int _PlayHP)
	{
		PlayHP = _PlayHP;
	}

	virtual void MainMAXHP(int _MAXHP)
	{
		PlayMAXHP = _MAXHP;
	}
	*/

private:
	
	UPROPERTY(Category = "UIOnOff", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility InventoryOnOff = ESlateVisibility::Hidden;

	/*UPROPERTY(Category = "UIOnOff", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility StatusWindowOnOff = ESlateVisibility::Hidden;*/

	UPROPERTY(Category = "UIOnOff", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility OptionOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIOnOff", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility CardOnOff = ESlateVisibility::Hidden;
	
	UPROPERTY(Category = "UIOnOff", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility TripleCardOnOff = ESlateVisibility::Hidden;


	class UInventoryUserWidget* Inven;


	UPROPERTY(Category = "CharacterHPM", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayHP = 0;
	
	UPROPERTY(Category = "CharacterHPM", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayMAXHP = 0;

	UPROPERTY(Category = "CharacterHPM", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayLEVELHP = 0;
    /*
	class AAIPlayerCharacter* AIPlayerCharacter = nullptr;*/
	
	UPROPERTY()
	TArray<UUserWidget*> AllWidGet;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool AllHidden = true;
	
};
