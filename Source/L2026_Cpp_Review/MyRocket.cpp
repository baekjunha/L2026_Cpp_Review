// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 2000.0f;
	Movement->MaxSpeed = 2000.0f;
	Movement->ProjectileGravityScale = 0.0f;

	//로켓 메시 연결
	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/P38/SM_Rocket.SM_Rocket'"));

	if (SM_Rocket.Succeeded())
	{
		Body->SetStaticMesh(SM_Rocket.Object);
	}


}


// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic( //콜리전 이벤트 델리게이트 작성
		this,
		&AMyRocket::ProcessBeginOverlap
	);
	SetLifeSpan(3.0f);
		
}

void AMyRocket::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) //콜리전 이벤트
{
	// 조건 1: OtherActor가 nullptr이 아닐 것
	// 조건 2: OtherActor에 "Player" 태그가 없을 것
	// 두 조건을 동시에 만족하는 if문 작성
	if (OtherActor && !OtherActor->ActorHasTag(TEXT("Player")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Rocket Overlap Detected"));
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
		UGameplayStatics::ApplyDamage(
			OtherActor,
			10.0f,
			nullptr,
			this,
			UDamageType::StaticClass()
		);

		//CallCPPToExecuteBP();

		CallCPPToExecuteBPButDefaultCPP();

		Destroy();
	}	
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyRocket::CallCPPToExecuteBPButDefaultCPP_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Default CPP Executed"));
}
