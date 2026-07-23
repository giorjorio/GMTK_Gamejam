// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TimeCharacterBase.h"

#include "AbilitySystem/TimeAbilitySystemComponent.h"
#include "AbilitySystem/TimeAttributeSet.h"

ATimeCharacterBase::ATimeCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	TimeAbilitySystemComponent =
	CreateDefaultSubobject<UTimeAbilitySystemComponent>(
		TEXT("AbilitySystemComponent"));

	TimeAttributeSet =
		CreateDefaultSubobject<UTimeAttributeSet>(
			TEXT("AttributeSet"));

}

void ATimeCharacterBase::Die()
{
	if (bIsDead)
	{
		return;
	}
	
	bIsDead = true;
	OnDied.Broadcast(this);
}

bool ATimeCharacterBase::IsDead() const
{
	return bIsDead;
}

UAbilitySystemComponent* ATimeCharacterBase::GetAbilitySystemComponent() const
{
	return TimeAbilitySystemComponent;
}

void ATimeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	AddCharacterAbilities();
	
}

void ATimeCharacterBase::AddCharacterAbilities()
{
	TimeAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}

void ATimeCharacterBase::InitAbilityActorInfo()
{
	TimeAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

