// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TP_WeaponComponent.h"
#include "InputActionValue.h"
#include "MobileFPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AMobileFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/* 射击输入动作*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	
public:
	AMobileFPSCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** 玩家携带弹药量 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	int AmmoCount;

	/** 玩家手持武器 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	UTP_WeaponComponent* HoldingWeapon;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** Setter to set AmmoCount */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetAmmoCount(int newAmmoCount);

	/** Getter for AmmoCount */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	int32 GetAmmoCount();

	/** 尝试射击 */
	UFUNCTION(BlueprintCallable)
	void TryToFire();

	UFUNCTION(BlueprintCallable)
	void FireOneAmmo();

	/** 附加武器 */
	UFUNCTION(BlueprintCallable)
	void AttachWeapon(UTP_WeaponComponent* pickingUpWeapon);

	/** 获得武器 */
	UFUNCTION(BlueprintCallable)
	UTP_WeaponComponent* GetWeapon();

	/** 去除武器 */
	UFUNCTION(BlueprintCallable)
	void DropWeapon();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


};

