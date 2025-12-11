// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarPanel.generated.h"
class ADirectionalLight;
UCLASS()
class TESTTASKS_API ASolarPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASolarPanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	ADirectionalLight* LightSource;
	
	float Efficiency;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
