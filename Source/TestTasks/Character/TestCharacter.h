// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "./TestTasks/Energy/ConnectableCable.h"
#include "TestCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInspectionComponent;
class AConnectionCable;
struct FInputActionValue;
class UInputAction;
UCLASS()
class TESTTASKS_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere)
	UInputMappingContext* InspectMappingContext;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InteractAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	
	TScriptInterface<IConnectableCable> Cable;
		
	UPROPERTY(EditAnywhere)
	UInspectionComponent* InspectionComponent;

};
