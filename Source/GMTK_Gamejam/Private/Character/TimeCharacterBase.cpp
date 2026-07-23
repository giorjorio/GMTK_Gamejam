// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TimeCharacterBase.h"


#include "AbilitySystem/TimeAbilitySystemComponent.h"
#include "AbilitySystem/TimeAttributeSet.h"
#include "TimeGameplayTags.h"
#include "GameplayEffect.h"
#include "Components/CapsuleComponent.h"


ATimeCharacterBase::ATimeCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	TimeAbilitySystemComponent =
	CreateDefaultSubobject<UTimeAbilitySystemComponent>(
		TEXT("AbilitySystemComponent"));

	TimeAttributeSet =
		CreateDefaultSubobject<UTimeAttributeSet>(
			TEXT("AttributeSet"));
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ATimeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	InitializeTime();
	StartTimeDecay();
	
}

void ATimeCharacterBase::InitializeTime()
{
	check(TimeAbilitySystemComponent);
	check(DefaultTimeEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = TimeAbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = TimeAbilitySystemComponent->MakeOutgoingSpec(DefaultTimeEffectClass, 1.f, ContextHandle);
	
	if (!SpecHandle.IsValid())
	{
		return;
	}
	
	SpecHandle.Data->SetSetByCallerMagnitude(
		TimeGameplayTags::Data_InitialTime,
		InitialTime);
	
	TimeAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
	
}

void ATimeCharacterBase::Die()
{
	if (bIsDead)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Died"));

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


void ATimeCharacterBase::AddCharacterAbilities()
{
	TimeAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}

void ATimeCharacterBase::InitAbilityActorInfo()
{
	TimeAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ATimeCharacterBase::StartTimeDecay()
{
	check(TimeDecayEffectClass);

	FGameplayEffectContextHandle ContextHandle = TimeAbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = TimeAbilitySystemComponent->MakeOutgoingSpec(TimeDecayEffectClass, 1.f, ContextHandle);
	
	if (!SpecHandle.IsValid())
	{
		return;
	}
	
	TimeAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

