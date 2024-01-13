// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Engine/EngineBaseTypes.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Ensures we automatically possess the player whenever we start the game
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Create default values for modifiers
	LookSensitivity = 1.0f;
	SprintModifier = 1.5f;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initiate component pointers
	Camera = FindComponentByClass<UCameraComponent>();
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

	//Bind input axes with relevant functions
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerCharacter::SprintEnd);

}

void APlayerCharacter::MoveForward(float value)
{
	//Determine local forward rotation
	FRotator ForwardRotation = GetControlRotation();
	ForwardRotation.Roll = 0.0f;
	ForwardRotation.Pitch = 0.0f;

	//Built-in function from Character class - moves our player based on direction and magnitude
	AddMovementInput(ForwardRotation.Vector(), value);
}

void APlayerCharacter::Strafe(float value)
{
	//Built-in function from Character class - moves our player based on direction and magnitude
	AddMovementInput(GetActorRightVector(), value);
}

void APlayerCharacter::LookUp(float value)
{
	//Invert look direction if requested
	if (InvertMouseY)
		value *= -1;

	//Store our rotation in a temporary Rotator
	FRotator LookUpRotation = FRotator::ZeroRotator;
	LookUpRotation.Pitch = value *= LookSensitivity;

	//If our Camera's Pitch hasn't gotten past abs(90) then change the camera's pitch
	if (Camera) {
		if(Camera->GetRelativeRotation().Pitch + LookUpRotation.Pitch <= 90.0f && 
			Camera->GetRelativeRotation().Pitch + LookUpRotation.Pitch >= -90.0f)
				Camera->AddRelativeRotation(LookUpRotation);
	}
}

void APlayerCharacter::Turn(float value)
{
	//Change our player capsule's yaw based on value and look sensitivity
	value *= LookSensitivity;
	AddControllerYawInput(value);
}

void APlayerCharacter::SprintStart()
{
	//Modify the walkspeed based on our sprint modifier
	GetCharacterMovement()->MaxWalkSpeed *= SprintModifier;
}

void APlayerCharacter::SprintEnd()
{
	//Modify the walkspeed based on our sprint modifier
	GetCharacterMovement()->MaxWalkSpeed /= SprintModifier;
}

