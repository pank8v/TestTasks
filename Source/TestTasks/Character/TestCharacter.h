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
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> InspectMappingContext;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IConnectableCable> Cable;
		
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInspectionComponent> InspectionComponent;
	
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
	UFUNCTION()
	void Interact();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
