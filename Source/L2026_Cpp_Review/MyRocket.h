// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRocket.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class L2026_CPP_REVIEW_API AMyRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRocket(); // 생성자
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UFUNCTION(BlueprintCallable)
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	//나이아가라
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	//폭발 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<USoundBase> ExplosionSound;

	UFUNCTION(BlueprintImplementableEvent)
	void CallCPPToExecuteBP();

	UFUNCTION(BlueprintNativeEvent)
	void CallCPPToExecuteBPButDefaultCPP();
	void CallCPPToExecuteBPButDefaultCPP_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
