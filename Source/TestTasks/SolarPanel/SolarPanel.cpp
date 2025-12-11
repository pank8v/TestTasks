// Fill out your copyright notice in the Description page of Project Settings.


#include "SolarPanel.h"

#include "Engine/DirectionalLight.h"

// Sets default values
ASolarPanel::ASolarPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
	
}

// Called when the game starts or when spawned
void ASolarPanel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASolarPanel::Tick(float DeltaTime)
{
	if (LightSource)
	{
		FVector PanelDirection = StaticMesh->GetUpVector();
		FVector SunDirection = -LightSource->GetActorForwardVector();

		Efficiency = FMath::Max(FVector::DotProduct(PanelDirection, SunDirection), 0.0f);
	
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Efficiency: %f"), Efficiency));
	}

}

