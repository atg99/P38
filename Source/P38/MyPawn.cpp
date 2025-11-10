// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "MyRocket.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//에디터 드래그 앤 드롭, 설정 다 코드로 변경 가능
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(46.f, 62.f, 10.f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	//실제로 거의 안함 (에디터로딩할때 오래걸림)
	//static = 한번만 함
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/SM/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Left(TEXT("/Script/Engine.StaticMesh'/Game/SM/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Left.Succeeded())
	{
		Left->SetStaticMesh(SM_Left.Object);
		Right->SetStaticMesh(SM_Left.Object);
	}

	ArrowCompoent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowCompoent->SetupAttachment(Body);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));


}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FloatingPawnMovement->AddInputVector(GetActorForwardVector()*100*DeltaTime);

	Left->AddLocalRotation(FRotator(0,0,1000.f*DeltaTime));
	Right->AddLocalRotation(FRotator(0, 0, 1000.f * DeltaTime));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(FAction, ETriggerEvent::Started, this, &AMyPawn::Fire);
	}
}

void AMyPawn::Fire()
{
	FActorSpawnParameters SpawnParam;
	
	GetWorld()->SpawnActor<AMyRocket>(RocketClass, FTransform(GetActorRotation() + FRotator(-90.f, 0, 0), GetActorLocation(), FVector(1.f)), SpawnParam);
}

