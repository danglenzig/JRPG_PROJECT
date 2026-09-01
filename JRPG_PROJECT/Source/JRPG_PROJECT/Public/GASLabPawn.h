// GASLabPawn.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "AbilitySystemInterface.h"
#include "GASLabPawn.generated.h"

UCLASS()
class JRPG_PROJECT_API AGASLabPawn : public ADefaultPawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AGASLabPawn();
	
	// override the one function in IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// override DefaultPawn's PossesedBy function
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
};
