#include "PickableActor.h"
#include "Components/BoxComponent.h"
#include "../../GameManagers/GameItemsManager.h"
#include "../../GameManagers/GameCharacterManager.h"
#include "../../GameObjects/Player/PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickableActor::APickableActor()
	: m_inputboxSize(100, 100, 100)
	, m_visualboxSize(50,50,50)
	, m_pickAble(true)
	, m_actorId(11)
{
	PrimaryActorTick.bCanEverTick = true;

	// Input Box Component
	InputBoxComponent = CreateDefaultSubobject< UBoxComponent > (TEXT("InputBoxComponent"));
	InputBoxComponent->SetBoxExtent(m_inputboxSize);
	InputBoxComponent->SetCollisionProfileName("InputTrigger");
	InputBoxComponent->SetupAttachment(RootComponent);
	InputBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableActor::OnOverlapBegin);
	InputBoxComponent->OnComponentEndOverlap.AddDynamic(this, &APickableActor::OnOverlapEnd);
	
	APickableActor::OnEndCursorOver;
	APickableActor::OnBeginCursorOver;
	// Visual Box Component
	VisualBoxComponent = CreateDefaultSubobject< UBoxComponent >(TEXT("VisualBoxComponent"));
	VisualBoxComponent->SetBoxExtent(m_visualboxSize);
	VisualBoxComponent->SetCollisionProfileName("VisualTrigger");
	VisualBoxComponent->SetupAttachment(InputBoxComponent);

	//Mesh Component
	MeshComponent = CreateDefaultSubobject < UStaticMeshComponent > (TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(VisualBoxComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void APickableActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Item111")); // Check Error
}

void APickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickableActor::SetActorId(int _actorid)
{
	this->m_actorId = _actorid;
}

int APickableActor::GetActorId()
{
	return this->m_actorId;
}

void APickableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (this->m_pickAble)
		{
			APlayerCharacter* Player = static_cast<APlayerCharacter*> (OtherActor);
			if (Player)
			{
				Player->SetInteractable(true);
				GameCharacterManager::GetInstance()->SetPickableActor(this);
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
			

			UE_LOG(LogTemp, Warning, TEXT("Name: %i ."), this->GetUniqueID());
		}
	}
	
}

void APickableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		APlayerCharacter* Player = static_cast<APlayerCharacter*> (OtherActor);
		if (Player)
		{
			Player->SetInteractable(false);
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}


