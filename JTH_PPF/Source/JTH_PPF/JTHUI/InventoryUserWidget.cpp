// Fill out your copyright notice in the Description page of Project Settings.


#include "JTHUI/InventoryUserWidget.h"
#include "Components/TileView.h"
#include <Global/GlobalGameInstance.h>
#include "InvenItemSlot.h"
#include "InvenItemData.h"


// 굉장히 위험도가 높다.
UInventoryUserWidget* UInventoryUserWidget::InvenWidget = nullptr;

// GameMode아니면 HUD가 알게하는게 가장 좋습니다.

// 데이터와 랜더링은 분리되어야 한다.
void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InvenWidget = this;

	InvenList = Cast<UTileView>(GetWidgetFromName(TEXT("InvenTileView")));

	// 여기에다가 뭘 넣어줘야 하는지가 내일 배워야할 내용.

	for (size_t i = 0; i < 49; i++)
	{
		UInvenItemData* ItemObject = NewObject<UInvenItemData>();
		ItemObject->Data = nullptr;
		InvenList->AddItem(ItemObject);
	}

	UGlobalGameInstance* GameInstance = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	const TArray<UObject*>& Items = InvenList->GetListItems();
	for (size_t i = 0; i < 3; i++)
	{
		UInvenItemData* DataObject = Cast<UInvenItemData>(Items[i]);
		DataObject->Data = GameInstance->GetRandomItemData();
	}
}

void UInventoryUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 앵커와 상관없이 변환되어서 들어온 포지션을 의미한다.
	// 앵커의 개념은 정확하게 설명하자면 블루프린트에서만 유효하다.
	// 화면에서의 좌표계를 기준으로 처리한것과.
	// MyGeometry.GetAbsolutePosition();

	// SetPositionInViewport(FVector2D{0, 0});

	// 틱에 들어왔다는것은 인벤토리가 열리고 아이템이 다 만들어졌다는 이야기이다.
	const TArray<UObject*>& Items = InvenList->GetListItems();
	for (size_t i = 0; i < Items.Num(); i++)
	{
		UInvenItemData* DataObject = Cast<UInvenItemData>(Items[i]);

		if (nullptr == DataObject->Widget)
		{
			// 세팅될때까지 기다리면 된다.
			continue;
		}

		UInvenItemSlot* SlotWidget = DataObject->Widget;
		SlotWidget->SlotDataCheck();
	}


}

void UInventoryUserWidget::AddInvenItem(UObject* _Data, UUserWidget* _Widget)
{
	UInvenItemSlot* ItemSlotWidget = Cast<UInvenItemSlot>(_Widget);

	UInvenItemData* InvenSlotData = Cast<UInvenItemData>(_Data);

	if (nullptr == ItemSlotWidget)
	{
		return;
	}

	InvenSlotData->Widget = ItemSlotWidget;
	ItemSlotWidget->SetItemData(InvenSlotData);

	int a = 0;
}

void UInventoryUserWidget::AddGameItem(const FItemData* Data)
{
	// 전체 아이템
	const TArray<UObject*>& Items = InvenList->GetListItems();

	// 중복가능한 아이템들을 한번다 살펴보고

	for (size_t i = 0; i < Items.Num(); i++)
	{
		UInvenItemData* DataObject = Cast<UInvenItemData>(Items[i]);

		if (nullptr == DataObject->Data)
		{
			// 데이터까지만 세팅해 놓습니다.
			// 비어있는 인벤이다.
			DataObject->Data = Data;
			return;
		}

		if (DataObject->Data == Data
			&& DataObject->Count < Data->StackMax)
		{
			++DataObject->Count;
			return;
		}
	}


	return;
}


void UInventoryUserWidget::NewWidget(UUserWidget* _Widget)
{
	int a = 0;
}