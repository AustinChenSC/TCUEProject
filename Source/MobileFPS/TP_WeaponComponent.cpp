// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "MobileFPSCharacter.h"
#include "MobileFPSProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	// 武器扔出默认速度
	VelocityWhenDrop = FVector(300.0f, 0, 0);
}


void UTP_WeaponComponent::Fire()
{

	//debug
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Try to fire"));
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	//debug
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Fired"));

	// 检测玩家是否有子弹
	if (Character->GetAmmoCount()) {
		// Try and fire a projectile 
		if (ProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
				const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// Spawn the projectile at the muzzle
				World->SpawnActor<AMobileFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}

			//将子弹数量减一
			Character->FireOneAmmo();
		}

		// Try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
		}

		// Try and play a firing animation if specified
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}

	}
	
	
	
}

void UTP_WeaponComponent::AttachWeapon(AMobileFPSCharacter* TargetCharacter)
{
	
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}
	
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			if (!Subsystem->HasMappingContext(FireMappingContext)) {
				Subsystem->AddMappingContext(FireMappingContext, 1);
			}
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}
}

void UTP_WeaponComponent::DropWeapon()
{
	//必须在持有武器才能丢弃
	if (Character == nullptr)
	{
		return;
	}
	//设置Chara持有武器状态
	Character->SetHasRifle(false);

	//取消Fire输入事件
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Character->GetController()->InputComponent))
	{
		// Fire
		EnhancedInputComponent->ClearActionBindings(); //BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("取消Fire输入事件"));
	}

	FVector throwVelocity;
	//删除Fire输入映射
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("删除Fire输入映射"));
			Subsystem->RemoveMappingContext(FireMappingContext);
		}

		//保存扔出去的方向与速度
		//玩家速度
		throwVelocity = PlayerController->GetPawn()->GetVelocity();
		//相机朝向方向 默认速度
		FVector facingDirection = PlayerController->PlayerCameraManager->GetCameraRotation().RotateVector(VelocityWhenDrop);
		//叠加速度
		throwVelocity += facingDirection;
	}

	//将Weapon从父项移除
	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
	Character = nullptr;

	//将Weapon向前扔出去
	this->SetPhysicsLinearVelocity(throwVelocity);

}

AMobileFPSCharacter* UTP_WeaponComponent::GetPlayer()
{
	return Character;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}