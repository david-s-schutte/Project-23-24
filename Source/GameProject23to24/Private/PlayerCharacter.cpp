// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Engine/EngineBaseTypes.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Ensures we automatically possess the player whenever we start the game
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Allows us to use pitch rotations
	bUseControllerRotationPitch = true;

	LookSensitivity = 1.0f;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
}

void APlayerCharacter::MoveForward(float value)
{
	FRotator ForwardRotation = GetControlRotation();
	ForwardRotation.Roll = 0.0f;
	ForwardRotation.Pitch = 0.0f;

	//Built-in function from Character class - moves our player based on direction and magnitude
	AddMovementInput(ForwardRotation.Vector(), value);
	//AddMovementInput(GetActorForwardVector(), value);
}

void APlayerCharacter::Strafe(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void APlayerCharacter::LookUp(float value)
{
	if (!InvertMouseY)
		value *= -1;

	value *= LookSensitivity;
	AddControllerPitchInput(value);
}

void APlayerCharacter::Turn(float value)
{
	value *= LookSensitivity;
	AddControllerYawInput(value);
}

