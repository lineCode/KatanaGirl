// Fill out your copyright notice in the Description page of Project Settings.


#include "KatanaAnimInstance.h"
#include "KatanaCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UKatanaAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EchoCharacter = Cast<AKatanaCharacter>(TryGetPawnOwner());
}

void UKatanaAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (EchoCharacter == nullptr) EchoCharacter = Cast<AKatanaCharacter>(TryGetPawnOwner());

	if (EchoCharacter)
	{
		// Get the lateral speed of the character from velocity
		Speed = UKismetMathLibrary::VSizeXY(EchoCharacter->GetCharacterMovement()->Velocity);

		// Is the character in the air?
		bIsInAir = EchoCharacter->GetCharacterMovement()->IsFalling();

		// Is the character moving?
		bIsMoving = EchoCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0;

		// What is the current state of the Character?
		CharacterState = EchoCharacter->GetCharacterState();
	}
}
