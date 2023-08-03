#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneActor.generated.h"

class GameItem;

UENUM(BlueprintType)
enum Types
{
	DESTOY UMETA(DisplayName = "Destroy"),
	ACTION UMETA(DisplayName = "Action")
};


UCLASS()
class SHADOW_WEAVER_API ASceneActor : public AActor
{
	GENERATED_BODY()

public:	
	ASceneActor();
	ASceneActor(const GameItem*& _type_item, Types _type);

protected:
	virtual void BeginPlay() override;

private:
	void Initialize();
	void Action();

public:	
	virtual void Tick(float DeltaTime) override;
	void SetAction();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	FVector m_inputboxSize;
	FVector m_visualboxSize;
	const GameItem* m_type_item;
	//Types m_type;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* InputBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* VisualBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Variables")
		TEnumAsByte<Types> m_type;
	


public:
	bool m_pickAble;
	bool m_interact;
};
