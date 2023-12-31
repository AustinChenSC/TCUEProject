// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileFPSCharacter.h"
#include "MobileFPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AMobileFPSCharacter

AMobileFPSCharacter::AMobileFPSCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// ��ʼЯ����ҩΪ0
	AmmoCount = 0;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AMobileFPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AMobileFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMobileFPSCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMobileFPSCharacter::Look);

		//try to Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMobileFPSCharacter::TryToFire);
	}
}


void AMobileFPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMobileFPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMobileFPSCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AMobileFPSCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AMobileFPSCharacter::SetAmmoCount(int NewAmmoCount)
{
	AmmoCount = NewAmmoCount;
}

int32 AMobileFPSCharacter::GetAmmoCount()
{
	return AmmoCount;
}

void AMobileFPSCharacter::TryToFire()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Try to fire"));
	if (bHasRifle) {
		HoldingWeapon->Fire();
	}
}

void AMobileFPSCharacter::FireOneAmmo()
{
	if (AmmoCount) {
		AmmoCount--;
	}
}

void AMobileFPSCharacter::AttachWeapon(UTP_WeaponComponent* pickingUpWeapon)
{
	if (pickingUpWeapon) {
		HoldingWeapon = pickingUpWeapon;
	}
	else {
		return;
	}

	// switch bHasRifle so the animation blueprint can switch to another animation set
	AMobileFPSCharacter::SetHasRifle(true);
}

UTP_WeaponComponent* AMobileFPSCharacter::GetWeapon()
{
	return HoldingWeapon;
}

void AMobileFPSCharacter::DropWeapon()
{
	if (!bHasRifle) {
		return;
	}
	AMobileFPSCharacter::SetHasRifle(false);
	HoldingWeapon->DropWeapon();

}
