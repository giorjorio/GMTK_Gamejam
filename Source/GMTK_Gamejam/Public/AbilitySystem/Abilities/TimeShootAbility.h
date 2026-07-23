// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TimeGameplayAbility.h"
#include "TimeShootAbility.generated.h"

class ATimeProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS(Abstract)
class GMTK_GAMEJAM_API UTimeShootAbility : public UTimeGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	void SpawnProjectile(const FVector& TargetLocation, float Damage, bool bExtractTimeOnLethalHit);
	
	FVector GetTargetLocation() const;
	
	FVector GetMuzzleLocation() const;
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ATimeProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shot")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shot")
	TSubclassOf<UGameplayEffect> TimeGainEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shot")
	float BaseDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shot")
	FName MuzzleSocketName = TEXT("Muzzle");
	
};
