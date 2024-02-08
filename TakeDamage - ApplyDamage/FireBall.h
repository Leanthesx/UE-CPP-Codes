#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBall.generated.h"

class UProjectileMovementComponent;
class UDamageType;

UCLASS()

class UICPP_API AFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	AFireBall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallMesh;

	// DamageType Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileComp;

	// HitSound
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* HitSound;

	// HitParticle
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* HitParticle;

	// BeginOverlap Function
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 bodyindex, bool bFromSweep, const FHitResult& SweepResult);
};
