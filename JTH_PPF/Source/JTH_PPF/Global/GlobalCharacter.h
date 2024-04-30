// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Global/GlobalAnimInstance.h>
#include <Global/Data/PlayerCharacterData.h>
#include <Global/Data/SaveLevelData.h>
#include <random>
#include "GlobalCharacter.generated.h"

UCLASS()
class JTH_PPF_API AGlobalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGlobalCharacter();
	/*
	UPROPERTY(Category = "ATT", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName AttDataName = "NONE";

	struct FPlayerCharacterData* CurPlayerCharacterData;

	int characterATT = 0;
	*/
	//사운드 재생
	//struct FPlayerCharacterData* G_CurPlayerCharacterData;

	//TAssetPtr<USoundBase> G_SoundToPlay = nullptr;
	//TMap<ESound, USoundWave*> G_MapSound;
	//TMap<ESound, USoundWave*> _G_MapSound = G_CurPlayerCharacterData->MapSound;

	struct FSaveLevelData* SaveCurPlayerCharacterData;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName SaveName = "NONE";

	UPROPERTY(Category = "ATT", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName GrobalAttDataName = "Data";

	UPROPERTY(Category = "PlayerHp", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerHP = 0;

	UPROPERTY(Category = "PlayerMaxHp", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerMAXHP = 0;

	UPROPERTY(Category = "LevelHp", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerLEVELHP = 0;

	UPROPERTY(Category = "LevelHp", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float UiPlayerLEVELHP = 1;

	UPROPERTY(Category = "PlayerDamage", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerDAMAGE = 1;

	UPROPERTY(Category = "PlayerDamage", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerSTUNDAMAGE = 10;

	UPROPERTY(Category = "PlayerARMOR", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerARMOR = 0;

	UPROPERTY(Category = "PlayerMOVE", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerMOVE = 350;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Key = 0;

	// 나의 랜덤함수
	int MyRandom(int A, int B) 
	{
		// 시드값을 얻기 위한 random_device 생성.
		std::random_device rd;

		// random_device 를 통해 난수 생성 엔진을 초기화 한다.
		std::mt19937 gen(rd());

		// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
		std::uniform_int_distribution<int> dis(A, B);

		int MyRand = dis(gen);
		return MyRand;
	}

	//사운드 재생 체크
	UPROPERTY(Category = "PlayerMOVE", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool PlaySoundCheck = false;

	UPROPERTY(Category = "PlayerMOVE", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int PlaySoundName = 0;

	UFUNCTION()
	void SetPlaySound(bool _PlaySoundCheck, int _PlaySoundName)
	{
		PlaySoundCheck = _PlaySoundCheck;
		PlaySoundName = _PlaySoundName;
	}

	UFUNCTION(BlueprintCallable)
	bool GetPlaySound()
	{
		return PlaySoundCheck;
	}

	UFUNCTION(BlueprintCallable)
	int GetPlaySoundName() 
	{
		return PlaySoundName;
	}


	void SetHP(int _HP)
	{
		HP -= _HP;
	}

	void AddHP(int _HP)
	{
		HP += _HP;
	}

	int GetHP()
	{
		return HP;
	}

	int GetLevelHP()
	{
		return PlayerLEVELHP;
	}

	int GetATT()
	{
		return Att;
	}

	int GetMAXHP()
	{
		return MAXHP;
	}

	int GetAniState()
	{
		return AniState;
	}

	bool GetStunCheck()
	{
		return StunCheck;
	}

	void SetStunCheck(bool _StunCheck)
	{
		StunCheck = _StunCheck;
	}

	bool GetLongStunCheck()
	{
		return LongStunCheck;
	}

	void SetLongStunCheck(bool _LongStunCheck)
	{
		LongStunCheck = _LongStunCheck;
	}

	template<typename EnumType>
	EnumType GetAniState()
	{
		return static_cast<EnumType>(AniState);
	}

	template<typename EnumType>
	void SetAniState(EnumType _AniState)
	{
		AniState = static_cast<int>(_AniState);
	}

	void SetAniState(int _AniState)
	{
		AniState = _AniState;
	}

	class UGlobalAnimInstance* GetGlobalAnimInstance()
	{
		return GlobalAnimInstance;
	}

	template<typename EnumType>
	class UAnimMontage* GetAnimMontage(EnumType _Index)
	{
		return GetAnimMontage(static_cast<int>(_Index));
	}

	class UAnimMontage* GetAnimMontage(int _Index)
	{
		if (false == AllAnimations.Contains(_Index))
		{
			return nullptr;
		}

		return AllAnimations[_Index];
	}

	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& _MapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> Pair : _MapAnimation)
		{
			AllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}

	UFUNCTION()
		void PushComponent(UActorComponent* _Component)
	{
		MgrComponent.Add(_Component);
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	template<typename EnumType>
	void PushAnimation(EnumType _Index, class UAnimMontage* _Montage)
	{
		PushAnimation(static_cast<int>(_Index), _Montage);
	}

	void PushAnimation(int _Index, class UAnimMontage* _Montage)
	{
		if (true == AllAnimations.Contains(_Index))
		{
			return;
		}

		AllAnimations.Add(_Index, _Montage);
	}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
		void OverLap(class UPrimitiveComponent* OverlappedComponent,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);


	//virtual void Damage(AActor* _Actor) {}

		virtual void Damage(int _Att)
		{
			Att = _Att;
		}
		//virtual 
		//virtual void PlayerDamage(int _Att)
		//{
		//	PlayerDAMAGE = _Att;
		//}

		virtual void MainHP(int _HP)
		{
			HP = _HP;
		}

		virtual void MainMAXHP(int _MAXHP)
		{
			MAXHP = _MAXHP;
			PlayerMAXHP = MAXHP;
		}

		virtual void MainSTUNHP(int _STUNHP)
		{
			STUNHP = _STUNHP;
			MAXSTUNHP = STUNHP;
		}

		virtual void MainLEVELHP(int _LEVELHP)
		{
			PlayerLEVELHP = _LEVELHP;
		}

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UActorComponent*> MgrComponent;


private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int AniState = 0;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<int, class UAnimMontage*> AllAnimations;

	class UGlobalAnimInstance* GlobalAnimInstance = nullptr;
	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float EXP = 40;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	    float HP = 0;
	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MAXHP = 0;
	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float STUNHP = 0;
	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MAXSTUNHP = 0;
	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float LEVELHP = 1;
	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	    int Att = 0;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool StunCheck = false;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool LongStunCheck = false;

};
