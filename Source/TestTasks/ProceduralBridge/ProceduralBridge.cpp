// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralBridge.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AProceduralBridge::AProceduralBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootComp;
	StartMesh = CreateDefaultSubobject<UStaticMeshComponent>("StartMesh");
	EndMesh = CreateDefaultSubobject<UStaticMeshComponent>("EndMesh");
	
}

// Called when the game starts or when spawned
void AProceduralBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProceduralBridge::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	EndMesh->SetRelativeLocation(FVector(BridgeLength,0.0f ,0.0f));
	
	FVector End = EndMesh->GetRelativeLocation();
	FVector Start = StartMesh->GetRelativeLocation();
	
	FVector Direction = (End - Start).GetSafeNormal();
	float Distance = (End-Start).Size();
	int32 NumSegments = FMath::FloorToInt(Distance / SegmentLength);
	float RealSegmentLength = Distance / NumSegments;
	for (auto Comp:MiddleMeshes)
	{
		Comp->DestroyComponent();
	}
	MiddleMeshes.Empty();
	
	for (int i = 1; i <= NumSegments; i++)
	{
		UStaticMeshComponent* NewMesh = NewObject<UStaticMeshComponent>(this);
		NewMesh->RegisterComponent();
		NewMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		NewMesh->SetStaticMesh(MiddleMesh);
		FVector Pos = Start + Direction * (RealSegmentLength * i);
		NewMesh->SetRelativeLocation(Pos);
		MiddleMeshes.Add(NewMesh);
	}
	
	
	
}

// Called every frame
void AProceduralBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

