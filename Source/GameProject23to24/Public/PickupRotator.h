// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT23TO24_API UPickupRotator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupRotator();
	UPROPERTY(EditInstanceOnly)
	bool roll;
	UPROPERTY(EditInstanceOnly)
	bool pitch;
	UPROPERTY(EditInstanceOnly)
	bool yaw;

private:
	UPROPERTY(EditInstanceOnly)
	float RotSpeed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TickRotateObject(const float& DeltaTime);
		
};
