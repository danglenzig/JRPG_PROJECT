#include "../Public/SimpleStateMachineComponent.h"

// Constructor
USimpleStateMachineComponent::USimpleStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USimpleStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	if (StartingState == NAME_None)
	{
		UE_LOG(LogTemp, Error, TEXT("### SimpleStateMachine: Initial state not set"));
		return;
	}
	StateHistory.Add(CurrentState); // Adds Name_None as the first state history
	CurrentState = StartingState;
	OnStateEntered.Broadcast(CurrentState);
	UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: SM initialized in state: %s"), *CurrentState.ToString());
}


// Called every frame
void USimpleStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USimpleStateMachineComponent::RequestTransition(FName ToState)
{
	// find the first (which should be the ONLY) transition whose
	//   FromStateName is the current state
	const FSimpleTransitionsStruct* MatchingTransition = Transitions.FindByPredicate(
		[this](const FSimpleTransitionsStruct& Transition)
		{
			return Transition.FromStateName == CurrentState;
		}
	);
	
	if (!MatchingTransition)
	{
		UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: Current state not found in Transitions list: %s"), *CurrentState.ToString());
		return false;
	}
	
	// iterate through all the to-states allowed for the current state
	for (const auto& AllowedToState : MatchingTransition->ToStateNames)
	{
		// when / if we find one matching the requested new state...
		if (AllowedToState == ToState)
		{
			StateHistory.Add(CurrentState);
			GroomStateHistory();
			OnStateExited.Broadcast(CurrentState);
			CurrentState = ToState;
			OnStateEntered.Broadcast(CurrentState);
			UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: New current state: %s"), *CurrentState.ToString());
			return true;
		}
	}
	
	// this is a Log message, and not Warning or Error because there could be 
	// perfectly legit reasons that the state cannot transition, and is expected to
	// happen during normal gameplay from time to time
	UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: Current state has no allowed transition to state %s"), *ToState.ToString());
	return false;
}

void USimpleStateMachineComponent::GroomStateHistory()
{
	// if the history size is greated that the max
	if (StateHistory.Num() > StateHistorySize)
	{
		// remove the oldest one
		StateHistory.RemoveAt(0);
	}
}
