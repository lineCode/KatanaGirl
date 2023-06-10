// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class KATANAGIRL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sine Parameters", meta = (AllowPrivateAccess))
	float RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sine Parameters", meta = (AllowPrivateAccess))
	float Amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sine Parameters", meta = (AllowPrivateAccess))
	float TimeConstant;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* ItemMesh;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
