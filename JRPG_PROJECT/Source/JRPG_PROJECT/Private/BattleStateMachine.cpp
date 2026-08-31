// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/BattleStateMachine.h"

bool UBattleStateMachine::RequestStateTransition(const FName ToStateName)
{
	const FTransitionsStruct* MatchingTransition = Transitions.FindByPredicate(
		[this](const FTransitionsStruct& Transition)
		{
			return Transition.FromStateName == CurrentStateName;
		});
	
	if (!MatchingTransition)
	{
		UE_LOG(LogTemp, Log, TEXT("Current state not found in Transitions list: %s"), *CurrentStateName.ToString());
		return false;
	}
	
	for (const auto& AllowedToState : MatchingTransition->ToStateNames)
	{
		if (AllowedToState == ToStateName)
		{
			OnStateExited.Broadcast(CurrentStateName);
			CurrentStateName = ToStateName;
			OnStateEntered.Broadcast(CurrentStateName);
			UE_LOG(LogTemp, Log, TEXT("New current state: %s"), *CurrentStateName.ToString());
			return true;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Current state has no allowed transition to state %s"), *ToStateName.ToString());
	return false;
}
