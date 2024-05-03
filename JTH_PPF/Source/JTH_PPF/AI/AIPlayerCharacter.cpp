// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Global/GlobalGameInstance.h>
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundBase.h"
#include <random>
#include "Global/ProjectTile.h"
#include "AIEnum.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

AAIPlayerCharacter::AAIPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//캐릭터 기본 이동속도 설정
	MoveCom = Cast<UCharacterMovementComponent>(GetMovementComponent());
	MoveCom->MaxWalkSpeed = PlayerMOVE;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->bDoCollisionTest = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	FName WeaponSocket(TEXT("B_R_Hand"));
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), WeaponSocket);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->FieldOfView = 45.0f;
	CameraComponent->SetupAttachment(SpringArmComponent);
	// SpringArmComponent
}

/*
void AAIPlayerCharacter::Tick(float Delta)
{
	
	//사운드 재생
	{
		bool SPlaySoundCheck = false;
		int SPlaySoundName = 0;
		SPlaySoundCheck = GetPlaySound();
	    SPlaySoundName = GetPlaySoundName();
		if (SPlaySoundCheck == true) 
		{
			TAssetPtr<USoundBase> SoundToPlay = nullptr;

			TMap<ESound, USoundWave*> _MapSound = CurPlayerCharacterData->MapSound;

			if (SPlaySoundName == 1) 
			{
				SoundToPlay = _MapSound[ESound::SOUND_Attack_Hit];
				UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay.Get(), GetActorLocation());
			}
			if (SPlaySoundName == 2)
			{
				SoundToPlay = _MapSound[ESound::SOUND_Damage_Hit];
				UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay.Get(), GetActorLocation());
			}
			if (SPlaySoundName == 3)
			{
				SoundToPlay = _MapSound[ESound::SOUND_LevelHPDown];
				UGameplayStatics::PlaySound2D(this, SoundToPlay.Get());  //감쇠없는 사운드, UI사운드에 적합하다.
			}
			// 사운드 종료시
			SetPlaySound(false, 0);
		}


	}
}
*/

void AAIPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerRiverAttack"), EKeys::RightMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerRollsAction"), EKeys::LeftShift));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("InventoryWindow"), EKeys::Nine));
	}

	// 키와 함수를 연결합니다.
	// 이 키가 눌리면 이 함수를 실행시켜줘인데.
	// 축일때는 일단 계속 실행시켜줘.
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AAIPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AAIPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AAIPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AAIPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AAIPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AAIPlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &AAIPlayerCharacter::AttackAction);
	PlayerInputComponent->BindAction("PlayerRiverAttack", EInputEvent::IE_Pressed, this, &AAIPlayerCharacter::RiverAttackAction);
	PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AAIPlayerCharacter::JumpAction);
	PlayerInputComponent->BindAction("PlayerRollsAction", EInputEvent::IE_Pressed, this, &AAIPlayerCharacter::RollsAction);
}

void AAIPlayerCharacter::BeginPlay()
{
	SetAllAnimation(MapAnimation);

	Super::BeginPlay();

	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();
	if (nullptr != Inst)
	{
		CurPlayerCharacterData = Inst->GetPlayerCharacterData(DataName);
	}
	//CharacterATT = CurPlayerCharacterData->ATT;
	CharacterHP = CurPlayerCharacterData->HP;
	CharacterMAXHP = CurPlayerCharacterData->MAXHP;
	CharacterLEVELHP = CurPlayerCharacterData->LEVELHP;
	//PlayerDamage(CharacterATT);

	//MainHP(CharacterHP);
	//MainMAXHP(CharacterMAXHP);
	//MainLEVELHP(CharacterLEVELHP);








	GetGlobalAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &AAIPlayerCharacter::MontageEnd);

	GetGlobalAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &AAIPlayerCharacter::AnimNotifyBegin);

	SetAniState(AIAniState::Start);

	//SetAniState(AIAniState::Idle);
}

void AAIPlayerCharacter::MoveSetting() 
{
	MoveCom = Cast<UCharacterMovementComponent>(GetMovementComponent());
	MoveCom->MaxWalkSpeed = PlayerMOVE;

}

void AAIPlayerCharacter::RiverAttackAction()
{
	UAnimInstance* animinstance = GetMesh()->GetAnimInstance();
	AIAniState AniStateValue = GetAniState<AIAniState>();
	if (AniStateValue == AIAniState::Jump || AniStateValue == AIAniState::Rull || 
		AniStateValue == AIAniState::Attack || AniStateValue == AIAniState::Attack02 || 
		AniStateValue == AIAniState::Attack03 || AniStateValue == AIAniState::Stun || AniStateValue == AIAniState::Stun02)
	{
		return;
	}
	SetAniState(AIAniState::RiverAttack);
}

void AAIPlayerCharacter::AttackAction()
{
	UAnimInstance* animinstance = GetMesh()->GetAnimInstance();
	// 여기가 아니라 몽타주가 책임져줘야 한다.
	// 이걸 여기에서 하면 안된다.
	AIAniState AniStateValue = GetAniState<AIAniState>();

	if (AniStateValue == AIAniState::Jump || AniStateValue == AIAniState::Rull || 
		AniStateValue == AIAniState::RiverAttack || AniStateValue == AIAniState::Stun || 
		AniStateValue == AIAniState::Stun02)
	{
		return;
	}

		if (isAttack == false)
		{
			isAttack = true;
			Combo = 1;
			SetAniState(AIAniState::Attack);
		}
		else
		{
			chainCombo = true;
		}

	//SetAniState(AIAniState::Attack);
}
void AAIPlayerCharacter::UnAttackAction()
{
	//AAIPlayerCharacter::UnAttackAction();

	chainCombo = false;
	Combo = 0;
}
void AAIPlayerCharacter::StartAtt(FName NotifyName)
{

}
void AAIPlayerCharacter::EndAttack(FName NotifyName)
{
	if (NotifyName == TEXT("AttackEnd"))
	{
		if (ComboCount == 2) 
		{
			ComboLock = false;
		    SetAniState(AIAniState::Attack02);
		    ComboCount = 0;
		}
		else 
		{
			ComboCount = 2;
		}
	}
	if (NotifyName == TEXT("AttackEnd2"))
	{
		if (ComboCount == 3)
		{
			SetAniState(AIAniState::Attack03);
			ComboCount = 0;
		}
		else
		{
			ComboCount = 3;
		}
	}

}
void AAIPlayerCharacter::JumpAction()
{
	AIAniState AniStateValue = GetAniState<AIAniState>();

	if (AniStateValue == AIAniState::Attack || AniStateValue == AIAniState::Attack02 || AniStateValue == AIAniState::Attack03 || AniStateValue == AIAniState::Rull || AniStateValue == AIAniState::Stun || AniStateValue == AIAniState::Stun02)
	{
		return;
	}
	Jump();
	SetAniState(AIAniState::Jump);
}
void AAIPlayerCharacter::RollsAction()
{
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
	isAttack = false;
	ComboLock = false;
	Combo = 0;
	ComboCount = 0;

	AGlobalCharacter* Character = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// 키보드 입력에 따른 회전 각도 계산
	FRotator DesiredRotation = CalculateRotationFromInput(Character);

	// 캐릭터를 회전시킵니다.
	Character->SetActorRotation(DesiredRotation);

	SetAniState(AIAniState::Rull);
}

FRotator AAIPlayerCharacter::CalculateRotationFromInput(ACharacter* Character)
{
	FString VectorAsString = FString::Printf(TEXT("X: %f, Y: %f, Z: %f"),
		GetCharacterMovement()->Velocity.X, GetCharacterMovement()->Velocity.Y, GetCharacterMovement()->Velocity.Z);

	UE_LOG(LogTemp, Log, TEXT("%s"), *VectorAsString);

	FVector PlayerDir = GetCharacterMovement()->Velocity;

	if (!PlayerDir.IsNearlyZero())
	{
		// 회전을 수행할 수 있는 캐릭터 포인터를 가져옵니다.
		//ACharacter* Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			// 플레이어의 속도 벡터를 정규화합니다.
			PlayerDir.Normalize();

			// 플레이어의 속도 벡터를 기준으로 회전 행렬을 만듭니다.
			FRotator TargetRotation = FRotationMatrix::MakeFromX(PlayerDir).Rotator();

			return TargetRotation;

			// 캐릭터를 플레이어의 이동 방향으로 회전시킵니다.
			//Character->SetActorRotation(TargetRotation);
		}
	}
	return FRotator::ZeroRotator;
}
void AAIPlayerCharacter::MoveRight(float Val)
{

	AIAniState AniStateValue = GetAniState<AIAniState>();

	if (AniStateValue == AIAniState::Attack || AniStateValue == AIAniState::Attack02 || 
		AniStateValue == AIAniState::Attack03 || AniStateValue == AIAniState::Jump || 
		AniStateValue == AIAniState::Rull || AniStateValue == AIAniState::Stun || AniStateValue == AIAniState::Stun02)
	{
		return;
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			// transform to world space and add it
			// 현재 내 회전을 가져와서 y축에 해당하는 축벡터를 얻어오는 겁니다.
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);

			SetAniState(Val > 0.f ? AIAniState::RightMove : AIAniState::LeftMove);
			return;
		}
	}
	else
	{
		if (AniStateValue == AIAniState::RightMove || AniStateValue == AIAniState::LeftMove)
		{
			SetAniState(AIAniState::Idle);
			isAttack = false;
			ComboLock = false;

			Combo = 0;
			ComboCount = 0;
		}
	}
}
void AAIPlayerCharacter::MoveForward(float Val)
{

	AIAniState AniStateValue = GetAniState<AIAniState>();

	if (AniStateValue == AIAniState::Attack || AniStateValue == AIAniState::Attack02 || 
		AniStateValue == AIAniState::Attack03 || AniStateValue == AIAniState::Jump || 
		AniStateValue == AIAniState::Rull || AniStateValue == AIAniState::Stun || AniStateValue == AIAniState::Stun02)
	{
		return;
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	if (Val != 0.f)
	{
		if (Controller)
		{
			// 컨트롤러는 기본적으로
			// charcter 하나씩 붙어 있습니다.

			FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
			AddMovementInput(Direction, Val);

			//FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// 이건 방향일 뿐입니다.
			// transform to world space and add it
			
			//AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
			
			// 탑뷰게임이면 다르게 나오게 되는데.
			// 지금은 TPS를 하고 있기 때문에 컨트롤러의 회전이나 액터의 회전이나 같아요.
			// AddMovementInput(GetActorForwardVector(), Val);

			SetAniState(Val > 0.f ? AIAniState::ForwardMove : AIAniState::BackwardMove);
			return;
		}
	}
	else
	{
		if (AniStateValue == AIAniState::ForwardMove || AniStateValue == AIAniState::BackwardMove)
		{
			SetAniState(AIAniState::Idle);
			isAttack = false;
			ComboLock = false;

			Combo = 0;
			ComboCount = 0;
		}
	}
}
void AAIPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AAIPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AAIPlayerCharacter::CHDamage(bool BigDamageCheck, bool DamageCheck)
{
	if (DamageCheck == true)
	{
		SetAniState(AIAniState::Stun);
	}
	if(BigDamageCheck == true)
	{
		SetAniState(AIAniState::Stun02);
	}
	return;
}
void AAIPlayerCharacter::Death()
{
	SetAniState(AIAniState::Death);
}

void AAIPlayerCharacter::MontageEnd(UAnimMontage* Anim, bool _Inter)
{
	TSubclassOf<UAnimInstance> Inst = AAIPlayerCharacter::StaticClass();

	// Anim 종료된 몽타주
	if (MapAnimation[AIAniState::Start] == Anim)
	{
		SetAniState(AIAniState::Idle);
	}
	if (MapAnimation[AIAniState::Stun] == Anim)
	{
		SetAniState(AIAniState::Idle);
	}
	if (MapAnimation[AIAniState::Stun02] == Anim)
	{
		SetAniState(AIAniState::Idle);
	}
	
	if (MapAnimation[AIAniState::RiverAttack] == Anim)
	{
		SetAniState(AIAniState::Idle);
	}

	if (MapAnimation[AIAniState::Attack] == Anim)
	{
		if (Combo == 2)
		{
			Weapon->SetCollisionProfileName(TEXT("NoCollision"));
			SetAniState(AIAniState::Idle);
			isAttack = false;
			ComboLock = false;
			
			Combo = 0;
			ComboCount = 0;
		}
	}

	if (MapAnimation[AIAniState::Attack02] == Anim)
	{
		if (Combo == 3)
		{
			Weapon->SetCollisionProfileName(TEXT("NoCollision"));
			SetAniState(AIAniState::Idle);
			isAttack = false;
			ComboLock = false;
			
			Combo = 0;
			ComboCount = 0;
		}
	}

	if (MapAnimation[AIAniState::Attack03] == Anim)
	{
		if (Combo == 0)
		{
			Weapon->SetCollisionProfileName(TEXT("NoCollision"));
			SetAniState(AIAniState::Idle);
			isAttack = false;
			ComboLock = false;
			
			Combo = 0;
			ComboCount = 0;
		}
	}
	
	if (MapAnimation[AIAniState::Jump] == Anim)
	{
		Weapon->SetCollisionProfileName(TEXT("NoCollision"));
		SetAniState(AIAniState::Idle);
		isAttack = false;
		ComboLock = false;

		Combo = 0;
		ComboCount = 0;
	}

	if (MapAnimation[AIAniState::Rull] == Anim)
	{
		SetAniState(AIAniState::Idle);
	}
}

void AAIPlayerCharacter::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	TSubclassOf<UObject> vEndAttack = Inst->GetSubClass(TEXT("EndAttack"));

	TSubclassOf<UObject> Effect = Inst->GetSubClass(TEXT("Effect"));

	TSubclassOf<UObject> RangeAttack = Inst->GetSubClass(TEXT("PlayerRangeAttack"));

	
	if (NotifyName == TEXT("InvincibilityStart"))
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Roll"));
	}

	if (NotifyName == TEXT("InvincibilityEnd"))
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	}

	//EndAttack();
	if (NotifyName == TEXT("AttackStart"))
	{
		StartAtt(NotifyName);
	}

	if (NotifyName == TEXT("AttackEnd") || NotifyName == TEXT("AttackEnd2"))
	{
        EndAttack(NotifyName);
        Weapon->SetCollisionProfileName(TEXT("NoCollision"));
	}

	if (NotifyName == TEXT("HitStart"))
	{
		Weapon->SetCollisionProfileName(TEXT("PlayerAttack"));
	}

	if (NotifyName == TEXT("HitEnd"))
	{
		Weapon->SetCollisionProfileName(TEXT("NoCollision"));
	}

	if (NotifyName == TEXT("StepSound01"))
	{
		TAssetPtr<USoundBase> SoundToPlay = nullptr;
		
		TMap<ESound, USoundWave*> _MapSound = CurPlayerCharacterData->MapSound;
		
		int SoundNum = MyRandom(0, 2);

		switch (SoundNum) {
		case 0:
			SoundToPlay = _MapSound[ESound::SOUND01];
			break;
		case 1:
			SoundToPlay = _MapSound[ESound::SOUND02];
			break;
		case 2:
			SoundToPlay = _MapSound[ESound::SOUND03];
			break;
		default:
			SoundToPlay = nullptr;
			break;
		}
		
		// 사운드 재생
		if (SoundToPlay != nullptr) 
		{
			UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay.Get(), GetActorLocation());
			//UGameplayStatics::PlaySound2D(this, SoundToPlay.Get());  //감쇠없는 사운드, UI사운드에 적합하다.
		}
	}
	
	if (NotifyName == TEXT("StepSound02"))
	{
		TAssetPtr<USoundBase> SoundToPlay = nullptr;
		
		TMap<ESound, USoundWave*> _MapSound = CurPlayerCharacterData->MapSound;

		int SoundNum = MyRandom(0, 2);

		switch (SoundNum) {
		case 0:
			SoundToPlay = _MapSound[ESound::SOUND04];
			break;
		case 1:
			SoundToPlay = _MapSound[ESound::SOUND05];
			break;
		case 2:
			SoundToPlay = _MapSound[ESound::SOUND06];
			break;
		default:
			SoundToPlay = nullptr;
			break;
		}

		// 사운드 재생
		if (SoundToPlay != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay.Get(), GetActorLocation());
		}
	}



	/*
	if (nullptr != Effect)
	{
		FTransform Trans;
		FVector Pos;
		TArray<UActorComponent*> MeshEffects = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("WeaponEffect"));
		TArray<UActorComponent*> StaticMeshs = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("WeaponMesh"));
		


		USceneComponent* EffectCom = Cast<USceneComponent>(MeshEffects[0]);
		Pos = EffectCom->GetComponentToWorld().GetLocation();

		// 이펙트 만들기
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(Effect);
			// 본의 위치를 얻어오는 법.
			// 내가 얻어오고 싶은 정보가 있다. 누가 가지고 있을까?
			//USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
			//Trans = SkeletalMeshComponent->GetSocketTransform(TEXT("B_R_Weapon"));
			//Pos = Trans.GetLocation();
			// UActorComponent* ActorComponent = GetComponentByClass(UStaticMeshComponent::StaticClass());
			// TArray<UActorComponent*> ActorComponents = GetComponentsByClass(UStaticMeshComponent::StaticClass());
			// UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(ActorComponents[0]);
			// Pos = StaticMeshComponent->GetComponentToWorld().GetLocation();
			Actor->SetActorLocation(Pos);
			Actor->SetActorRotation(GetActorRotation());
			Actor->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
		}

		// 발사체 만들기
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(RangeAttack);

			AProjectTile* ProjectTile = Cast<AProjectTile>(Actor);

			ProjectTile->SetActorLocation(Pos);
			ProjectTile->SetActorRotation(GetActorRotation());
			ProjectTile->GetSphereComponent()->SetCollisionProfileName(TEXT("PlayerAttack"), true);
		}
	}
	*/
}

void AAIPlayerCharacter::PlaySound(int SoundNum)
{
	TAssetPtr<USoundBase> SoundToPlay = nullptr;

	TMap<ESound, USoundWave*> _MapSound = CurPlayerCharacterData->MapSound;

	if (SoundNum == 1) 
	{
		SoundToPlay = _MapSound[ESound::SOUND_Attack_Hit];
		UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay.Get(), GetActorLocation());
	}
	if (SoundNum == 2) 
	{
		SoundToPlay = _MapSound[ESound::SOUND_Damage_Hit];
		UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay.Get(), GetActorLocation());
	}
	if (SoundNum == 3) 
	{
		SoundToPlay = _MapSound[ESound::SOUND_LevelHPDown];
		UGameplayStatics::PlaySound2D(this, SoundToPlay.Get());  //감쇠없는 사운드, UI사운드에 적합하다.
	}
	if (SoundNum == 4)
	{
		SoundToPlay = _MapSound[ESound::SOUND_ExpUp];
		UGameplayStatics::PlaySound2D(this, SoundToPlay.Get());  //감쇠없는 사운드, UI사운드에 적합하다.
	}
	if (SoundNum == 5)
	{
		SoundToPlay = _MapSound[ESound::SOUND_Stun];
		UGameplayStatics::PlaySound2D(this, SoundToPlay.Get());  //감쇠없는 사운드, UI사운드에 적합하다.
	}
	if (SoundNum == 6)
	{
		SoundToPlay = _MapSound[ESound::SOUND_KeyUp];
		UGameplayStatics::PlaySound2D(this, SoundToPlay.Get());  //감쇠없는 사운드, UI사운드에 적합하다.
	}
	// 사운드 종료시
	SetPlaySound(false, 0);
}

/*void AAIPlayerCharacter::PlayerHPCheck()
{
	GetGlobalCharacter()->GetHP();
	PlayerHP = GetHP();
	
}*/
/*
UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerJumpAxis", EKeys::E, -1.f));
*/