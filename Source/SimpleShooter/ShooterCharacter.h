// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
bool isHiveDead = false;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	void Shoot();

	UFUNCTION(BlueprintCallable)
	AGun  * GetGun();

	UFUNCTION(BlueprintCallable)
	void SetGun(AGun * NewGun);

	UFUNCTION(BlueprintCallable)
	void SetHealth();

	UFUNCTION(BlueprintCallable)
	void SetAmmo();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	float GetPercentAmmo() const;

	UPROPERTY(EditAnywhere)
	AGun * MyGun;

	UPROPERTY(EditAnywhere)
	bool isHive = false;

	UPROPERTY(EditAnywhere)
	bool isPlayer = false;

	UFUNCTION(BlueprintPure)
	bool HasHiveDeath() const;

	UFUNCTION(BlueprintPure)
	bool ExitEnding(bool bWin);

	UFUNCTION(BlueprintCallable)
	void CallPawnKilled(APawn * Killed);

	UPROPERTY()
	bool isHittedButNotDead = 0;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float Axisvalue);
	
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun * Gun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 10;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
