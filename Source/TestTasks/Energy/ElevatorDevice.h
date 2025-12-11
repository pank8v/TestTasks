// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElectricalDeviceComponent.h"
#include "./TestTasks/Interactable.h"
#include "EnergyNode.h"
#include "ElevatorDevice.generated.h"

UCLASS()
class TESTTASKS_API AElevatorDevice : public AActor, public IEnergyNode, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorDevice();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsActive;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TScriptInterface<IEnergyNode> SwitchDevice;
	
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UElectricalDeviceComponent* ElectricalDeviceComponent;
	
	UPROPERTY(EditAnywhere)
	FVector EndLocation;
	
	UPROPERTY(EditAnywhere)
	float Speed = 200.0f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateConnection_Implementation(bool DeviceState) override;
	virtual void DisconnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode) override;
	virtual void ConnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode) override;
	virtual void Interact_Implementation() override;
	
private:
	FVector StartLocation;
	bool bMovingUp;
	bool bIsMoving;
};
