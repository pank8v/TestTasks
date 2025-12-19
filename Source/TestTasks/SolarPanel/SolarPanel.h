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
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<ADirectionalLight> LightSource;
	
	UPROPERTY(VisibleAnywhere)
	float Efficiency;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
