// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "ShooterCharacter.h"

void AShooterPlayerController::BeginPlay(){
    Super::BeginPlay();
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr){
        HUD->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner){
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    HUD->RemoveFromViewport();
    if(bIsWinner){
        UUserWidget * WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr){
            WinScreen->AddToViewport();
            RestartDelay += 7;
        }
    }
    else if(isHiveDead){
        UUserWidget * LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr){
            LoseScreen->AddToViewport();
            RestartDelay += 7;
        }
    }
    else{
        UUserWidget * RebirthScreen = CreateWidget(this, RebirthScreenClass);
        if(RebirthScreen != nullptr){
            RebirthScreen->AddToViewport();
        }
    }
    isHiveDead = false;
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
