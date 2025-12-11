// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"
#include "./TestTasks/InspectionSystem/InspectionComponent.h"

ATestPlayerController::ATestPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (APawn* ControlledPawn = GetPawn())
	{
		if (UInspectionComponent* InspectionComponent = ControlledPawn->FindComponentByClass<UInspectionComponent>())
		{
			InspectionComponent->OnInspectionStateChanged.AddDynamic(this, &ATestPlayerController::HandleInspectionStateChange);
		}
	}
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	
}

void ATestPlayerController::HandleInspectionStateChange(bool bIsInspecting)
{
	if (bIsInspecting)
	{
		EnableInspectionMode();
	}else
	{
		DisableInspectionMode();
	}
}


void ATestPlayerController::EnableInspectionMode()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(DefaultMappingContext);
		Subsystem->AddMappingContext(InspectMappingContext, 0);
	}
}

void ATestPlayerController::DisableInspectionMode()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(InspectMappingContext);
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}


