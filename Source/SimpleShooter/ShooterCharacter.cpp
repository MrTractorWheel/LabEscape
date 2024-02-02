// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "KillEmAllGameMode.h"
#include "Engine/World.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay(){
	Super::BeginPlay();
	Health = MaxHealth;
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	isHiveDead = false;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

bool AShooterCharacter::HasHiveDeath() const{
    return isHiveDead;
}

bool AShooterCharacter::ExitEnding(bool bWin){
	(Cast<AKillEmAllGameMode>(GetWorld()->GetAuthGameMode()))->EndGame(bWin);
	return bWin;
}

void AShooterCharacter::CallPawnKilled(APawn *Killed){
	(Cast<AKillEmAllGameMode>(GetWorld()->GetAuthGameMode()))->PawnKilled(Killed);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue){
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue){
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue){
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot(){
	Gun->PullTrigger();
}

AGun * AShooterCharacter::GetGun(){
	MyGun = &(*Gun);
	return MyGun;
}

void AShooterCharacter::SetGun(AGun *NewGun){
	MyGun = &(*Gun);
	MyGun = NewGun;
}

void AShooterCharacter::SetHealth(){
	if(MaxHealth <= 300){
		MaxHealth += 10;
	}
	if(Health <= MaxHealth-10){
		Health += 10;
	}
	else Health = MaxHealth;
}

void AShooterCharacter::SetAmmo(){
	if(Gun->Ammo <= 90) Gun->Ammo += 10;
	else Gun->Ammo = 100;
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser){
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), Health);
	if(IsDead()){
		isHittedButNotDead = false;
		ASimpleShooterGameModeBase * GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(this->isHive == false && isHiveDead == false && this->isPlayer == false){
			FVector TeleportLocation = this->GetActorLocation();
			AActor * UserActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
			FVector ExPlayerLocation = UserActor->GetActorLocation();
			UserActor->SetActorLocation(TeleportLocation);
			this->SetActorLocation(ExPlayerLocation);
		}
		if(GameMode != nullptr) GameMode->PawnKilled(this);
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else{
		this->isHittedButNotDead = true;
	}
	return DamageToApply;
}

bool AShooterCharacter::IsDead() const{
	return (Health <= 0);
}

float AShooterCharacter::GetHealthPercent() const{
    return Health/MaxHealth;
}

float AShooterCharacter::GetPercentAmmo() const{
    return (Gun->Ammo)/200;
}
