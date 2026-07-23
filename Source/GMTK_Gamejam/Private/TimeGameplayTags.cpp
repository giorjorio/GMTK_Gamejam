#include "TimeGameplayTags.h"

namespace TimeGameplayTags
{
	
	/* Ability Tags */
	UE_DEFINE_GAMEPLAY_TAG(Ability_Shot, "Ability.Shot");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Shot_Default, "Ability.Shot.Default");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Shot_Charged, "Ability.Shot.Charged");
	
	/* State Tags */
	UE_DEFINE_GAMEPLAY_TAG(State_Charging, "State.Charging");

	/* Data Tags */
	UE_DEFINE_GAMEPLAY_TAG(Data_TimeDamage, "Data.TimeDamage");
	UE_DEFINE_GAMEPLAY_TAG(Data_TimeGain, "Data.TimeGain");
	UE_DEFINE_GAMEPLAY_TAG(Data_InitialTime, "Data.InitialTime");
	
	/* Attributes Tags */
	UE_DEFINE_GAMEPLAY_TAG(Attributes_CurrentTime, "Attributes.CurrentTime");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_IncomingTimeDamage, "Attributes.IncomingTimeDamage");
	
	/* Input Tags */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LMB, "InputTag.LMB");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RMB, "InputTag.RMB");
	
}