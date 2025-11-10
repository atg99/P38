// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;

UCLASS()
class P38_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:

	virtual void SetupInputComponent() override;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	UInputMappingContext* DefaultMappingContext;
};
