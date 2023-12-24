// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AMobileFPSCharacter;
/* ��������ʱ��ί�� */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireOneBullet);
/* �ӵ�����ʱ��ί�� */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropThisWeapon);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEFPS_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** �������� delegate */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnFireOneBullet OnFireOneBullet;

	/** Drop Weapon delegate */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnDropThisWeapon OnDropThisWeapon;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AMobileFPSProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** �ӳ�����ʱĬ���ٶ� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector VelocityWhenDrop;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	///** Fire Input Action */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	//class UInputAction* FireAction;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AMobileFPSCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	/** �������� */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DropWeapon();

	/** ���Ի�ȡ��� */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AMobileFPSCharacter* GetPlayer();

protected:
	///** Ends gameplay for this component. */
	//UFUNCTION()
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	AMobileFPSCharacter* Character;
};
