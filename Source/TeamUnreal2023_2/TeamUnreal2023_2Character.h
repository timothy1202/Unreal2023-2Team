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

	// ������ - �÷��̾� Attack Montage
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

	// ������ - Attack Action -> �÷��̾� ���� �׼�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	// ������ - Focus Action -> �ð� ������ �Ǹ� �߰� �� �׼�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FocusAction;

	// ������ - RightFistCollisionBox -> �÷��̾� ���� �� ��� Ȱ��ȭ�Ǵ� �ڽ��ݸ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightFistCollisionBox;

	// �ڱ��� - �÷��̾� �۶��̵�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* GlidingAction;

	// �ڱ��� - �÷��̾� �������� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		float DescendingRate = 300;

	//�ڱ��� - �۶��̴� �޽�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GliderMesh;

	// �ڱ��� - ���� Ŭ���̵� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		bool IsGliding = false;

	//�ڱ��� - �� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* PetSpringArm;

	//�ڱ��� - �� ���̷���޽�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* PetSkeletalMesh;

	// �ڱ��� - �÷��̾� �� ��ȯ ��ǲ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SummonPetAction;

	// �ڱ��� - �÷��̾� �� ��ȯ ��ǲ
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
	/// �ڱ��� - ĳ���� ���� ����
	/// </summary>
	bool IsInvisible;

public:
	FORCEINLINE bool GetIsInvisible()
	{
		return IsInvisible;
	}

	/// <summary>
/// �ڱ��� - ���� ��Ƽ����� �ٲ��ִ� �Լ�
/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Material")
		void ChangeMaterialToInvisible();

	/// <summary>
	/// �ڱ��� - �÷��̾� ��ŷ ���ҽ� ���� �Լ�
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Material")
	void ChangeHackedPlayerToInvisible();

	/// <summary>
	/// �ڱ��� - �Ϲ� ��Ƽ����� �ٲ��ִ� �Լ�
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Material")
		void RestoreOriginalMaterial();

	/// <summary>
	/// �ڱ��� - ������ �Լ�
	/// </summary>
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// �ڱ��� - ������
	/// </summary>
	FTimerHandle DelayTimerHandle;

	/// <summary>
	/// �ڱ��� - �� ������
	/// </summary>
	FTimerHandle TimerHandle;

	/// <summary>
	/// �ڱ��� - �� ��ȯ ��Ÿ��
	/// </summary>
	FTimerHandle CoolTimeHandle;

	/// <summary>
	/// �ڱ��� - ƽ �̺�Ʈ �߰�
	/// </summary>
	virtual void Tick(float DeltaTime) override;


	void DelayPlay();

	ATeamUnreal2023_2Character();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// ������ - Attack����� ž��� �Լ�(Attack Action�� ���ε� ��)
	void Attack();

	// ������ - Focus����� ž��� �Լ�(Focus Action�� ���ε� ��)
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Input)
	void Focus();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	// �ڱ��� - �۶��̴� ���� �Լ�
	UFUNCTION(BlueprintCallable, Category = Character)
	 void Togglegliding();
	// �ڱ��� - �۶��̴� ���� �Լ�
	void StartGliding();
	// �ڱ��� - �۶��̴� ���� �Լ�
	void StopGliding();
	// �ڱ��� - �۶��̴� ���� �Լ�
	bool CanStartGliding();
	// �ڱ��� - �۶��̴� ���� �Լ�
	void RecordOrignalSettings();
	// �ڱ��� - �۶��̴� ���� �Լ�
	void DescentPlayer();
	// �ڱ��� - �۶��̴� ���� �Լ�
	void ApplyOrignalSettings();
	//�ڱ��� - �� ��ȯ
	void SummonPet();
	//�ڱ��� - �� ��ȯ ���
	void CancelPet();
	//�ڱ��� - �� ��ȯ ��������
	bool okayToSummonPet;
	//�ڱ��� - �� ��ȯ ��Ÿ��
	void PetCoolTime();
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// ������ - Attack�� RightFistCollisionȰ��ȭ (Player Attack Montage�� ž��� PlayerAttackAnimNotifyStateŬ�������� ȣ���)
	void AttackCollisionEnable();

	// ������ - Attack�� ���� �� RightFistCollision��Ȱ��ȭ (Player Attack Montage�� ž��� PlayerAttackAnimNotifyStateŬ�������� ȣ���)
	void AttackCollisionDisable();

	void UpdateInvisible(bool bInvisible);

private:
	bool playerHacked;

public:
	bool IsPlayerHacked() const { return playerHacked; }
	void SetPlayerHacked(bool value) { playerHacked = value; }
};