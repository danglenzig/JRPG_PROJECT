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
	
	
	if (!StartingStateTag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("### SimpleStateMachine: SM has no valid initial state."));
	}
	StateHistoryNames.Add(CurrentStateName); // Adds NONE as the first state history
	CurrentStateName = StartingStateTag.GetTagName();
	FGameplayTag CurrentStateTag = UGameplayTagsManager::Get().RequestGameplayTag(CurrentStateName);
	
	if (!CurrentStateTag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("### SimpleStateMachine: SM has no valid initial state."));
		return;
	}
	OnStateEntered.Broadcast(CurrentStateTag);
	UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: SM initialized in state: %s"), *CurrentStateName.ToString());
	
}


// Called every frame
void USimpleStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USimpleStateMachineComponent::RequestTransition(FGameplayTag ToStateTag)
{
	
	if (!ToStateTag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("### SimpleStateMachine: Invalid state transition requested."));
		return false;
	}
	
	const FSimpleTransitionsStruct* MatchingTransition = Transitions.FindByPredicate(
		[this](const FSimpleTransitionsStruct& Transition)
		{
			return Transition.FromStateTag == UGameplayTagsManager::Get().RequestGameplayTag(CurrentStateName);
		}
	);
	
	if (!MatchingTransition)
	{
		UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: Current state not found in Transitions list: %s"), *CurrentStateName.ToString());
		return false;
	}
	
	// iterate through all the to-states allowed for the current state
	TArray<FGameplayTag> TagsArray = MatchingTransition->ToStateTags.GetGameplayTagArray();
	//for (const auto& AllowedToStateTag : MatchingTransition->ToStateTags)
	for (const auto& AllowedToStateTag : TagsArray)
	{
		// when / if we find one matching the requested new state...
		if (AllowedToStateTag == ToStateTag)
		{
			StateHistoryNames.Add(CurrentStateName);
			GroomStateHistory();
			OnStateExited.Broadcast(UGameplayTagsManager::Get().RequestGameplayTag(CurrentStateName));
			CurrentStateName = ToStateTag.GetTagName();
			OnStateEntered.Broadcast(ToStateTag);
			UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: New current state: %s"), *CurrentStateName.ToString());
			return true;
		}
	}
	
	// this is a Log message, and not Warning or Error because there could be 
	// perfectly legit reasons that the state cannot transition, and is expected to
	// happen during normal gameplay from time to time
	FName ToStateName = ToStateTag.GetTagName();
	UE_LOG(LogTemp, Log, TEXT("### SimpleStateMachine: Current state has no allowed transition to state %s"), *ToStateName.ToString());
	return false;
}

void USimpleStateMachineComponent::GroomStateHistory()
{
	// if the history size is greated that the max
	if (StateHistoryNames.Num() > StateHistorySize)
	{
		// remove the oldest one
		StateHistoryNames.RemoveAt(0);
	}
}
