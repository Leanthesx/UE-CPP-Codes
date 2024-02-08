#include "HealthComponent.h"
#include "ATakeAndApply/ATakeAndApplyCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//Cast MainCharacter
	MainCharacter = Cast<ATakeAndApplyCharacter>(GetOwner());

	// CurrentHealth = MaxHealth when the game starts
	CurrentHealth = MaxHealth;

	//OnTakeAnyDamage Delegate
	MainCharacter->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// OnTakeAnyDamage Function
void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(!ChDied)
	{
		SetCurrentHealth(-Damage);
		CurrentHealth = FMath::Clamp(CurrentHealth,0.f,MaxHealth);

		UE_LOG(LogTemp,Warning,TEXT("--------------------------"));
		UE_LOG(LogTemp,Warning,TEXT("HealthComponent Delegate is working!!"));
		UE_LOG(LogTemp,Warning,TEXT("Current Health: %f"),CurrentHealth);
		UE_LOG(LogTemp,Warning,TEXT("%f Damage Received"),Damage);
		UE_LOG(LogTemp,Warning,TEXT("Damage Causer: %s"),*DamageCauser->GetName());
		UE_LOG(LogTemp,Warning,TEXT("--------------------------"));
		
		if(CurrentHealth <= 0)
		{
			ChDied = true;
			MainCharacter->DamageTakenD.Broadcast(DamageCauser, Damage);
		}
	}
}

