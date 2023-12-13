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
	// ������ - ���� ���ݹ����� ���� Sphere�ݸ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackRange;

	// ������ - ���� �ൿ�� �����ϱ� ���� enum����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior myBehavior;

	// ������ - ���� �ൿUI�� ���� ���� ���� ������Ʈ
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* BehaviorWidget;

	// ������ - ���� ������Ʈ�κ��� �Ҵ�� �ൿ UI���� ���۷��� ����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBehaviorUI* behaviorUIRef;

	// ������ - Attack Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	// ������ - Reaction Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* GotHitMontage;

	// ������ - �ൿ ������ �̹��� �ؽ��� ���۷�����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* nothingIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* patrolIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* chaseIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* attackIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* gothitIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* skillIcon;

	// ������ - ����Ʈ AI��Ʈ�ѷ� �Ҵ� ���� ����
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ANPCAIController> myController;

	// ������ - Anim Instance�� Fighting Idle�� Ȱ��ȭ ��ų���� ���� �����μ� Ȱ��
	bool isFindPlayer = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree; //�� Ʈ���� �����Ϳ� �����ȴ�

	// ������ - ��ų����� ���� ����Ʈ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* SubTree;

public:
	// Sets default values for this character's properties
	ANPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ������ - AI�� ������ ������ ����
	UFUNCTION()
	void OnBeginOverlapAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// ������ - AI���ݹ��� ���� �÷��̾� �������� ����
	UFUNCTION()
	void OnBeginOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// ������ - AI���ݹ��� ���� �÷��̾� �������� ���� �� ����
	UFUNCTION()
	void OnEndOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/// <summary>
	/// ������ - �ൿ�� ���� UI�� �����ϴ� �κ�
	/// </summary>
	/// <param name="�Ҵ��� �� �ൿ Enum"></param>
	void SetUI(const EMonsterBehavior& behavior);

	// ������ - �ൿUI�� �÷��̾� ī�޶� �ٶ󺸰� �ϱ� ���� �Լ�
	void UILookCamera();

	/// <summary>
	/// ������ - �ൿ enum�� ���� �����ų Montage�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="�����ų �ൿ Enum (ATTACK�ϰ� GOTHIT�� ����"></param>
	void PlayMontageOnBehavior(EMonsterBehavior behavior);

	// ������ - Montage�� ���������� ��ȯ�ϴ� �Լ�
	bool IsPlayingMontage();
	

	// Setter�Լ���

	FORCEINLINE void SetBehavior(EMonsterBehavior newBehavior) { myBehavior = newBehavior; }
	FORCEINLINE void SetIsFindPlayer(bool isFind) { isFindPlayer = isFind; }

	// Getter�Լ���

	// ������ - Anim Instance���� ����ϴ� �Լ� -> isFindPlayer��ȯ
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsFindPlayer() const { return isFindPlayer; }

	FORCEINLINE EMonsterBehavior GetBehavior() const { return myBehavior; }
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return Tree; }
	FORCEINLINE UBehaviorTree* GetSubBehaviorTree() const { return SubTree; }
};
