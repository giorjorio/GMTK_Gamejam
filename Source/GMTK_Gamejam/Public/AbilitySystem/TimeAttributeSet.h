// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"


#include "TimeAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	/* Source */
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	/* Source end */

	/* Target */
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	/* Target end */
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


UCLASS()
class GMTK_GAMEJAM_API UTimeAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UTimeAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentTime, Category = "Primary Attributes")
	FGameplayAttributeData CurrentTime;
	ATTRIBUTE_ACCESSORS(UTimeAttributeSet, CurrentTime);
	
	UFUNCTION()
	void OnRep_CurrentTime(const FGameplayAttributeData& OldCurrentTime) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IncomingTimeDamage, Category = "Primary Attributes")
	FGameplayAttributeData IncomingTimeDamage;
	ATTRIBUTE_ACCESSORS(UTimeAttributeSet, IncomingTimeDamage);
	
	UFUNCTION()
	void OnRep_IncomingTimeDamage(const FGameplayAttributeData& OldIncomingTimeDamage) const;
	
private: 
	
	void SetEffectProperties(const FGameplayEffectModCallbackData&Data, FEffectProperties& Props);
	void HandleIncomingTimeDamage(const FEffectProperties& Props);

	
	
};
