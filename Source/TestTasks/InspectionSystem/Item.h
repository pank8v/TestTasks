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
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;


public:	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UItemInspectionComponent> ItemInspectionComponent;
	
	virtual void Interact_Implementation() override;
	

	
};
