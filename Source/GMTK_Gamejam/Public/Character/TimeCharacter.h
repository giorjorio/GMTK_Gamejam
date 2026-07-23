// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TimeCharacterBase.h"
#include "TimeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class GMTK_GAMEJAM_API ATimeCharacter : public ATimeCharacterBase
{
	GENERATED_BODY()
	
public:
	ATimeCharacter();

	virtual void PossessedBy(AController* NewController) override;
	
	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
};
