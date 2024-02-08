#include "FireBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AFireBall::AFireBall()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(RootComponent);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
}

void AFireBall::BeginPlay()
{
	Super::BeginPlay();

	//BeginOverlap Delegate
	BallMesh->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OnComponentBeginOverlap);
	
}

void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// BeginOverlap Function
void AFireBall::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 bodyindex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ApplyDamage
	UGameplayStatics::ApplyDamage(OtherActor, 25.f, GetInstigatorController(), this, DamageType);
	
	if(HitSound && HitParticle)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, OtherActor->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, OtherActor->GetActorLocation());
		Destroy();
	}
}

