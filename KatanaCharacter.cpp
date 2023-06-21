// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Item.h"
#include "Weapon.h"
#include "Animation/AnimMontage.h"

// Sets default values
AKatanaCharacter::AKatanaCharacter() :
	BaseTurnRate(70.f),
	BaseLookUpRate(70.f),
	CharacterState(ECharacterState::ECS_Unequipped),
	ActionState(EActionState::EAS_Unoccupied),
	CarryingWeapon(false)
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
	if (ActionState != EActionState::EAS_Unoccupied) return;

	if (GetController() && Value != 0.f)
	{
		const FRotator ControlRotation = GetControlRotation(), YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void AKatanaCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;

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
	if (OverlappingWeapon && !CarryingWeapon)
	{
		OverlappingWeapon->EquipWeapon(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_Equipped;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
		CarryingWeapon = true;
	}
	else
	{
		if (ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped && CarryingWeapon)
		{
			PlayEquipMontage(FName("Unequip"));
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_Equipping;
		}
		else if (ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_Unequipped && CarryingWeapon)
		{
			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::ECS_Equipped;
			ActionState = EActionState::EAS_Equipping;
		}
	}
}

void AKatanaCharacter::Attack()
{
	if (CharacterState == ECharacterState::ECS_Unequipped) return;

	if (ActionState == EActionState::EAS_Unoccupied)
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AKatanaCharacter::FinishAttacking()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AKatanaCharacter::PlayAttackMontage()
{
	auto AnimInstance = GetMesh()->GetAnimInstance();
	const int32 Selection = FMath::RandRange(0, 1);
	FName SectionName = FName();
	switch (Selection)
	{
	case 0:
		SectionName = FName("Attack1");
		break;
	case 1:
		SectionName = FName("Attack2");
		break;
	}

	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void AKatanaCharacter::PlayEquipMontage(FName SectionName)
{
	auto AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

void AKatanaCharacter::DisarmWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttackMeshToSocket(GetMesh(), FName("SpineSocket"));
		CharacterState = ECharacterState::ECS_Unequipped;
	}
}

void AKatanaCharacter::ArmWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttackMeshToSocket(GetMesh(), FName("RightHandSocket"));
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
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AKatanaCharacter::Attack);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AKatanaCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AKatanaCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AKatanaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AKatanaCharacter::LookUpAtRate);
}

