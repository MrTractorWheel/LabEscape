// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AKillEmAllGameMode::PawnKilled(APawn * PawnKilled){
    Super::PawnKilled(PawnKilled);
    APlayerController * PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr && isHiveDead == true){
        EndGame(false);
    }
    else if(PlayerController != nullptr && isHiveDead == false){
      EndGame(false);
    }
    else if((Cast<AShooterCharacter>(PawnKilled))->isHive == true){
        isHiveDead = true;
    }
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner){
    UE_LOG(LogTemp, Warning, TEXT("In the EndGame"));
    for(AController* Controller : TActorRange<AController>(GetWorld())){
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
