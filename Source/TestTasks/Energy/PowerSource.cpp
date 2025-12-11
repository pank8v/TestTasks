// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSource.h"
#include "CableComponent.h"

class UCableComponent;
// Sets default values
APowerSource::APowerSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
}

// Called when the game starts or when spawned
void APowerSource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APowerSource::ConnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode)
{
	UObject* Obj = EnergyNode.GetObject();  
	if (!Obj->GetClass()->ImplementsInterface(UEnergyProvider::StaticClass()))
	ConnectedDevices.Add(EnergyNode);
	UpdateConnection_Implementation(bIsActive);
}

void APowerSource::UpdateConnection_Implementation(bool DeviceState)
{
	for (auto& Device : ConnectedDevices)
	{
		Execute_UpdateConnection(Device.GetObject(), bIsActive);
	}
}

void APowerSource::DisconnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode)
{
	ConnectedDevices.Remove(EnergyNode);
	UpdateConnection_Implementation(bIsActive);
}







