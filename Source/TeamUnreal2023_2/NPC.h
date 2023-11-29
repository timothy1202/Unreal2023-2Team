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
	// ���� �ൿ�� �����ϱ� ���� enum����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior myBehavior;

	// ���� �ൿUI�� ���� ���� ���� ������Ʈ
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* BehaviorWidget;

	// ���� ������Ʈ�� �Ҵ�� ���� ���۷��� ����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBehaviorUI* behaviorUIRef;

	// �ൿ ������ �̹��� �ؽ��� ���۷�����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* nothingIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* chaseIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* attackIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* gothitIcon;

	// ����Ʈ AI��Ʈ�ѷ� �Ҵ� ���� ����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ANPCAIController> myController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree; //�� Ʈ���� �����Ϳ� �����ȴ�

public:
	// Sets default values for this character's properties
	ANPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �������Ʈ ����� ���� �������ϴ� �Լ� -> UI���� ���� �ڵ���� �� �Լ��� ��
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
	void SetUI(const EMonsterBehavior& behavior);

	// �ൿUI�� �÷��̾� ī�޶� �ٶ󺸰� �ϱ� ���� �Լ�
	void UILookCamera();

	// Setter, Getter�Լ� ���úκ�
	inline void SetBehavior(EMonsterBehavior newBehavior) { myBehavior = newBehavior; }
	inline EMonsterBehavior GetBehavior() { return myBehavior; }
	UBehaviorTree* GetBehaviorTree() const;
};
