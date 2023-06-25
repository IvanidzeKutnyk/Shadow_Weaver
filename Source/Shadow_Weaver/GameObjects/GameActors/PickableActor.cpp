#include "PickableActor.h"
#include "Components/BoxComponent.h"
#include "../../GameManagers/GameItemsManager.h"
#include "../../GameManagers/GameCharacterManager.h"
#include "../../GameObjects/Player/PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickableActor::APickableActor()
	: m_boxSize(50, 50, 50)
	, m_pickAble(true)
{
	PrimaryActorTick.bCanEverTick = true;

	//Capsule Component
	BoxComponent = CreateDefaultSubobject< UBoxComponent > (TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(m_boxSize);
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableActor::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APickableActor::OnOverlapEnd);


	MeshComponent = CreateDefaultSubobject < UStaticMeshComponent > (TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void APickableActor::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (this->m_pickAble)
		{
			APlayerCharacter* Player = static_cast<APlayerCharacter*> (OtherActor);
			if (Player)
			{
				//Player->Tags.Add("T_Interactable");
				GameCharacterManager::GetInstance()->SetInteractable(true);
				//Player->interact = true;
				GameCharacterManager::GetInstance()->SetPickableActor(this);
				//Player->SetPickableActor(this);
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		}
	}
	
}

void APickableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}

