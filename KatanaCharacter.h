// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KatanaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;

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

private:
	float BaseTurnRate, BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hair, meta = (AllowPrivateAccess = "true"))
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hair, meta = (AllowPrivateAccess = "true"))
	UGroomComponent* Eyebrows;

public:	
	// Getters for private variables

};
