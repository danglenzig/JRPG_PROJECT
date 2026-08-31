// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BattleStateMachine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateEntered, FName, EnteredState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateExited, FName, ExitedState);

namespace BattleStateNames
{
	static const FName Start(TEXT("START"));
	static const FName Setup(TEXT("SETUP"));
	static const FName RoundStart(TEXT("ROUND_START"));
	static const FName CommandInput(TEXT("COMMAND_INPUT"));
	static const FName ActionWindup(TEXT("ACTION_WINDUP"));
	static const FName Resolution(TEXT("RESOLUTION"));
	static const FName Aftermath(TEXT("AFTERMATH"));
	static const FName BattleEnd(TEXT("BATTLE_END"));
}

USTRUCT(BlueprintType)
struct FTransitionsStruct
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transitions")
	FName FromStateName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Transitions")
	TArray<FName> ToStateNames;
	
	FTransitionsStruct() = default;
	FTransitionsStruct(const FName FromStateName, const TArray<FName>& ToStateNames): FromStateName(FromStateName), ToStateNames(ToStateNames) {}
};


UCLASS(Blueprintable, BlueprintType)
class JRPG_PROJECT_API UBattleStateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleStateMachine")
	FName CurrentStateName;
	
	// RequestStateTransition:
	// - if there is a transition in the Transitions array whose FromStateName == CurrentState name, AND
	//   the ToStateName is in that transition's ToStateNames array, then:
	//   - Pop off FOnStateExited with the current state
	//   - Change the current state to the requested state
	//   - Pop off FOnStateEntered with the new state
	//   - return true
	// - Otherwise, log a warning and return false.
	// Implemented in .cpp file
	UFUNCTION(BlueprintCallable, Category = "BattleStateMachine")
	bool RequestStateTransition(const FName ToStateName);
	
	UPROPERTY(BlueprintAssignable)
	FOnStateEntered OnStateEntered;
	UPROPERTY(BlueprintAssignable)
	FOnStateExited OnStateExited;
	
	//default (and only) constructor
	UBattleStateMachine()
	{
		BattleStates.Add(BattleStateNames::Start);
		BattleStates.Add(BattleStateNames::Setup);
		BattleStates.Add(BattleStateNames::RoundStart);
		BattleStates.Add(BattleStateNames::CommandInput);
		BattleStates.Add(BattleStateNames::ActionWindup);
		BattleStates.Add(BattleStateNames::Resolution);
		BattleStates.Add(BattleStateNames::Aftermath);
		BattleStates.Add(BattleStateNames::BattleEnd);
		CurrentStateName = BattleStateNames::Start;
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::Start,
				{BattleStateNames::Setup}
				)
			);
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::Setup,
				{BattleStateNames::RoundStart}
				)
			);
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::RoundStart,
				{BattleStateNames::CommandInput}
				)
			);
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::CommandInput,
				{BattleStateNames::ActionWindup}
				)
			);
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::ActionWindup,
				{BattleStateNames::Resolution}
				)
			);
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::Resolution,
				{BattleStateNames::Aftermath}
				)
			);
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::Aftermath,
				{BattleStateNames::Start, BattleStateNames::BattleEnd}
				)
			);
		
		Transitions.Add(
			FTransitionsStruct(
				BattleStateNames::BattleEnd,
				{BattleStateNames::Start}
				)
			);
	}
	
	
private:
	
	TArray<FName> BattleStates;
	TArray<FTransitionsStruct> Transitions;
	
};
