// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PickUpComponent.h"

void UTP_PickUpComponent::SetOnBeginOverlap()
{
	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	UTP_PickUpComponent::SetOnBeginOverlap();
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Hud stuff
	
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("-----------Overlapping-------"));
	// Checking if it is a First Person Character overlapping
	AMobileFPSCharacter* Character = Cast<AMobileFPSCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
