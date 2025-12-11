// Fill out your copyright notice in the Description page of Project Settings.


#include "InspectionComponent.h"
#include "EnhancedInputComponent.h"
#include "./TestTasks/Character/TestPlayerController.h"
#include "./TestTasks/Character/TestCharacter.h"
#include "Camera/CameraComponent.h"

// ============================================================================
// Construction && Initialization
// ============================================================================

UInspectionComponent::UInspectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InspectionPivot = CreateDefaultSubobject<USceneComponent>("InspectionPivot");
	// ...
}

// Called when the game starts
void UInspectionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* Owner = GetOwner();
	if (Owner != nullptr)
	{
		CameraComponent = Owner->FindComponentByClass<UCameraComponent>();
		if (CameraComponent != nullptr)
		{
			InspectionPivot->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
	// ...
	
}

// Called every frame
void UInspectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// ============================================================================
// Input setup
// ============================================================================

void UInspectionComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ThisClass::Rotate);
		EIC->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::Zoom);
		EIC->BindAction(StopInspectionAction, ETriggerEvent::Started, this, &ThisClass::StopInspection);
		EIC->BindAction(HoldAction, ETriggerEvent::Started, this, &ThisClass::HoldInspection);
		EIC->BindAction(HoldAction, ETriggerEvent::Completed, this, &ThisClass::StopHoldingInspection);
	}
}

void UInspectionComponent::StartInspection(AActor* InspectedActor)
{
	OnInspectionStateChanged.Broadcast(true);
	OriginalPosition =  InspectedActor->GetActorLocation();
	OriginalRotation = InspectedActor->GetActorRotation();
	OriginalScale = InspectedActor->GetActorScale();
	UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(InspectedActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	StaticMesh->SetSimulatePhysics(false);
	
	CurrentInspectedActor = InspectedActor;
	CurrentInspectedActor->AttachToComponent(InspectionPivot, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	CurrentInspectedActor->SetActorRelativeLocation(FVector::ZeroVector);
	CurrentInspectedActor->SetActorRelativeRotation(FRotator::ZeroRotator);
}

void UInspectionComponent::StopInspection()
{
	OnInspectionStateChanged.Broadcast(false);
	
	CurrentInspectedActor->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(CurrentInspectedActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	StaticMesh->SetSimulatePhysics(true);
	CurrentInspectedActor->SetActorLocation(OriginalPosition);
	CurrentInspectedActor->SetActorRotation(OriginalRotation);
	CurrentInspectedActor->SetActorScale3D(OriginalScale);
	CurrentInspectedActor = nullptr;
	
}

void UInspectionComponent::HoldInspection(const FInputActionValue& Value)
{
	bIsHolding = true;
}

void UInspectionComponent::StopHoldingInspection(const FInputActionValue& Value)
{
	bIsHolding = false;
}


// ============================================================================
// Actions
// ============================================================================

void UInspectionComponent::Rotate(const FInputActionValue& Value)
{
	if(!bIsHolding) return;
    
	FVector2D RotationInput = Value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	
	if(!CameraComponent) return;
	
	FVector CameraUp = CameraComponent->GetUpVector();
	CurrentInspectedActor->AddActorWorldRotation(
		FQuat(CameraUp, FMath::DegreesToRadians(-RotationInput.X * RotationOffset * RotationSpeed * DeltaTime))
	);
	
	FVector CameraRight = CameraComponent->GetRightVector();
	CurrentInspectedActor->AddActorWorldRotation(
		FQuat(CameraRight, FMath::DegreesToRadians(RotationInput.Y * RotationOffset * RotationSpeed * DeltaTime))
	);
}

void UInspectionComponent::Zoom(const FInputActionValue& Value)
{
	float ZoomValue = Value.Get<float>();
	float Delta = -ZoomValue * ZoomOffset * ZoomSpeed * GetWorld()->GetDeltaSeconds();
	FVector Loc = InspectionPivot->GetRelativeLocation();
	float NewX = Loc.X + Delta;
	if (NewX < MinZoom || NewX > MaxZoom)
		return;
	InspectionPivot->AddLocalOffset(FVector(Delta,0,0));
}








