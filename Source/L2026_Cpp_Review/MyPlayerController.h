// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class L2026_CPP_REVIEW_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> DefaultMappingContext;

	virtual void BeginPlay() override;
};

