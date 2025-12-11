// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "InspectionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInspectionStateChanged, bool, IsInspecting);
class UInputAction;
class UCameraComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASKS_API UInspectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInspectionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ============================================================================
	// Public Methods
	// ============================================================================
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	void StartInspection(AActor* Actor);
	
	// ============================================================================
	// Delegates
	// ============================================================================
	UPROPERTY(BlueprintAssignable)
	FOnInspectionStateChanged OnInspectionStateChanged;

	
protected:
	virtual void BeginPlay() override;
	// ============================================================================
	// Input Actions 
	// ============================================================================
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> RotateAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ZoomAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> StopInspectionAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> HoldAction;
	
	
	 // ============================================================================
	// Inspection Pivot & Camera
	// ============================================================================
	UPROPERTY(EditAnywhere)
	USceneComponent* InspectionPivot;
	
	
	UCameraComponent* CameraComponent;
	

	// ============================================================================
	// Configurable Settings
	// ============================================================================
	UPROPERTY(EditAnywhere)
	float RotationOffset = 10.0f;
	
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10.0f;
	
	UPROPERTY(EditAnywhere)
	float ZoomOffset = 1.0f;
	
	UPROPERTY(EditAnywhere)
	float ZoomSpeed = 10.0f;
	
	UPROPERTY(EditAnywhere)
	float MinZoom = 150.0f;
	UPROPERTY(EditAnywhere)
	float MaxZoom = 80.0f;

	
	
private:
	AActor* CurrentInspectedActor;
	
	bool bIsHolding;
	FVector OriginalPosition;
	FRotator OriginalRotation;
	FVector OriginalScale;
	
	// ============================================================================
	// Input Callbacks
	// ============================================================================
	void Rotate(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void HoldInspection(const FInputActionValue& Value);
	void StopHoldingInspection(const FInputActionValue& Value);
	void StopInspection();

};
