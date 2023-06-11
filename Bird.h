// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class KATANAGIRL_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bird, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bird, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BirdMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ViewCamera;

	float BaseTurnRate, BaseLookUpRate;
};
