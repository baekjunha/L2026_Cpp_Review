// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"

#include "MyStaticMeshComponent.h"

#include "Engine/World.h"
#include "MyRocket.h"


// Sets default values
AMyPawn::AMyPawn() //생성자 구현
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm ->SetupAttachment(Box);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 120.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 0.0f;


	//왼쪽날개 오른쪽 날개
	Left = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Left"));
	Left -> SetupAttachment(Body);
	Right = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	// 에셋 적용하기
	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	// 프로펠러 에셋 적용
	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		PropellerMesh(TEXT("/Script/Engine.StaticMesh'/Game/P38/SM_P38_Propeller.SM_P38_Propeller'"));
	if (PropellerMesh.Succeeded())
	{
		Left->SetStaticMesh(PropellerMesh.Object);
		Right->SetStaticMesh(PropellerMesh.Object);
	}

	//프로펠러 위치 조정
	Left->SetRelativeLocation(FVector(36.8f, -21.0f, 1.3f));
	Right->SetRelativeLocation(FVector(36.8f, +21.0f, 1.3f));


	static ConstructorHelpers::FClassFinder<AMyRocket> RocketBP(
		TEXT("/Game/Blueprints/BP_MyRocket")
	);
	if (RocketBP.Succeeded())
	{
		RocketTemplate = RocketBP.Class;
	}

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPawn::Fire() // fire() 함수 구현
{
	UWorld* World = GetWorld(); 
	if (World != nullptr && RocketTemplate) // == if(World)
	{	
		FTransform SpawnTransform = Arrow->K2_GetComponentToWorld(); 
		//FTransform = 위치·회전·크기를 표현, Arrow의 월드 Transform 가져오기
		World->SpawnActor<AMyRocket>(RocketTemplate, SpawnTransform);
		


	}
}




// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

