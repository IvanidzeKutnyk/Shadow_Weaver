#include "MainPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

AMainPlayer::AMainPlayer()
	: bDead(false) 
	, fMaxWalkSpeed(400)
	, fMaxRunSpeed(800)
{
	PrimaryActorTick.bCanEverTick = true;
		
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); // Set CapsuleComponent Size

	bUseControllerRotationPitch = false;	//
	bUseControllerRotationYaw = false;		// Set Camera Rotation Params
	bUseControllerRotationRoll = false;		//

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // Init CameraBoom
	CameraBoom->SetupAttachment(RootComponent); // Connect to Capsule
	CameraBoom->TargetArmLength = 400.0f;	// Set Arm Length
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // Init Camera
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Connect to Spting Arm
	FollowCamera->bUsePawnControlRotation = false;	// Set Camera

	GetCharacterMovement()->bOrientRotationToMovement = true; // Move Character by Camera
	GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f); // Set Speed Rotation
	GetCharacterMovement()->JumpZVelocity = 700.0f; // Set Power Jump
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = this->fMaxWalkSpeed;
	GetCharacterMovement()->SetWalkableFloorAngle(60);
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookLeftRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpDown", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayer::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainPlayer::StopJumping);

	PlayerInputComponent->BindAxis("MoveForwardBackward",this, &AMainPlayer::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AMainPlayer::MoveLeftRight);
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainPlayer::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainPlayer::SprintEnd);
}

void AMainPlayer::MoveForwardBackward(float _Axis)
{
	if ((Controller != NULL) && (_Axis != 0.0f) && (bDead != true))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, _Axis);
	}
}

void AMainPlayer::MoveLeftRight(float _Axis)
{
	if ((Controller != NULL) && (_Axis != 0.0f) && (bDead != true))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, _Axis);
	}
}

void AMainPlayer::Jump()
{
	if ((Controller != NULL) && (bDead != true))
	{
		ACharacter::Jump();
	}
}

void AMainPlayer::StopJumping()
{
	if ((Controller != NULL) && (bDead != true))
	{
		ACharacter::StopJumping();
	}
}

void AMainPlayer::SprintStart()
{

}

void AMainPlayer::SprintEnd()
{

}
