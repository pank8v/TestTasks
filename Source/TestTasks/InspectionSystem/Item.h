// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./TestTasks/Interactable.h"
#include "Item.generated.h"

class UItemInspectionComponent;
UCLASS()
class TESTTASKS_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;
	
	UPROPERTY(EditAnywhere)
	UItemInspectionComponent* ItemInspectionComponent;
	
};
