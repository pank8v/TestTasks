// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "ProceduralBridge.generated.h"

UCLASS()
class TESTTASKS_API AProceduralBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralBridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	
	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StartMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EndMesh;
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* MiddleMesh;
	
	UPROPERTY(EditAnywhere)
	float SegmentLength = 100.0f;
	
	UPROPERTY(EditAnywhere)
	float BridgeLength = 300.0f;
	TArray<UStaticMeshComponent*> MiddleMeshes;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	
	
	
};
