// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "TimePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UTimeAbilitySystemComponent;
class UTimeInputConfig;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class GMTK_GAMEJAM_API ATimePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATimePlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	
	/*
	 * Movement
	 */
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> TimeInputContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	void Move(const FInputActionValue& InputActionValue);
	
	/*void ShiftPressed() { bShiftKeyDown = true;}
	void ShiftReleased() { bShiftKeyDown = false;}
	bool bShiftKeyDown = false;*/
	
	/*
	 * Abilities Inputs
	 */

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UTimeInputConfig> TimeInputConfig;
	
	UPROPERTY()
	TObjectPtr<UTimeAbilitySystemComponent> TimeAbilitySystemComponent;

	UTimeAbilitySystemComponent* GetTimeASC();
	
};
