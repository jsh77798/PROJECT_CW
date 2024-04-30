// Fill out your copyright notice in the Description page of Project Settings.


#include "JTHUI/GameHUD.h"

AGameHUD::AGameHUD()
{

}

AGameHUD::~AGameHUD()
{

}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	
	
	// 실제 존재하는 블루프린트의 레퍼런스를 경로를 가져오는 방법은 아래와 같다.
	FSoftClassPath ClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/GamePlayeBluePrint/GameUI/WBP_PlayerGameScreen.WBP_PlayerGameScreen'"));
	TSubclassOf<UUserWidget> MainWidgetClass = ClassPath.TryLoadClass<UUserWidget>();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	MainWidget = Cast<UMainWidget>(Widget);
	MainWidget->AddToViewport();
	
	{
		//UUserWidget* Window = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("TalkTextWindow")));


		// Window->SetVisibility(ESlateVisibility::Hidden);
		// Window->Visibility = ESlateVisibility::Visible;


	}
	/*
	{
		UUserWidget* Window = Cast<UUserWidget>(MainWidget->GetWidgetFromName(TEXT("StatusWindow")));
	}*/

}

void AGameHUD::Tick(float _Delta)
{
	Super::Tick(_Delta);

	// /Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UIEx/WBP_UIEX.WBP_UIEX'
}