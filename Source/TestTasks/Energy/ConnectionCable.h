// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "ConnectableCable.h"
#include "EnergyNode.h"
#include "./TestTasks/Interactable.h"
#include "ConnectionCable.generated.h"

UCLASS()
class TESTTASKS_API AConnectionCable : public AActor, public IConnectableCable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConnectionCable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UCableComponent* CableComponent;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StartCableMesh;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EndCableMesh;
	
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="EnergyNode"))
	TScriptInterface<IEnergyNode> StartEnergyNode;
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="EnergyNode"))
	TScriptInterface<IEnergyNode> EndEnergyNode;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;
	
	bool bStartConnected = false;
	bool bEndConnected = false;
	

public:	
	
	TScriptInterface<IEnergyNode> GetStartEnergyNode();
	TScriptInterface<IEnergyNode> GetEndEnergyNode();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool TryConnectNode_Implementation(TScriptInterface<IEnergyNode>& Node, AActor* HitActor) override;
	virtual void Disconnect_Implementation() override;
	
private:
	void UpdateConnection();
	void AttachStartTo(AActor* Actor);
	void AttachEndTo(AActor* Actor);
	
};
