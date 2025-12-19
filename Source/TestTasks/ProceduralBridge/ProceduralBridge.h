// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralBridge.generated.h"

UCLASS()
class TESTTASKS_API AProceduralBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralBridge();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> RootComp;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StartMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> EndMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> MiddleMesh;
	
	UPROPERTY(EditAnywhere)
	float SegmentLength = 100.0f;
	
	UPROPERTY(EditAnywhere)
	float BridgeLength = 300.0f;
	UPROPERTY()
	TArray<UStaticMeshComponent*> MiddleMeshes;
};
