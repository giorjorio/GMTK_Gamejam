// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TimePlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystem/TimeAbilitySystemComponent.h"
#include "Input/TimeInputComponent.h"

ATimePlayerController::ATimePlayerController()
{
}

void ATimePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATimePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TimeInputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(TimeInputContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	

}

void ATimePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UTimeInputComponent* TimeInputComponent = CastChecked<UTimeInputComponent>(InputComponent);

	TimeInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATimePlayerController::Move);
	TimeInputComponent->BindAbilityActions(TimeInputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased);

}

void ATimePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if  (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ATimePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void ATimePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
}

UTimeAbilitySystemComponent* ATimePlayerController::GetTimeASC()
{
	if (TimeAbilitySystemComponent == nullptr)
	{
		TimeAbilitySystemComponent = Cast<UTimeAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return TimeAbilitySystemComponent;
}
