// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Global/GlobalGameInstance.h"


// Sets default values
AGlobalCharacter::AGlobalCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGlobalCharacter::BeginPlay()
{
	
	Super::BeginPlay();

	PlayerHP = 0;
	
	// ������ �÷��̾� ĳ������ �����͸� �����Ҷ� ��´�
	{
		UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();
		if (nullptr != Inst)
		{
			SaveCurPlayerCharacterData = Inst->GetSavePlayerCharacterData(SaveName);
		}
		if (SaveName != "None")
		{

			AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			MyCharacter->PlayerLEVELHP = SaveCurPlayerCharacterData->S_LEVELHP;
			MyCharacter->UiPlayerLEVELHP = SaveCurPlayerCharacterData->S_UiLEVELHP;
			MyCharacter->PlayerDAMAGE = SaveCurPlayerCharacterData->S_ATT;
			MyCharacter->PlayerARMOR = SaveCurPlayerCharacterData->S_DEF;
			MyCharacter->PlayerSTUNDAMAGE = SaveCurPlayerCharacterData->S_STUN;
			MyCharacter->PlayerMOVE = SaveCurPlayerCharacterData->S_MOVE;
			MyCharacter->PlayerHP = SaveCurPlayerCharacterData->S_EXP;
			MyCharacter->PlayerMAXHP = SaveCurPlayerCharacterData->S_MAXEXP;
			MyCharacter->EXP = SaveCurPlayerCharacterData->S_GetEXP;
			MyCharacter->Key = SaveCurPlayerCharacterData->S_KEY;
		}
	}

	GlobalAnimInstance = Cast<UGlobalAnimInstance>(GetMesh()->GetAnimInstance());

	GlobalAnimInstance->AllAnimations = AllAnimations;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGlobalCharacter::OverLap);
}

// Called every frame
void AGlobalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Key == 0)
	{
		Tags.Remove("Key");
	}
	if (Key >= 1)
	{
		Tags.Add("Key");
	}

	// �̰����� �÷��̾� ĳ���Ϳ� �����͸� �����Ѵ�.
	{
		UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();
		if (nullptr != Inst)
		{
			SaveCurPlayerCharacterData = Inst->GetSavePlayerCharacterData(SaveName);
		}
		if (SaveName != "None")
		{

			AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			SaveCurPlayerCharacterData->S_LEVELHP = MyCharacter->PlayerLEVELHP;
			SaveCurPlayerCharacterData->S_UiLEVELHP = MyCharacter->UiPlayerLEVELHP;
			SaveCurPlayerCharacterData->S_ATT = MyCharacter->PlayerDAMAGE;
			SaveCurPlayerCharacterData->S_DEF = MyCharacter->PlayerARMOR;
			SaveCurPlayerCharacterData->S_STUN = MyCharacter->PlayerSTUNDAMAGE;
			SaveCurPlayerCharacterData->S_MOVE = MyCharacter->PlayerMOVE;
			SaveCurPlayerCharacterData->S_EXP = MyCharacter->PlayerHP;
			SaveCurPlayerCharacterData->S_MAXEXP = MyCharacter->PlayerMAXHP;
			SaveCurPlayerCharacterData->S_GetEXP = MyCharacter->EXP;
			SaveCurPlayerCharacterData->S_KEY = MyCharacter->Key;
		}
	}
}

// Called to bind functionality to input
void AGlobalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AGlobalCharacter::OverLap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// ���� HP�� ������� �ִٸ�.
	// ���⼭ ��� 
	// ���� ������ ������ Hp�� ���̶�� �Ҽ� ������
	// �������ϱ�?
	// �Ѿ��ϱ�?
	// Tag
	AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (true == OtherComp->ComponentHasTag(TEXT("Damage")))
	{
		// �÷��̾��� ����( ATT 1+ )
		if (OtherComp->ComponentHasTag(TEXT("PlayerAtt")))
		{
			StunCheck = false;
			// �÷���ĳ������ �θ�(GlobalCharacter)�� PlayerDAMAGE ���� ������� ����Ѵ�.
			//AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			HP -= MyCharacter->PlayerDAMAGE;
			if (LongStunCheck == false) 
			{
				STUNHP -= MyCharacter->PlayerSTUNDAMAGE;
			}
			// ���� ���
			MyCharacter->SetPlaySound(true, 1);

			if (0 >= HP)
			{
				HP = 0;
			}
			else 
			{
				if (0 >= STUNHP) 
				{
					StunCheck = false;
					LongStunCheck = true;
					STUNHP = MAXSTUNHP;
					// ���� ���
					MyCharacter->SetPlaySound(true, 5);
				}
				else 
				{
					if (LongStunCheck == false) 
					{
						StunCheck = true;
					}
					else 
					{
						StunCheck = false;
					}
				}
			}
			return;
		}

		// ������ ����( ATT 3 )
		if (OtherComp->ComponentHasTag(TEXT("BossAtt")))
		{
			//AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (0 < MyCharacter->PlayerARMOR) 
			{
				MyCharacter->PlayerARMOR -= 1;
				return;
			}
			
			PlayerLEVELHP -= 3;
			// ���� ���
			/*  1  */
			MyCharacter->SetPlaySound(true, 2);
			/*  2  */
			MyCharacter->SetPlaySound(true, 3);

			if (0 >= PlayerLEVELHP)
			{
				PlayerLEVELHP = 0;
			}
			LEVELHP = PlayerLEVELHP;
			return;
		}

		// �Ϲݸ����� ����( ATT 1 )
		else 
		{
			//AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (0 < MyCharacter->PlayerARMOR)
			{
				MyCharacter->PlayerARMOR -= 1;
				return;
			}

			PlayerLEVELHP -= 1;
			// ���� ���
			/*  1  */
			MyCharacter->SetPlaySound(true, 2);
			/*  2  */
			MyCharacter->SetPlaySound(true, 3);

			if (0 >= PlayerLEVELHP)
			{
				PlayerLEVELHP = 0;
				// 0 ������ �������� �ʰ� ����
			}
			LEVELHP = PlayerLEVELHP;
		}
		
	}
	
	if (true == OtherComp->ComponentHasTag(TEXT("HeartPostion")))
	{
		//AGlobalCharacter* MyCharacter = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		PlayerHP += EXP;
		// ���� ���
		MyCharacter->SetPlaySound(true, 4);


		if (PlayerHP >= PlayerMAXHP)
		{
			PlayerLEVELHP += 1;
			PlayerHP -= PlayerMAXHP;
			if (EXP >= 10) 
			{
		        EXP -= 2;
			}
			// MAXHP�� 100���� �����Ǿ��־� HP�� 100�� �ǰų� 100�� ������ LEVELHP�� �ø���.
			// ��� ���Ͽ��� ü���� 100���� �߱� ������ �� �̻����� ü���� �ö��� ���� 100���� ����
		}
		//PlayerHP = HP;
		//LEVELHP = PlayerLEVELHP;
	}

	if (true == OtherComp->ComponentHasTag(TEXT("Key")))
	{
		Key += 1;
		// ���� ���
		MyCharacter->SetPlaySound(true, 6);
		//Tags.Add("Key");
	}

	if (true == OtherComp->ComponentHasTag(TEXT("Door")))
	{
		if (Key == 0) 
		{
			return;
		}
		Key -= 1;
		// ���� ���
		//MyCharacter->SetPlaySound(true, ); �������� ����
	}

}






