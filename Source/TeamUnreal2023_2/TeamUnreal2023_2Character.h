// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Animation/AnimMontage.h"
#include "TeamUnreal2023_2Character.generated.h"


UCLASS(config = Game)
class ATeamUnreal2023_2Character : public ACharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	// 음영준 - 플레이어 Attack Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	// 음영준 - Attack Action -> 플레이어 공격 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	// 음영준 - Focus Action -> 시간 여유가 되면 추가 될 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FocusAction;

	// 음영준 - RightFistCollisionBox -> 플레이어 공격 시 잠시 활성화되는 박스콜리전
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightFistCollisionBox;

	// 박광훈 - 플레이어 글라이딩
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* GlidingAction;

	// 박광훈 - 플레이어 떨어지는 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		float DescendingRate = 300;

	//박광훈 - 글라이더 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GliderMesh;

	// 박광훈 - 현재 클라이딩 유무
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		bool IsGliding = false;

	//박광훈 - 팻 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* PetSpringArm;

	//박광훈 - 팻 스켈레톤메쉬
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* PetSkeletalMesh;

	// 박광훈 - 플레이어 팻 소환 인풋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SummonPetAction;

	// 박광훈 - 플레이어 팻 소환 인풋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CancelPetAction;

	FVector CurrentVelocity;

	bool OriginalOrientRotation;
	float OriginalGravityScale;
	float OriginalWalkingSpeed;
	float OriginalDecelration;
	float OriginalAcceleration;
	float OriginalAirControl;
	bool OriginalDesiredRotation;
	float MinimumHeight = 300;
	float Delta;

	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupStimulusSource();

	/// <summary>
	/// 박광훈 - 캐릭터 투명 유무
	/// </summary>
	bool IsInvisible;

public:
	FORCEINLINE bool GetIsInvisible()
	{
		return IsInvisible;
	}

	/// <summary>
/// 박광훈 - 투명 머티리얼로 바꿔주는 함수
/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Material")
		void ChangeMaterialToInvisible();

	/// <summary>
	/// 박광훈 - 플레이어 해킹 당할시 적용 함수
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeHackedPlayerToInvisible();

	/// <summary>
	/// 박광훈 - 일반 머티리얼로 바꿔주는 함수
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Material")
		void RestoreOriginalMaterial();

	/// <summary>
	/// 박광훈 - 오버랩 함수
	/// </summary>
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// 박광훈 - 딜레이
	/// </summary>
	FTimerHandle DelayTimerHandle;

	/// <summary>
	/// 박광훈 - 팻 딜레이
	/// </summary>
	FTimerHandle TimerHandle;

	/// <summary>
	/// 박광훈 - 팻 소환 쿨타임
	/// </summary>
	FTimerHandle CoolTimeHandle;

	/// <summary>
	/// 박광훈 - 틱 이벤트 추가
	/// </summary>
	virtual void Tick(float DeltaTime) override;


	void DelayPlay();

	ATeamUnreal2023_2Character();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// 음영준 - Attack기능이 탑재된 함수(Attack Action에 바인딩 됨)
	void Attack();

	// 음영준 - Focus기능이 탑재된 함수(Focus Action에 바인딩 됨)
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Input)
	void Focus();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	// 박광훈 - 글라이더 관련 함수
	UFUNCTION(BlueprintCallable, Category = Character)
	 void Togglegliding();
	// 박광훈 - 글라이더 관련 함수
	void StartGliding();
	// 박광훈 - 글라이더 관련 함수
	void StopGliding();
	// 박광훈 - 글라이더 관련 함수
	bool CanStartGliding();
	// 박광훈 - 글라이더 관련 함수
	void RecordOrignalSettings();
	// 박광훈 - 글라이더 관련 함수
	void DescentPlayer();
	// 박광훈 - 글라이더 관련 함수
	void ApplyOrignalSettings();
	//박광훈 - 펫 소환
	void SummonPet();
	//박광훈 - 펫 소환 취소
	void CancelPet();
	//박광훈 - 펫 소환 가능한지
	bool okayToSummonPet;
	//박광훈 - 펫 소환 쿨타임
	void PetCoolTime();
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// 음영준 - Attack시 RightFistCollision활성화 (Player Attack Montage에 탑재된 PlayerAttackAnimNotifyState클래스에서 호출됨)
	void AttackCollisionEnable();

	// 음영준 - Attack이 끝날 시 RightFistCollision비활성화 (Player Attack Montage에 탑재된 PlayerAttackAnimNotifyState클래스에서 호출됨)
	void AttackCollisionDisable();

	void UpdateInvisible(bool bInvisible);

private:
	bool playerHacked;

public:
	bool IsPlayerHacked() const { return playerHacked; }
	void SetPlayerHacked(bool value) { playerHacked = value; }
};