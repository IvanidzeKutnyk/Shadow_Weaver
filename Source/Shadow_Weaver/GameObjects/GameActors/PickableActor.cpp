#include "PickableActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickableActor::APickableActor()
	: m_InHalfHeight(50) //CapsuleComponent.SIZE
	, m_InRadius(50)		//CapsuleComponent.SIZE
{
	PrimaryActorTick.bCanEverTick = true;

	//Capsule Component
	CapsuleComponent = CreateDefaultSubobject< UCapsuleComponent > (TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(this->m_InRadius, this->m_InHalfHeight);
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableActor::OnOverlapBegin);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &APickableActor::OnOverlapEnd);


	MeshComponent = CreateDefaultSubobject < UStaticMeshComponent > (TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(CapsuleComponent, FAttachmentTransformRules::KeepRelativeTransform);
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void APickableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}

