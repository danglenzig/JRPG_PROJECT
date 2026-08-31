// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleStateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSimpleOnStateEntered, FName, EnteredState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSimpleOnStateExited, FName, ExitedState);

USTRUCT(BlueprintType)
struct FSimpleTransitionsStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Transitions")
	FName FromStateName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Transitions")
	TArray<FName> ToStateNames;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JRPG_PROJECT_API USimpleStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()
	
	
	
	

public:	
	// Sets default values for this component's properties
	USimpleStateMachineComponent();
	
	// State enter & exit events
	UPROPERTY(BlueprintAssignable)
	FSimpleOnStateEntered OnStateEntered;
	UPROPERTY(BlueprintAssignable)
	FSimpleOnStateExited OnStateExited;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateMachineComponent")
	FName CurrentState = FName("NONE");
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateMachineComponent")
	TArray<FName> StateHistory;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	int32 StateHistorySize = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	FName StartingState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	TArray<FName> States;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | Transitions")
	TArray<FSimpleTransitionsStruct> Transitions;
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "StateMachineComponent")
	bool RequestTransition(FName ToState);
	
private:
	void GroomStateHistory();
		
};
