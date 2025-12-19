// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyProvider.h"
#include "EnergyNode.h"
#include "PowerSource.generated.h"

UCLASS(Blueprintable)
class TESTTASKS_API APowerSource : public AActor, public IEnergyProvider, public IEnergyNode
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerSource();
	
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="EnergyNode"))
	TArray<TScriptInterface<IEnergyNode>>ConnectedDevices;
	
	
protected:
	
	UPROPERTY(EditAnywhere)
	bool bIsActive;


public:	
	virtual void ConnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode) override;
	virtual void UpdateConnection_Implementation(bool DeviceState) override;
	virtual void DisconnectNode_Implementation(const TScriptInterface<IEnergyNode>& EnergyNode) override;
	
};
