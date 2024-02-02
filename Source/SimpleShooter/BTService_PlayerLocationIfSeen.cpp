// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameWork/Pawn.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen(){
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn == nullptr) return;
    if(OwnerComp.GetAIOwner() == nullptr) return;
    APawn * DamageTaker = (Cast<AController>(OwnerComp.GetAIOwner()))->GetPawn();
    AShooterCharacter * HitEnemy = Cast<AShooterCharacter>(DamageTaker);
    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn) || HitEnemy->isHittedButNotDead){
        HitEnemy->isHittedButNotDead = false;
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else{
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}