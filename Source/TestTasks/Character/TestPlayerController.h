// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "TestPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
UCLASS()
class TESTTASKS_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATestPlayerController();
	
protected: 
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void HandleInspectionStateChange(bool bISInspecting);

private:

	
public:
	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere)
	UInputMappingContext* InspectMappingContext;

	void EnableInspectionMode();
	void DisableInspectionMode();

};
