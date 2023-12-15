// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MonsterBehavior.h"
#include "SkillType.h"
#include "BehaviorUI.h"
#include "BTTask_SkillBase.h"

#include "GameFramework/Character.h"
#include "NPC.generated.h"

// 음영준 - 스킬 사용을 설정할 델리게이트
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateSkill, ANPC*, npc, bool, isSkill);

UCLASS()
class TEAMUNREAL2023_2_API ANPC : public ACharacter
{
	GENERATED_BODY()

private:
	// 음영준 - 적의 공격범위를 위한 Sphere콜리젼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SkillRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ESkillType skillType;

	// 음영준 - 적의 행동을 구분하기 위한 enum변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior myBehavior;

	// 음영준 - 적의 행동UI를 띄우기 위한 위젯 컴포넌트
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* BehaviorWidget;

	// 음영준 - 위젯 컴포넌트로부터 할당된 행동 UI위젯 레퍼런스 변수
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UBehaviorUI* behaviorUIRef;

	// 음영준 - Attack Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	// 음영준 - Reaction Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* GotHitMontage;

	// 음영준 - Skill Montage -> 이 변수는 에디터에서 바꿔줌(각 AI마다 사용하는 스킬이 다르기 때문)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* SkillMontage;

	// 음영준 - 행동 아이콘 이미지 텍스쳐 레퍼런스들
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	UTexture2D* skillIcon;

	// 음영준 - 디폴트 AI컨트롤러 할당 관련 변수
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ANPCAIController> myController;

	// 음영준 - 스킬 로직 클래스
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBTTask_SkillBase> skillLogic;

	// 음영준 - 스킬 사용 쿨타임
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float skillCoolTime;
	float skillTime;

	// 음영준 - 스킬 사용중인지에 관한 bool변수
	bool isSkillOnGoing = false;

	// 음영준 - 트리거용 스킬에 사용
	bool triggerSkill = false;

	// 음영준 - 온힛 트리거용 스킬에 사용
	bool onHitTriggerSkill = false;

	// 음영준 - Anim Instance의 Fighting Idle을 활성화 시킬지에 대한 값으로서 활용
	bool isFindPlayer = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree; //이 트리가 에디터에 설정된다

	// 음영준 - 스킬사용을 위한 서브트리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* SubTree;

public:
	// Sets default values for this character's properties
	ANPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 음영준 - AI가 사용할 스킬 델리게이트 변수
	FDelegateSkill Skill;

	// 음영준 - AI가 공격을 받을때 실행
	UFUNCTION()
	void OnBeginOverlapAttack(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 음영준 - AI공격범위 내에 플레이어 오버랩시 실행
	UFUNCTION()
	void OnBeginOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 음영준 - AI공격범위 내에 플레이어 오버랩이 끝날 시 실행
	UFUNCTION()
	void OnEndOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 음영준 - AI스킬 발동범위 내에 플레이어 오버랩시 실행
	UFUNCTION()
	void OnBeginOverlapSkillRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 음영준 - AI스킬 발동범위 내에 플레이어 오버랩이 끝날 시 실행
	UFUNCTION()
	void OnEndOverlapSkillRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/// <summary>
	/// 음영준 - 행동에 따라 UI를 세팅하는 부분
	/// </summary>
	/// <param name="할당할 새 행동 Enum"></param>
	void SetUI(const EMonsterBehavior& behavior);

	// 음영준 - 행동UI가 플레이어 카메라를 바라보게 하기 위한 함수
	void UILookCamera();

	/// <summary>
	/// 음영준 - 행동 enum에 따라 재생시킬 Montage를 선택하는 함수
	/// </summary>
	/// <param name="재생시킬 행동 Enum (ATTACK하고 GOTHIT만 가능"></param>
	void PlayMontageOnBehavior(EMonsterBehavior behavior);

	// 음영준 - Montage가 실행중인지 반환하는 함수
	bool IsPlayingMontage();
	
	// 음영준 - 스킬 사용 함수
	void OperateSkillLogic(float deltaTime);

	// 음영준 - 스킬 사용 취소 함수
	void CancleSkillLogic();

	/* 음영준 - 각 스킬 타입마다 정의된 함수 */

	// 음영준 - 쿨타임 스킬
	void CoolTimeTypeSkill(float deltaTime);
	// 음영준 - 랜덤으로 나타나는 스킬
	void RandomTypeSkill(float deltaTime);
	// 음영준 - 차징 스킬
	void ChargingTypeSkill(float deltaTime);
	// 음영준 - 온힛 스킬 (맞았을 때 일어나는 스킬)
	void OnHitTypeSkill(float deltaTime);

	// Setter함수들

	FORCEINLINE void SetBehavior(EMonsterBehavior newBehavior) { myBehavior = newBehavior; }
	FORCEINLINE void SetIsFindPlayer(bool isFind) { isFindPlayer = isFind; }
	FORCEINLINE void SetIsSkillOn(bool isSkill) { isSkillOnGoing = isSkill; }
	FORCEINLINE void SetTriggerSkill() { triggerSkill = true; }
	FORCEINLINE void ResetSkillTime() { isSkillOnGoing = false; skillTime = 0.f; }

	// Getter함수들

	// 음영준 - Anim Instance에서 사용하는 함수 -> isFindPlayer반환
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsFindPlayer() const { return isFindPlayer; }

	FORCEINLINE EMonsterBehavior GetBehavior() const { return myBehavior; }
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return Tree; }
	FORCEINLINE UBehaviorTree* GetSubBehaviorTree() const { return SubTree; }
	FORCEINLINE bool GetIsSkillOn() const { return isSkillOnGoing; }
};
