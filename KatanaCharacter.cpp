// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Item.h"
#include "Weapon.h"

// Sets default values
AKatanaCharacter::AKatanaCharacter() :
	BaseTurnRate(70.f),
	BaseLookUpRate(70.f)
	// CharacterState(ECharacterState::ECS_Unequipped)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a spring arm and attach it to the camera;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a camera and attach it to the root component
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
}

// Called when the game starts or when spawned
void AKatanaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKatanaCharacter::MoveForward(float Value)
{
	if (GetController() && Value != 0.f)
	{
		const FRotator ControlRotation = GetControlRotation(), YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void AKatanaCharacter::MoveRight(float Value)
{
	if (GetController() && Value != 0.f)
	{
		const FRotator ControlRotation = GetControlRotation(), YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void AKatanaCharacter::TurnAtRate(float Rate)
{
	float DeltaTime{ GetWorld()->GetDeltaSeconds() };
	AddControllerYawInput(Rate * BaseTurnRate * DeltaTime);
}

void AKatanaCharacter::LookUpAtRate(float Rate)
{
	float DeltaTime{ GetWorld()->GetDeltaSeconds() };
	AddControllerPitchInput(Rate * BaseLookUpRate * DeltaTime);
}

void AKatanaCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->EquipWeapon(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_Equipped;
	}
}

// Called every frame
void AKatanaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AKatanaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AKatanaCharacter::EKeyPressed);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AKatanaCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AKatanaCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AKatanaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AKatanaCharacter::LookUpAtRate);
}

