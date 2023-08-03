#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DrawDebugHelpers.h"
#include "Components/TimelineComponent.h"
#include "Math/UnrealMathVectorCommon.h"
#include "MotionWarpingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "../../GameStorage/PlayerStorage.h"
#include "../../GameObjects/GameActors/SceneActor.h"
#include "../../GameManagers/GameItemsManager.h"

APlayerCharacter::APlayerCharacter()
	: m_interactable_zone(false)
	, m_pickable_itemHit(false)
	, IsCrouching(false)
	, vault_start_position(0.0f, 0.0f, 0.0f)
	, vault_middle_position(0.0f, 0.0f, 0.0f)
	, vault_end_position(0.0f, 0.0f, 0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	UCharacterMovementComponent* this_movement_component = GetCharacterMovement();
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	this_movement_component->bOrientRotationToMovement = true;
	this_movement_component->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	this_movement_component->JumpZVelocity = 700.f;
	this_movement_component->AirControl = 0.35f;
	this_movement_component->MaxWalkSpeed = 500.f;
	this_movement_component->MinAnalogWalkSpeed = 20.f;
	this_movement_component->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	VaultMotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	CrouchCameraTimeline = new FTimeline;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	GameItemsManager::GetInstance()->ParseItems();

	if (OnCrouchCameraCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("CrouchCameraAnimationProgress"));

		CrouchCameraTimeline->AddInterpFloat(OnCrouchCameraCurve, TimelineProgress);
		CrouchCameraTimeline->SetLooping(false);
	}

	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &APlayerCharacter::APlayerCharacter::OnMontageEnded);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LineTraceToItems();

	CrouchCameraTimeline->TickTimeline(DeltaTime);
}

void APlayerCharacter::PressedInteractButton()
{
	if(this->m_interactable_zone && this->m_pickable_itemHit)
	{
		this->m_tmpPickableActor->SetAction();
	}
}

void APlayerCharacter::UnPressedInteractButton()
{
}

void APlayerCharacter::SetInteractableInZone(bool _interact)
{
	this->m_interactable_zone = _interact;
}

void APlayerCharacter::LineTraceToItems()
{
	if (this->m_interactable_zone)
	{
		FHitResult OutHit;
		FVector _ZVectorCorrection = { 0,0,50 };
		FVector Start = APlayerCharacter::GetActorLocation() + _ZVectorCorrection;
		FVector ForwardVector = FollowCamera->GetForwardVector();
		FVector END = (Start + (ForwardVector * 2000.0));

		FCollisionQueryParams CollisionParams;

		DrawDebugLine(GetWorld(), Start, END, FColor::Green, false, 1, 0, 1);

		bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, END, ECC_Visibility, CollisionParams);
		if (isHit)
		{
			if (OutHit.bBlockingHit)
			{
				if (this->m_tmpPickableActor->GetUniqueID() != OutHit.GetActor()->GetUniqueID())
				{
					this->m_pickable_itemHit = false;
				}
				else
				{
					this->m_pickable_itemHit = true;
				}
				if (GEngine) // Use for Debug
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %i, Name: %s"),
						OutHit.GetActor()->GetUniqueID(), *OutHit.GetActor()->GetName()));
				}
			}
		}
	}
	
}

void APlayerCharacter::SetPickableActor(ASceneActor* _item)
{
	this->m_tmpPickableActor = _item;
}

USpringArmComponent* APlayerCharacter::GetCameraBoom() const
{
	return CameraBoom;
}

UCameraComponent* APlayerCharacter::GetFollowCamera() const
{
	return FollowCamera;
}

#pragma region Inputs

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::Crouch);

		//Shift
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &APlayerCharacter::Shift);
	}
	//Picking Up
	PlayerInputComponent->BindAction("Button_E_Interactive", IE_Pressed, this, &APlayerCharacter::PressedInteractButton);
	PlayerInputComponent->BindAction("Button_E_Interactive", IE_Released, this, &APlayerCharacter::UnPressedInteractButton);
	
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Crouch(const FInputActionValue& Value)
{
	IsCrouching = !IsCrouching;
	
	if (IsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = 350.0f;
		CrouchCameraTimeline->PlayFromStart();
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
		CrouchCameraTimeline->Reverse();
	}
}

void APlayerCharacter::Shift(const FInputActionValue& Value)
{
	if (CheckIfCanVaultBy())
	{
		DoVault();
	}
}

#pragma endregion

void APlayerCharacter::CrouchCameraAnimationProgress(float Value)
{
	CameraBoom->TargetArmLength = FMath::Lerp(400.0f, 550, Value);
}

void APlayerCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrunted)
{
	if (Montage == VaultByAnimMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("anim ended"));
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		SetActorEnableCollision(true);
		vault_end_position = FVector(0.0f, 0.0f, 20000.0f);
	}
}

bool APlayerCharacter::CheckIfCanVaultBy()
{
	const FVector  actor_location = GetActorLocation();
	const FRotator actor_rotation = GetActorRotation();
	const FVector  actor_forward  = GetActorForwardVector();
	
	bool can_warp = false;

	for (int i = 0; i < 3; i++)
	{
		FVector start_vector( actor_location.X,
							  actor_location.Y, 
                              actor_location.Z + i * 30);
		FVector end_vector( actor_forward.X * 180.0f + start_vector.X,
							actor_forward.Y * 180.0f + start_vector.Y,
							actor_forward.Z * 180.0f + start_vector.Z);

		TArray<AActor*> actors_to_ignore;
		actors_to_ignore.Add(GetOwner());

		FHitResult hit_result;
		
		bool is_hit = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(),
			start_vector,
			end_vector,
			5.0f,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			actors_to_ignore,
			EDrawDebugTrace::ForDuration,
			hit_result,
			true,
			FLinearColor::Blue,
			FLinearColor::Red,
			10.0f);

		if (is_hit)
		{
			for (int j = 0; j < 6; j++)
			{
				FHitResult sphere_hit_result;

				start_vector.Set( hit_result.Location.X + actor_forward.X * 50 * j,
								  hit_result.Location.Y + actor_forward.Y * 50 * j,
								  hit_result.Location.Z + actor_forward.Z * 50 * j + 100.0f);
				end_vector.Set( start_vector.X,
								start_vector.Y,
								start_vector.Z - 100.0f);
				
				is_hit = UKismetSystemLibrary::SphereTraceSingle(
					GetWorld(),
					start_vector,
					end_vector,
					10.0f,
					UEngineTypes::ConvertToTraceType(ECC_Visibility),
					false,
					actors_to_ignore,
					EDrawDebugTrace::ForDuration,
					sphere_hit_result,
					true,
					FLinearColor::Blue,
					FLinearColor::Red,
					10.0f);

				if (is_hit)
				{
					if (j == 0)
					{
						vault_start_position = sphere_hit_result.Location;
						UKismetSystemLibrary::DrawDebugSphere(
							GetWorld(),
							vault_start_position,
							10.0f,
							12,
							FLinearColor::Red,
							10.0f,
							2.0f);
					}

					vault_middle_position = sphere_hit_result.Location;
					UKismetSystemLibrary::DrawDebugSphere(
						GetWorld(),
						vault_start_position,
						10.0f,
						12,
						FLinearColor::Red,
						10.0f,
						2.0f);
				}
				else
				{
					start_vector.Set( sphere_hit_result.TraceStart.X + actor_forward.X * 80.0f,
									  sphere_hit_result.TraceStart.Y + actor_forward.Y * 80.0f,
									  sphere_hit_result.TraceStart.Z + actor_forward.Z * 80.0f);
					end_vector.Set( start_vector.X,
									start_vector.Y,
									start_vector.Z - 1000.0f);

					is_hit = UKismetSystemLibrary::LineTraceSingle(
						GetWorld(),
						start_vector,
						end_vector,
						UEngineTypes::ConvertToTraceType(ECC_Visibility),
						false,
						actors_to_ignore,
						EDrawDebugTrace::ForDuration,
						sphere_hit_result,
						true,
						FLinearColor::Green,
						FLinearColor::Red,
						10.0f);

					if (is_hit)
					{
						vault_end_position = sphere_hit_result.Location;
						can_warp = true;
						break;
					}
				}
			}
			
			break;
		}
	}
	
	return can_warp;
}

void APlayerCharacter::DoVault()
{
	UCharacterMovementComponent* character_movement = GetCharacterMovement();

	character_movement->SetMovementMode(MOVE_Flying);
	SetActorEnableCollision(false);

	FMotionWarpingTarget target;
	target.Name = FName("VaultStart");
	target.Location = vault_start_position;
	target.Rotation = GetActorRotation();
	VaultMotionWarping->AddOrUpdateWarpTarget(target);

	target.Name = FName("VaultMiddle");
	target.Location = vault_middle_position;
	target.Rotation = GetActorRotation();
	VaultMotionWarping->AddOrUpdateWarpTarget(target);

	target.Name = FName("VaultLand");
	target.Location = vault_end_position;
	target.Rotation = GetActorRotation();
	VaultMotionWarping->AddOrUpdateWarpTarget(target);

	if (VaultByAnimMontage)
	{
		PlayAnimMontage(VaultByAnimMontage, 1, NAME_None);
	}
}
