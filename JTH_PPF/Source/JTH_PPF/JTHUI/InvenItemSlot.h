// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Global/Data/ItemData.h>
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include <JTHUI/InvenItemData.h>
#include "InvenItemSlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotFunction);


/**
 * 
 */
UCLASS()
class JTH_PPF_API UInvenItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemBackVisibility = ESlateVisibility::Visible;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemIconVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemCountVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ItemType ItemTypeValue = ItemType::NONE;

	UPROPERTY(Category = "Icon", EditAnywhere, BlueprintReadWrite)
	UImage* ItemIconImage = nullptr;

	UPROPERTY(Category = "Icon", EditAnywhere, BlueprintReadWrite)
	UImage* ItemIconBack = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
	UTextBlock* ItemCountBlock = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
	int ItemCountValue = 0;

	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FORCEINLINE UInvenItemData* GetItemDataObject()
	{
		return ItemData;
	}

	void SetItemData(UInvenItemData* _ItemData);

	void SlotDataCheck();

	UFUNCTION(BlueprintCallable)
	void DragSetting(UInvenItemSlot* _OtherDragSlot);

	UFUNCTION(BlueprintCallable)
	void MoveSetting(UInvenItemSlot* _OtherDragSlot);

	UFUNCTION(BlueprintCallable)
	bool IsEmpty()
	{
		return ItemData->Data == nullptr;
	}

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FSlotFunction ItemChangeFunction;

	UFUNCTION(BlueprintCallable)
	UInvenItemData* GetItemData()
	{
		return ItemData;
	}

private:
	UInvenItemData* ItemData = nullptr;
	
};
