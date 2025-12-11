// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectionCable.h"


// Sets default values
AConnectionCable::AConnectionCable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = RootComp;
    StartCableMesh = CreateDefaultSubobject<UStaticMeshComponent>("StartCableMesh");
	StartCableMesh->SetupAttachment(RootComponent);
	CableComponent = CreateDefaultSubobject<UCableComponent>("CableComponent");
	CableComponent->SetupAttachment(StartCableMesh);
	EndCableMesh = CreateDefaultSubobject<UStaticMeshComponent>("EndCableMesh");
	EndCableMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AConnectionCable::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AConnectionCable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AConnectionCable::TryConnectNode_Implementation(TScriptInterface<IEnergyNode>& Node, AActor* HitActor)
{
	if (EndEnergyNode == nullptr)
	{
		EndEnergyNode = Node;
		AttachEndTo(HitActor);

	}else if (StartEnergyNode == nullptr)
	{
		StartEnergyNode = Node;
		AttachStartTo(HitActor);
		UpdateConnection();
		return true;
	}
	return false;
}


void AConnectionCable::AttachStartTo(AActor* Actor)
{
	if (StartCableMesh == nullptr)
	{
		return;
	}
	AttachToComponent(Actor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("CableSocket"));
}

void AConnectionCable::AttachEndTo(AActor* Actor)
{
	if (EndCableMesh == nullptr)
	{
		return;
	}
	EndCableMesh->AttachToComponent(Actor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("CableSocket"));
}



void AConnectionCable::Disconnect_Implementation()
{
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	EndCableMesh->AttachToComponent(
	RootComponent,
	FAttachmentTransformRules::KeepRelativeTransform);
	if (StartEnergyNode)
	{
		EndEnergyNode->DisconnectNode_Implementation(StartEnergyNode);
	}
	if (EndEnergyNode)
	{
		StartEnergyNode->DisconnectNode_Implementation(EndEnergyNode);
	}
	EndEnergyNode = nullptr;
	StartEnergyNode = nullptr;
}


void AConnectionCable::UpdateConnection()
{
	if (StartEnergyNode && EndEnergyNode)
	{
		StartEnergyNode->ConnectNode_Implementation(EndEnergyNode);
		EndEnergyNode->ConnectNode_Implementation(StartEnergyNode);
	}else
	{
		StartEnergyNode->ConnectNode_Implementation(nullptr);
		EndEnergyNode->ConnectNode_Implementation(nullptr);
	}
	
	
}

TScriptInterface<IEnergyNode> AConnectionCable::GetStartEnergyNode()
{
	return StartEnergyNode;
}

TScriptInterface<IEnergyNode> AConnectionCable::GetEndEnergyNode()
{
	return EndEnergyNode;
}


