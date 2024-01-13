// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GAMEPROJECT23TO24_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Control modifiers
	UPROPERTY(EditInstanceOnly)
	bool InvertMouseY;

	UPROPERTY(EditInstanceOnly)
	float LookSensitivity;

	UPROPERTY(EditInstanceOnly)
	float SprintModifier;


	//Pointers to blueprint components
	UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement functions
	void MoveForward(float value);
	void Strafe(float value);
	void LookUp(float value);
	void Turn(float value);

	//Sprint Functions
	void SprintStart();
	void SprintEnd();
};
