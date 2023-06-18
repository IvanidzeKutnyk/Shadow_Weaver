#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalAI.generated.h"

UCLASS()
class SHADOW_WEAVER_API AAnimalAI : public ACharacter
{
	GENERATED_BODY()

public:

	AAnimalAI();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
