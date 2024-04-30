// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "InventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class JTH_PPF_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 메모리적으로 엔진전
	static UInventoryUserWidget* InvenWidget;

	UFUNCTION(BlueprintCallable)
	void AddInvenItem(UObject* _Data, UUserWidget* _Widget);

	UFUNCTION(BlueprintCallable)
	void NewWidget(UUserWidget* _Widget);

	void AddGameItem(const struct FItemData* Data);

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTileView* InvenList = nullptr;



};
