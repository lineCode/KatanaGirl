// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "KatanaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class AWeapon;

UCLASS()
class KATANAGIRL_API AKatanaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKatanaCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to control forward and backward movement with the keyboard keys
	void MoveForward(float Value);

	// Called to control left and right movement with the keyboard keys
	void MoveRight(float Value);

	// Called to look left and right with mouse wheel X
	void TurnAtRate(float Value);

	// Called to look up and down with mouse wheel y
	void LookUpAtRate(float Value);

	// Called to allow the Character to pickup a Weapon
	void EKeyPressed();

	// Called to allow Character to attack Enemies
	void Attack();

	// Called from Montage to set ActionState to Unoccupied
	UFUNCTION(BlueprintCallable)
	void FinishAttacking();

	// Plays attack Montage when Action State is Unoccupied
	void PlayAttackMontage();

	void PlayEquipMontage(FName SectionName);

	UFUNCTION(BlueprintCallable)
	void DisarmWeapon();

	UFUNCTION(BlueprintCallable)
	void ArmWeapon();

private:
	float BaseTurnRate, BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool CarryingWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hair, meta = (AllowPrivateAccess = "true"))
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hair, meta = (AllowPrivateAccess = "true"))
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AItem* OverlappingItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* EquipMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

public:	
	// Getters for private variables
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	// Setters for private variables
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
};
