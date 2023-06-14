// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABird::ABird() :
	BaseTurnRate(70.f),
	BaseLookUpRate(70.f)
{
	PrimaryActorTick.bCanEverTick = true;

	// Create capsule component and set it as the root component
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);

	// Create skeletal mesh and attach it to the root component
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());

	// Create a spring arm and attach it to the camera;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	// Create a camera and attach it to the root component
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
}

void ABird::BeginPlay()
{
	Super::BeginPlay();
}

void ABird::MoveForward(float Value)
{
	if (GetController() && Value != 0.f) AddMovementInput(GetActorForwardVector(), Value);
}

void ABird::MoveRight(float Value)
{
	if (GetController() && Value != 0.f) AddMovementInput(GetActorRightVector(), Value);
}

void ABird::TurnAtRate(float Rate)
{
	float DeltaTime{ GetWorld()->GetDeltaSeconds() };
	AddControllerYawInput(Rate * BaseTurnRate * DeltaTime);
}

void ABird::LookUpAtRate(float Rate)
{
	float DeltaTime{ GetWorld()->GetDeltaSeconds() };
	AddControllerPitchInput(Rate * BaseLookUpRate * DeltaTime);
}
	

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABird::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::TurnAtRate);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABird::LookUpAtRate);
}

