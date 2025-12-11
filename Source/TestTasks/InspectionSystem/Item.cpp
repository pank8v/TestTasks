// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "ItemInspectionComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	ItemInspectionComponent = CreateDefaultSubobject<UItemInspectionComponent>("ItemInspectionComponent");

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
	UE_LOG(LogTemp, Display, TEXT("Interactuin"));
}

