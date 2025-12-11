// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorDevice.h"

// Sets default values
AElevatorDevice::AElevatorDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElectricalDeviceComponent = CreateDefaultSubobject<UElectricalDeviceComponent>("ElectricalDeviceComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
}

// Called when the game starts or when spawned
void AElevatorDevice::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AElevatorDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsMoving) return;

	FVector CurrentLocation = GetActorLocation();
	FVector Target = bMovingUp ? EndLocation : StartLocation;
	
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, Target, DeltaTime, Speed);
	SetActorLocation(NewLocation);
	if (FVector::Dist(CurrentLocation, Target) < 1.0f)
	{
		bIsMoving = false; 
	}

}

void AElevatorDevice::UpdateConnection_Implementation(bool DeviceState)
{
	bIsActive = DeviceState;
}

void AElevatorDevice::DisconnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode)
{
	SwitchDevice = nullptr;
	bIsActive = false;
}

void AElevatorDevice::ConnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode)
{
	if (EnergyNode)
	{
		SwitchDevice = EnergyNode;
	}
}

void AElevatorDevice::Interact_Implementation()
{
	if (bIsActive)
	{
		bMovingUp = !bMovingUp;
		bIsMoving = true;
	}
}

