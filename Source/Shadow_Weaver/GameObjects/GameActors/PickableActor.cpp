#include "PickableActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../GameManagers/GameItemsManager.h"
#include "../../GameObjects/Player/PlayerCharacter.h"
#include "../../GameObjects/GameItems/GameItem.h"


// Sets default values
APickableActor::APickableActor() 
	: AActor()
{
	this->M_DEBUG = false; // Use to Debug (FLAG)
	this->m_type_item = nullptr;
	this->Initialize();
}

APickableActor::APickableActor(const GameItem*& _type_item)
	: AActor()
{
	this->M_DEBUG = false; // Use to Debug (FLAG)
	this->m_type_item = _type_item;
	this->Initialize();
}

void APickableActor::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor::Initialize()
{
	this->m_inputboxSize = { 100,100,100 };
	this->m_visualboxSize = { 50,50,50 };
	this->m_pickAble = true;

	PrimaryActorTick.bCanEverTick = true;

	// Input Box Component
	InputBoxComponent = CreateDefaultSubobject< UBoxComponent >(TEXT("InputBoxComponent"));
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
	MeshComponent = CreateDefaultSubobject < UStaticMeshComponent >(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(VisualBoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void APickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
				Player->SetInteractableInZone(true);
				Player->SetPickableActor(this);

			}
			
			if (M_DEBUG) //Use to Debug
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
				UE_LOG(LogTemp, Warning, TEXT("Name: %i ."), this->GetUniqueID());
			}
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
			Player->SetInteractableInZone(false);
		}
		
		if (M_DEBUG) // Use to Debug
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
		}
	}
}


