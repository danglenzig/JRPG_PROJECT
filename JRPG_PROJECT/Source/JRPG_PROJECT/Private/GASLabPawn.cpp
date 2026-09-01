// GASLabPawn.cpp

#include "GASLabPawn.h"

#include "AbilitySystemComponent.h"

AGASLabPawn::AGASLabPawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* AGASLabPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASLabPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

