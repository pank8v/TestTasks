// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "ConnectableCable.h"
#include "EnergyNode.h"
#include "ConnectionCable.generated.h"

UCLASS()
class TESTTASKS_API AConnectionCable : public AActor, public IConnectableCable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConnectionCable();

protected:
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> RootComp;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCableComponent> CableComponent;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StartCableMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> EndCableMesh;
	
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="EnergyNode"))
	TScriptInterface<IEnergyNode> StartEnergyNode;
	
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="EnergyNode"))
	TScriptInterface<IEnergyNode> EndEnergyNode;

public:	
	
	TScriptInterface<IEnergyNode> GetStartEnergyNode();
	TScriptInterface<IEnergyNode> GetEndEnergyNode();
	
	virtual bool TryConnectNode_Implementation(TScriptInterface<IEnergyNode>& Node, AActor* HitActor) override;
	virtual void Disconnect_Implementation() override;
	
private:
	
	bool bStartConnected = false;
	bool bEndConnected = false;
	
	void UpdateConnection();
	void AttachStartTo(const AActor* Actor);
	void AttachEndTo(const AActor* Actor);
	
};
