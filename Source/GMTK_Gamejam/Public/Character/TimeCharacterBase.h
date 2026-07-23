// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TimeCharacterBase.generated.h"


class UGameplayAbility;
class UTimeAbilitySystemComponent;
class UTimeAttributeSet;
class UGameplayEffect;
class ATimeCharacterBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeCharacterDied, ATimeCharacterBase*, DeadCharacter);


UCLASS(Abstract)
class GMTK_GAMEJAM_API ATimeCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATimeCharacterBase();
	
	virtual void Die();
	
	bool IsDead() const;
	
	UPROPERTY(BlueprintAssignable, Category = "Death")
	FOnTimeCharacterDied OnDied;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	void InitializeTime();
	void AddCharacterAbilities();
	virtual void InitAbilityActorInfo();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Time")
	float InitialTime = 60.f;
	
	bool bIsDead = false;

	UPROPERTY()
	TObjectPtr<UTimeAbilitySystemComponent> TimeAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTimeAttributeSet> TimeAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Time")
	TSubclassOf<UGameplayEffect> DefaultTimeEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Time")
	TSubclassOf<UGameplayEffect> TimeDecayEffectClass;
	
	void StartTimeDecay();
	

	
private:
	
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
