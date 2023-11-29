// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MonsterBehavior.h"
#include "BehaviorUI.h"

#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class TEAMUNREAL2023_2_API ANPC : public ACharacter
{
	GENERATED_BODY()

private:
	// 적의 행동을 구분하기 위한 enum변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior myBehavior;

	// 적의 행동UI를 띄우기 위한 위젯 컴포넌트
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* BehaviorWidget;

	// 위젯 컴포넌트에 할당된 위젯 레퍼런스 변수
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBehaviorUI* behaviorUIRef;

	// 행동 아이콘 이미지 텍스쳐 레퍼런스들
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* nothingIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* chaseIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* attackIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* gothitIcon;

	// 디폴트 AI컨트롤러 할당 관련 변수
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ANPCAIController> myController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree; //이 트리가 에디터에 설정된다

public:
	// Sets default values for this character's properties
	ANPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 블루프린트 상속을 통해 재정의하는 함수 -> UI세팅 관련 코드들이 이 함수에 들어감
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
	void SetUI(const EMonsterBehavior& behavior);

	// 행동UI가 플레이어 카메라를 바라보게 하기 위한 함수
	void UILookCamera();

	// Setter, Getter함수 관련부분
	inline void SetBehavior(EMonsterBehavior newBehavior) { myBehavior = newBehavior; }
	inline EMonsterBehavior GetBehavior() { return myBehavior; }
	UBehaviorTree* GetBehaviorTree() const;
};
