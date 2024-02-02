// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	UFUNCTION(BlueprintCallable)
	void SetDamage(float NewDamage);

	UFUNCTION(BlueprintCallable)
	float GetDamage() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxRange(float NewRange);

	UFUNCTION(BlueprintCallable)
	float GetMaxRange() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float Ammo = 200;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere)
	USceneComponent * Root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent * Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem * MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase * MuzzleSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	UParticleSystem * ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase * ImpactSound;

private:
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController * GetOwnerController() const;
};
