#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class ASceneActor;
class PlayerStorage;

UCLASS(config = Game)
class SHADOW_WEAVER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

protected:

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Crouch(const FInputActionValue& Value);

	void Shift(const FInputActionValue& Value);

public:	
	
	virtual void Tick(float DeltaTime) override;

	void PressedInteractButton();

	void UnPressedInteractButton();

	void SetInteractableInZone(bool _interact);

	void LineTraceToItems();

	void SetPickableActor(ASceneActor* _item);


public:

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const;

	FORCEINLINE class UCameraComponent* GetFollowCamera() const;

private:

	UFUNCTION()
	void CrouchCameraAnimationProgress(float Value);

	UFUNCTION(BlueprintCallable)
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrunted);

	bool CheckIfCanVaultBy();
	
	void DoVault();

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ShiftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Variables, meta = (AllowPrivateAccess = "true"))
		bool IsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimationVariables, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* OnCrouchCameraCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Vault, meta = (AllowPrivateAccess = "true"))
		class UMotionWarpingComponent* VaultMotionWarping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Vault, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* VaultByAnimMontage;

	struct FTimeline* CrouchCameraTimeline;

	bool m_interactable_zone;
	bool m_pickable_itemHit;

	FVector vault_start_position;
	FVector vault_middle_position;
	FVector vault_end_position;

	ASceneActor* m_tmpPickableActor;
};
