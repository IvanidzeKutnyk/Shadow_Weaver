#include "AnimalAI.h"

AAnimalAI::AAnimalAI()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAnimalAI::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimalAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
