// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RoomEncounter.h"

// Sets default values
ARoomEncounter::ARoomEncounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomEncounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomEncounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

