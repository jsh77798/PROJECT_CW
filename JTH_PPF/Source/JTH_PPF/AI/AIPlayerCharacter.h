// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GlobalCharacter.h"
#include "AIEnum.h"
#include <Global/Data/PlayerCharacterData.h>
#include <Global/Data/SaveLevelData.h>
#include "AIPlayerCharacter.generated.h"


/**
 *
 */
UCLASS()
class JTH_PPF_API AAIPlayerCharacter : public AGlobalCharacter
{
	GENERATED_BODY()


public:
	AAIPlayerCharacter();

	UPROPERTY(EditAnywhere, Category = "WMesh")
	UStaticMeshComponent* Weapon;

	UCharacterMovementComponent* MoveCom;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName DataName = "NONE";

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isAttack = false;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Combo = 0;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ComboCount = 0;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool chainCombo = false;

	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ComboLock = false;

	struct FPlayerCharacterData* CurPlayerCharacterData;

	//bool Rollcheck = false;

	//UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CharacterATT = 1;

	float CharacterHP = 0;
	float CharacterMAXHP = 0;
	float CharacterLEVELHP = 0;

	void RiverAttackAction();
	
	void AttackAction();

	FRotator CalculateRotationFromInput(ACharacter* Character);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	class UAnimMontage* attackMontage;

	UFUNCTION(BlueprintCallable)
	void CHDamage(bool BigDamageCheck, bool DamageCheck);

	UFUNCTION(BlueprintCallable)
	void Death();
	
	UFUNCTION(BlueprintCallable)
	void StartAtt(FName NotifyName);

	UFUNCTION(BlueprintCallable)
	void EndAttack(FName NotifyName);

	UFUNCTION(BlueprintCallable)
	void MoveSetting();

	UFUNCTION(BlueprintCallable)
	void PlaySound(int SoundNum);

	//UFUNCTION(BlueprintCallable)
	//void GSetDAMAGE(int DamageUp)
	//{
	//	CharacterATT += DamageUp;
	//}

	void JumpAction();
	void RollsAction();

	void MoveRight(float Val);
	void MoveForward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	/*class AGlobalCharacter* GetGlobalCharacter()
	{
		return GlobalCharacter;
	}

	void PlayerHPCheck();
	
	int PlayerHP = 0;*/

protected:
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void BeginPlay() override;



private:
	//virtual void Tick(float Delta) override;
	//virtual void Tick(float _Delta) override;
	//void Tick(float _Delta) override;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	//void Tick(float _Delta) override;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<AIAniState, class UAnimMontage*> MapAnimation;

	UFUNCTION()
		void UnAttackAction();

	UFUNCTION()
		void MontageEnd(UAnimMontage* Anim, bool _Inter);

	UFUNCTION()
		void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

		//class AGlobalCharacter* GlobalCharacter = nullptr;

};
