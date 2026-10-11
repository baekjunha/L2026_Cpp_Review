// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStaticMeshComponent.h"

UMyStaticMeshComponent::UMyStaticMeshComponent() // 생성자 구현
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMyStaticMeshComponent::TickComponent(float DeltaTime,ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{ //재정의한 TickComponent 구현
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); // 부모에서 공통부분은 그대로 부모로 실행
	AddLocalRotation(FRotator(0.0f, 0.0f, RotationSpeed* DeltaTime)); // 이걸 재정의 하는듯?
}