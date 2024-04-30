// Fill out your copyright notice in the Description page of Project Settings.


#include "JTHUI/InventoryUserWidget.h"
#include "Components/TileView.h"
#include <Global/GlobalGameInstance.h>
#include "InvenItemSlot.h"
#include "InvenItemData.h"


// ������ ���赵�� ����.
UInventoryUserWidget* UInventoryUserWidget::InvenWidget = nullptr;

// GameMode�ƴϸ� HUD�� �˰��ϴ°� ���� �����ϴ�.

// �����Ϳ� �������� �и��Ǿ�� �Ѵ�.
void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InvenWidget = this;

	InvenList = Cast<UTileView>(GetWidgetFromName(TEXT("InvenTileView")));

	// ���⿡�ٰ� �� �־���� �ϴ����� ���� ������� ����.

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

	// ��Ŀ�� ������� ��ȯ�Ǿ ���� �������� �ǹ��Ѵ�.
	// ��Ŀ�� ������ ��Ȯ�ϰ� �������ڸ� �������Ʈ������ ��ȿ�ϴ�.
	// ȭ�鿡���� ��ǥ�踦 �������� ó���ѰͰ�.
	// MyGeometry.GetAbsolutePosition();

	// SetPositionInViewport(FVector2D{0, 0});

	// ƽ�� ���Դٴ°��� �κ��丮�� ������ �������� �� ��������ٴ� �̾߱��̴�.
	const TArray<UObject*>& Items = InvenList->GetListItems();
	for (size_t i = 0; i < Items.Num(); i++)
	{
		UInvenItemData* DataObject = Cast<UInvenItemData>(Items[i]);

		if (nullptr == DataObject->Widget)
		{
			// ���õɶ����� ��ٸ��� �ȴ�.
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
	// ��ü ������
	const TArray<UObject*>& Items = InvenList->GetListItems();

	// �ߺ������� �����۵��� �ѹ��� ���캸��

	for (size_t i = 0; i < Items.Num(); i++)
	{
		UInvenItemData* DataObject = Cast<UInvenItemData>(Items[i]);

		if (nullptr == DataObject->Data)
		{
			// �����ͱ����� ������ �����ϴ�.
			// ����ִ� �κ��̴�.
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