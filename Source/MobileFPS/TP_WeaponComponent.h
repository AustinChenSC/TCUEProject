// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AMobileFPSCharacter;
/* 武器发射时的委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireOneBullet);
/* 扔掉武器时的委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropThisWeapon);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEFPS_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** 武器发射 delegate */
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

	/** 扔出武器时默认速度 */
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

	/** 丢弃武器 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DropWeapon();

	/** 尝试获取玩家 */
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
