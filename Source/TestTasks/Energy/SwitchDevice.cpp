// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchDevice.h"

#include "EnergyProvider.h"

// Sets default values
ASwitchDevice::ASwitchDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void ASwitchDevice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitchDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitchDevice::ConnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode)
{
	UObject* Obj = EnergyNode.GetObject();  
	if (Obj->GetClass()->ImplementsInterface(UEnergyProvider::StaticClass()))  
	{  
		TScriptInterface<IEnergyProvider> Source;  
		Source.SetObject(Obj);  
		Source.SetInterface(Cast<IEnergyProvider>(Obj));  
		PowerSource = Source;  
	}else
	{
		ConnectedDevices.Add(EnergyNode);
	}
		UpdateConnection_Implementation(bIsActive);
}

void ASwitchDevice::UpdateConnection_Implementation(bool DeviceState)
{
	bIsActive = DeviceState;
	for (auto& Device : ConnectedDevices)
	{
		Execute_UpdateConnection(Device.GetObject(), bIsActive);
	}
}

void ASwitchDevice::DisconnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode)
{
	UObject* Obj = EnergyNode.GetObject();  
	if (Obj->GetClass()->ImplementsInterface(UEnergyProvider::StaticClass()))  
	{  
		PowerSource = nullptr;
		bIsActive = false;
	}else
	{
		ConnectedDevices.Remove(EnergyNode);
	}
	UpdateConnection_Implementation(bIsActive);
}




