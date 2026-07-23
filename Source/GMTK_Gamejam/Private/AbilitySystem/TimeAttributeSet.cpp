// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TimeAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Character/TimeCharacterBase.h"
#include "Net/UnrealNetwork.h"

UTimeAttributeSet::UTimeAttributeSet()
{
}

void UTimeAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTimeAttributeSet, CurrentTime, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTimeAttributeSet, IncomingTimeDamage, COND_None, REPNOTIFY_Always);
}

void UTimeAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetCurrentTimeAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
}

void UTimeAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetCurrentTimeAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}

}

void UTimeAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentTimeAttribute() && OldValue > 0.f && NewValue <= 0.f)
	{
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		
		ATimeCharacterBase* TargetCharacter = ASC ? Cast<ATimeCharacterBase>(ASC->GetAvatarActor()) : nullptr;
		
		if (TargetCharacter && !TargetCharacter->IsDead())
		{
			TargetCharacter->Die();
		}
	}
}

void UTimeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	ATimeCharacterBase* TargetCharacter = Cast<ATimeCharacterBase>(Props.TargetAvatarActor);

	if (!TargetCharacter || TargetCharacter->IsDead())
	{
		return;
	}
	
	// Incoming damage changes
	if (Data.EvaluatedData.Attribute == GetIncomingTimeDamageAttribute())
	{
		HandleIncomingTimeDamage(Props);
	}
	
}

void UTimeAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	// Source = causer of the effect, Target = target of the effect (owner of this AttributeSet)
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		/*Props.SourceController =  Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}*/
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
		/*Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);*/
	}
}

void UTimeAttributeSet::HandleIncomingTimeDamage(const FEffectProperties& Props)
{
	const float LocalDamage = GetIncomingTimeDamage();
	
	SetIncomingTimeDamage(0.f);
	
	if (LocalDamage > 0.f)
	{
		SetCurrentTime(GetCurrentTime() - LocalDamage);
	}
	
}

void UTimeAttributeSet::OnRep_CurrentTime(const FGameplayAttributeData& OldCurrentTime) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTimeAttributeSet, CurrentTime, OldCurrentTime);
}

void UTimeAttributeSet::OnRep_IncomingTimeDamage(const FGameplayAttributeData& OldIncomingTimeDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTimeAttributeSet, IncomingTimeDamage, OldIncomingTimeDamage);
}


