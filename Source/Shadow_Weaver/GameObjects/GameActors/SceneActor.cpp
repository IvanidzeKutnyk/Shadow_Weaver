#include "SceneActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../GameManagers/GameItemsManager.h"
#include "../../GameObjects/Player/PlayerCharacter.h"
#include "../../GameObjects/GameItems/GameItem.h"


// Sets default values
ASceneActor::ASceneActor() 
	: AActor()
{
	this->m_interact = false;
	this->m_type = Types::DESTOY;
	this->m_type_item = nullptr;
	this->Initialize();
}

ASceneActor::ASceneActor(const GameItem*& _type_item,Types _type)
	: AActor()
{
	this->m_interact = false;
	this->m_type = _type;
	this->m_type_item = _type_item;
	this->Initialize();
}

void ASceneActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASceneActor::Initialize()
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
	InputBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASceneActor::OnOverlapBegin);
	InputBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASceneActor::OnOverlapEnd);

	ASceneActor::OnEndCursorOver;
	ASceneActor::OnBeginCursorOver;

	// Visual Box Component
	VisualBoxComponent = CreateDefaultSubobject< UBoxComponent >(TEXT("VisualBoxComponent"));
	VisualBoxComponent->SetBoxExtent(m_visualboxSize);
	VisualBoxComponent->SetCollisionProfileName("VisualTrigger");
	VisualBoxComponent->SetupAttachment(InputBoxComponent);

	//Mesh Component
	MeshComponent = CreateDefaultSubobject < UStaticMeshComponent >(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(VisualBoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ASceneActor::Action()
{
	if (this->m_interact)
	{
		this->m_interact = false;

		switch (this->m_type)
		{
		case Types::DESTOY:
		{
			this->Destroy();
		}
		default:
			break;
		}
	}
}

void ASceneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Action();
}

void ASceneActor::SetAction()
{
	this->m_interact = true;
}

void ASceneActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
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
		}
	}
	
}

void ASceneActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		APlayerCharacter* Player = static_cast<APlayerCharacter*> (OtherActor);
		if (Player)
		{
			Player->SetInteractableInZone(false);
		}
	}
}


