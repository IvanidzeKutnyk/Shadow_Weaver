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
#include "../../GameObjects/GameActors/PickableActor.h"
#include "../../GameManagers/GameItemsManager.h"
#include "../../GameManagers/GameCharacterManager.h"



APlayerCharacter::APlayerCharacter()
	:m_interactable_zone(false)
	, m_pickable_item(false)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; 
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	GameItemsManager::GetInstance()->ParseItems();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LineTraceToItems();

}

void APlayerCharacter::PressedInteractButton()
{
	if(this->m_interactable_zone && this->m_pickable_item)
	{
		GameCharacterManager::GetInstance()->GetPickableActor()->Destroy();
	}
}

void APlayerCharacter::UnPressedInteractButton()
{
}

void APlayerCharacter::SetInteractable(bool _interact)
{
	this->m_interactable_zone = _interact;
}

bool APlayerCharacter::GetInteractable()
{
	return  this->m_interactable_zone;
}


void APlayerCharacter::LineTraceToItems()
{
	if (this->m_interactable_zone)
	{
		FHitResult OutHit;
		FVector _ZVectorCorrection = { 0,0,50 };
		FVector Start = APlayerCharacter::GetActorLocation() + _ZVectorCorrection;
		FVector ForwardVector = FollowCamera->GetForwardVector();
		FVector END = (Start + (ForwardVector * 2000.f));

		FCollisionQueryParams CollisionParams;
		DrawDebugLine(GetWorld(), Start, END, FColor::Green, false, 1, 0, 1);

		bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, END, ECC_Visibility, CollisionParams);
		if (isHit)
		{
			if (OutHit.bBlockingHit)
			{
				if (GameCharacterManager::GetInstance()->GetPickableActor()->GetUniqueID() != OutHit.GetActor()->GetUniqueID())
				{
					this->m_pickable_item = false;
				}
				else
				{
					this->m_pickable_item = true;
				}
				if (GEngine && GameCharacterManager::GetInstance()->bDebugFlag)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %i, Name: %s"),
						OutHit.GetActor()->GetUniqueID(), *OutHit.GetActor()->GetName()));
					//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
					//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));
				}
			}
		}
	}
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
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
