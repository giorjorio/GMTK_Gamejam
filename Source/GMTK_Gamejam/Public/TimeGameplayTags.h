#pragma once

#include "NativeGameplayTags.h"

namespace  TimeGameplayTags
{
	

	/* Ability Tags */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Shot);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Shot_Default);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Shot_Charged);

	/* State Tags */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Charging);

	/* Data Tags */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_TimeDamage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_TimeGain);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_InitialTime);
	
	/* Attributes Tags */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_CurrentTime);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_IncomingTimeDamage);
	
	/* Input Tags */
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RMB);

	
};
