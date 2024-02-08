#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ATakeAndApplyCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UICPP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthComponent", meta = (AllowPrivateAccess))
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthComponent", meta = (AllowPrivateAccess))
	float MaxHealth = 100.f;

	ATakeAndApplyCharacter* MainCharacter;

public:
	FORCEINLINE float GetCurrentHealth() const {return CurrentHealth;}
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}

	FORCEINLINE void SetCurrentHealth(float const Health) {CurrentHealth += Health;}
	FORCEINLINE void SetMaxHealth(float const Health) {SetCurrentHealth(Health/2); MaxHealth += Health;}

	// OnTakeAnyDamage Function
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// To check if character die
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ChDied = false;
};
