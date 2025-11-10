// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"

//CDO 초기화 할때 용도, class 구조 잡거나 초기화 할때
AMyGameModeBase::AMyGameModeBase()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("ㅂㅂㅂㅂㅂㅂㅂ"));
	//StaticClass();

	PlayerControllerClass = AMyPlayerController::StaticClass(); //CDO가 기억하는 클래스이름
	DefaultPawnClass = AMyPawn::StaticClass();
}
