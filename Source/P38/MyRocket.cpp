// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket"));
	RootComponent = Rocket;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/SM/SM_Rocket.SM_Rocket'"));
	if (SM_Rocket.Succeeded())
	{
		Rocket->SetStaticMesh(SM_Rocket.Object);
	}

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectComp"));
	ProjectileComp->InitialSpeed = 1000;
	ProjectileComp->Velocity = FVector(0, 0, 1.f);
	//SetLifeSpan(3);

}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, FTimerDelegate::CreateLambda([this]() { Destroy(); }), 3, false);

	Rocket->OnComponentBeginOverlap.AddDynamic(this, &AMyRocket::OnRocketBeginOverlap);
	
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyRocket::OnRocketBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Target"))
	{	
		TSubclassOf<UDamageType> DamageType;
		
		UGameplayStatics::ApplyDamage(OtherActor, 10, Cast<APawn>(GetOwner())->GetController(), this, DamageType);
		//OtherActor->TakeDamage();
	}
}

