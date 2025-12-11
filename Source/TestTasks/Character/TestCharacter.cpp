// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "TestTasks/Energy/EnergyNode.h"
#include "TestTasks/Energy/ConnectableCable.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "TestTasks/Interactable.h"
#include "TestTAsks/Energy/ConnectionCable.h"
#include "TestTasks/InspectionSystem/InspectionComponent.h"
#include "Camera/CameraComponent.h"
#include "TestTasks/InspectionSystem/ItemInspectionComponent.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(RootComponent);
	
	InspectionComponent = CreateDefaultSubobject<UInspectionComponent>("InspectionComponent");
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::Interact);
		
		if (InspectionComponent)
		{
			InspectionComponent->SetupPlayerInputComponent(PlayerInputComponent);
		}
	}

}

void ATestCharacter::Move(const FInputActionValue& Value)
{
	FVector2d MovementInput = Value.Get<FVector2d>();
	AddMovementInput(GetActorForwardVector(), MovementInput.Y);
	AddMovementInput(GetActorRightVector(), MovementInput.X);
}

void ATestCharacter::Look(const FInputActionValue& Value)
{
	FVector2d LookInput = Value.Get<FVector2d>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(-LookInput.Y);
}

void ATestCharacter::Interact()
{
	FVector Start = CameraComponent->GetComponentLocation();
	FRotator Rotation = CameraComponent->GetComponentRotation();
	FVector End = Start + Rotation.Vector() * 500;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
		
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == nullptr)
		{
			return;
		}
		
		if (UItemInspectionComponent* InspectedItem = HitActor -> FindComponentByClass<UItemInspectionComponent>())
		{
			if (InspectedItem)
			{
				InspectionComponent->StartInspection(HitActor);
				return;
			}
		}
		
		if (HitActor->GetClass()->ImplementsInterface(UConnectableCable::StaticClass()))
		{
			if (Cable)
			{
				return;
			}
			Cable.SetObject(HitActor);
			Cable.SetInterface(Cast<IConnectableCable>(HitActor));
			IConnectableCable::Execute_Disconnect(Cable.GetObject());
			HitActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("ItemSocket"));
		}
		
		if (HitActor->GetClass()->ImplementsInterface(UEnergyNode::StaticClass()))
		{
			if (Cable)
			{
				TScriptInterface<IEnergyNode> EnergyNode;
				EnergyNode.SetObject(HitActor);
				EnergyNode.SetInterface(Cast<IEnergyNode>(HitActor));
				if (Cable && IConnectableCable::Execute_TryConnectNode(Cable.GetObject(),EnergyNode, HitActor))
				{
					Cable = nullptr;	
					return;
				}
			}
		}
		
		if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_Interact(HitActor);
		}
	}
	
}

