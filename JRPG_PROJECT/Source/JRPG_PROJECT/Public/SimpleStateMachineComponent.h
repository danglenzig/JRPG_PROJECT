// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "GameplayTagContainer.h"
#include "SimpleStateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSimpleOnStateEntered, FGameplayTag, EnteredState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSimpleOnStateExited, FGameplayTag, ExitedState);

USTRUCT(BlueprintType)
struct FSimpleTransitionsStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Transitions")
	FGameplayTag FromStateTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Transitions")
	FGameplayTagContainer ToStateTags;
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
	FName CurrentStateName = FName("NONE");
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateMachineComponent")
	TArray<FName> StateHistoryNames;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	int32 StateHistorySize = 10;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	FGameplayTag StartingStateTag;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	FGameplayTagContainer StateTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | Transitions")
	TArray<FSimpleTransitionsStruct> Transitions;
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "StateMachineComponent")
	bool RequestTransition(FGameplayTag ToStateTag);
	
private:
	void GroomStateHistory();
		
};
