// Copyright Fireteam Interactive

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    SetRootComponent(Mesh);
    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
    Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (const IAbilitySystemInterface* AscInterface = Cast<IAbilitySystemInterface>(OtherActor))
    {
        if (AscInterface->GetAbilitySystemComponent())
        {
            const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(
                AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
            //TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
            UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
            MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
            MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.f);
            Destroy();
        }
    }
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
    Super::BeginPlay();

    Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
    Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}