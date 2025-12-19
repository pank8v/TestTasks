// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnergyProvider.h"
#include "GameFramework/Actor.h"
#include "EnergyNode.h"
#include "SwitchDevice.generated.h"

UCLASS(Blueprintable)
class TESTTASKS_API ASwitchDevice : public AActor, public IEnergyNode
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitchDevice();


protected:
	UPROPERTY(EditAnywhere, meta = (AllowedClasses="EnergyProvider"))
	TScriptInterface<IEnergyProvider> PowerSource;
	
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="EnergyNode"))
	TArray<TScriptInterface<IEnergyNode>> ConnectedDevices;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
public:	
	virtual void ConnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode) override;
	virtual void UpdateConnection_Implementation(bool DeviceState) override;
	virtual void DisconnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode) override;
};
