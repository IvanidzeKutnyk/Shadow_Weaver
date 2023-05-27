#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "MainPlayer.generated.h"

UCLASS()
class SHADOW_WEAVER_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()


public:

	
	AMainPlayer();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FTimeline WalkRunTimeline;

public:
	/*	Смерть Персонажа	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDead;

	/*	Селфіпалка	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	/*	Камера	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;

	void MoveForwardBackward(float _Axis); // Рух вперед назад
	void MoveLeftRight(float _Axis); // Рух вліво вправо
	void Jump();
	void StopJumping();
	void SprintStart();
	void SprintEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fMaxWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fMaxRunSpeed;
};
