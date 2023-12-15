// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "NPCAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TeamUnreal2023_2Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TeamUnreal2023_2Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPC::ANPC() : skillCoolTime(5.0f), skillTime(0.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������ - AI���ݹ��� Attach
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(GetMesh());
	
	// ������ - AI���ݹ��� ��ġ �� ����, �����ʼ���
	AttackRange->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	AttackRange->InitSphereRadius(50.0f);
	AttackRange->SetCollisionProfileName(TEXT("AttackRange"));

	// ������ - AI��ų �ߵ����� Attach
	SkillRange = CreateDefaultSubobject<USphereComponent>(TEXT("SkillRange"));
	SkillRange->SetupAttachment(GetMesh());

	// ������ - AI��ų �ߵ����� ��ġ �� ����, �����ʼ���
	SkillRange->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	SkillRange->InitSphereRadius(200.0f);
	SkillRange->SetCollisionProfileName(TEXT("SkillRange"));

	// ������ - ��Ʈ�ѷ� ȸ�� ���X
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// ������ - �����Ʈ �������� ȸ��
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// ������ - �޽� ������ ��ġ
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	
	// ������ - ī�޶� �ε��� ����
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("IgnoreCameraPawn"));
	GetMesh()->SetCollisionProfileName(TEXT("IgnoreCameraMesh"));

	// ������ - WidgetComponent�Ҵ�
	BehaviorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BehaviorWidget"));

	// ������ - �÷��̾ UI Window�� �ε����� ���� ����
	BehaviorWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ������ - ��Ʈ�� ����
	BehaviorWidget->SetupAttachment(RootComponent);

	// ������ - UI��ġ ������ ��ġ
	BehaviorWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> BPUserWidget(L"Blueprint'/Game/ThirdPerson/Blueprints/BP_BehaviorUI.BP_BehaviorUI_C'");
	if (BPUserWidget.Class != NULL)
	{
		BehaviorWidget->SetWidgetClass(BPUserWidget.Class);
	}

	// ������ - ������ ���� �κ�

	static ConstructorHelpers::FObjectFinder<UAnimMontage> a_attackMontage(L"UAnimMontage'/Game/Animations/Montage/AttackMontage.AttackMontage'");
	if (a_attackMontage.Object != NULL)
		AttackMontage = a_attackMontage.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> a_hitMontage(L"UAnimMontage'/Game/Animations/Montage/ReactionMontage.ReactionMontage'");
	if (a_hitMontage.Object != NULL)
		GotHitMontage = a_hitMontage.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> t_nothingIcon(L"Texture2D'/Game/Icons/question-mark.question-mark'");
	if (t_nothingIcon.Object != NULL)
		nothingIcon = t_nothingIcon.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> t_patrolIcon(L"Texture2D'/Game/Icons/patrol.patrol'");
	if (t_patrolIcon.Object != NULL)
		patrolIcon = t_patrolIcon.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> t_chaseIcon(L"Texture2D'/Game/Icons/chase.chase'");
	if (t_chaseIcon.Object != NULL)
		chaseIcon = t_chaseIcon.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> t_attackIcon(L"Texture2D'/Game/Icons/attack.attack'");
	if (t_attackIcon.Object != NULL)
		attackIcon = t_attackIcon.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> t_gothitIcon(L"Texture2D'/Game/Icons/gothit.gothit'");
	if (t_gothitIcon.Object != NULL)
		gothitIcon = t_gothitIcon.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> t_skillIcon(L"Texture2D'/Game/Icons/invisible.invisible'");
	if (t_skillIcon.Object != NULL)
		skillIcon = t_skillIcon.Object;

	AttackRange->SetGenerateOverlapEvents(true);
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBeginOverlapAttack);

	myController = ANPCAIController::StaticClass();
	AIControllerClass = myController;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	isFindPlayer = false;
	BehaviorWidget->InitWidget();

	if (UBehaviorUI* const ref = Cast<UBehaviorUI>(BehaviorWidget->GetUserWidgetObject()))
	{
		behaviorUIRef = ref;
	}

	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBeginOverlapPlayer);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnEndOverlapPlayer);
	SkillRange->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBeginOverlapSkillRange);
	SkillRange->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnEndOverlapSkillRange);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->UILookCamera();
	this->OperateSkillLogic(DeltaTime);
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::OnBeginOverlapAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATeamUnreal2023_2Character* PlayerInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (OtherComp->GetCollisionProfileName() == FName("Fist"))
	{		
		// playerHacked ���� false�� ���� ������ �����մϴ�.
		if (PlayerInstance && !PlayerInstance->IsPlayerHacked())
		{
			SetBehavior(EMonsterBehavior::GOTHIT);
			PlayMontageOnBehavior(EMonsterBehavior::GOTHIT);

			//������ - ���� ��ų ������ ������ �ִ� AI��� ��ų ��� �� ��ų ��Ÿ�ӵ� �ʱ�ȭ
			CancleSkillLogic();
			if (GotHitMontage)
			{
				SetBehavior(EMonsterBehavior::GOTHIT);
				PlayMontageOnBehavior(EMonsterBehavior::GOTHIT);

				// IsPlayerHacked()�� ������ �����մϴ�.
				PlayerInstance->SetPlayerHacked(true);

				ATeamUnreal2023_2Character* MyCharacterInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				// �ν��Ͻ��� ��ȿ���� Ȯ���մϴ�.
				if (MyCharacterInstance)
				{
					// �ش� �ν��Ͻ��� �Լ��� ȣ���մϴ�.
					MyCharacterInstance->ChangeHackedPlayerToInvisible();
				}

				// FTimerHandle �ν��Ͻ��� �����մϴ�.
				FTimerHandle TimerHandle;

				// 3�� �ڿ� SetPlayerHacked() �Լ��� ȣ���Ͽ� ���� �������� �ٲߴϴ�.
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerInstance, MyCharacterInstance]()
					{
						if (PlayerInstance)
						{
							PlayerInstance->SetPlayerHacked(false);
						}
						if (MyCharacterInstance)
						{
							MyCharacterInstance->RestoreOriginalMaterial();
						}
					}, 3.0f, false);
			}
		}
	}
}

void ANPC::OnBeginOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("Player"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsObject("TargetActor", OtherActor);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("InAttackRange", true);
	}
}

void ANPC::OnEndOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag("Player"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("InAttackRange", false);
	}
}

void ANPC::OnBeginOverlapSkillRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("Player"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("InSkillRange", true);
	}
}

void ANPC::OnEndOverlapSkillRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag("Player"))
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent()->SetValueAsBool("InSkillRange", false);
	}
}

void ANPC::SetUI(const EMonsterBehavior& behavior)
{
	switch (behavior)
	{
	case EMonsterBehavior::NOTHING:
		behaviorUIRef->SetIconAndText(nothingIcon, FText::FromString(""));
		break;
	case EMonsterBehavior::PATROL:
		behaviorUIRef->SetIconAndText(patrolIcon, FText::FromString("Patrol"));
		break;
	case EMonsterBehavior::CHASE:
		behaviorUIRef->SetIconAndText(chaseIcon, FText::FromString("Chase"));
		break;
	case EMonsterBehavior::ATTACK:
		behaviorUIRef->SetIconAndText(attackIcon, FText::FromString("Attack"));
		break;
	case EMonsterBehavior::GOTHIT:
		behaviorUIRef->SetIconAndText(gothitIcon, FText::FromString("Hit"));
		break;
	case EMonsterBehavior::SKILL:
		behaviorUIRef->SetIconAndText(skillIcon, FText::FromString("Skill"));
		break;
	}
}

void ANPC::UILookCamera()
{
	FVector UILocation = BehaviorWidget->GetComponentLocation();
	FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();

	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(UILocation, cameraLocation);

	BehaviorWidget->SetWorldRotation(newRotation);
}

void ANPC::PlayMontageOnBehavior(EMonsterBehavior behavior)
{
	switch (behavior)
	{
	case EMonsterBehavior::ATTACK:
		PlayAnimMontage(AttackMontage);
		break;
	case EMonsterBehavior::GOTHIT:
		PlayAnimMontage(GotHitMontage);
		break;
	case EMonsterBehavior::SKILL:
		PlayAnimMontage(SkillMontage);
		break;
	}
}

bool ANPC::IsPlayingMontage()
{
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage) 
		|| GetMesh()->GetAnimInstance()->Montage_IsPlaying(GotHitMontage)
			|| GetMesh()->GetAnimInstance()->Montage_IsPlaying(SkillMontage))
		return true;
	else
		return false;
}

void ANPC::OperateSkillLogic(float deltaTime)
{
	if (skillLogic != nullptr)
	{
		switch (skillType)
		{
		case ESkillType::RANDOM:
			HitTypeSkill(deltaTime);
			break;
		case ESkillType::COOLTIME:
			CoolTimeTypeSkill(deltaTime);
			break;
		case ESkillType::CHARGING:
			ChargingTypeSkill();
			break;
		}
	}
}

void ANPC::CancleSkillLogic()
{
	if (skillLogic)
	{
		// ������ - AI�� ������ ��ų������ �ν��Ͻ��� ������
		UBTTask_SkillBase* SkillInstance = skillLogic.GetDefaultObject();
		if (SkillInstance)
		{
			// ������ - AI��Ʈ�ѷ��� BehaviorTree�� ������
			if(UBehaviorTreeComponent* myBT = Cast<UBehaviorTreeComponent>(UAIBlueprintHelperLibrary::GetAIController(this)->GetBrainComponent()))
				SkillInstance->CancleSkillOnFailPerception(*myBT);
		}

		ResetSkillTime();
	}
}

void ANPC::CoolTimeTypeSkill(float deltaTime)
{
	if (Skill.IsBound())
	{
		skillTime += deltaTime;
		if (skillTime >= skillCoolTime)
		{
			isSkillOnGoing = isSkillOnGoing ? false : true;
			Skill.Execute(this, isSkillOnGoing);
			skillTime = 0.f;
		}
	}
	else
	{
		skillTime = 0.f;
	}
}

void ANPC::HitTypeSkill(float deltaTime)
{
	if (Skill.IsBound())
	{
		skillTime += deltaTime;
		if (triggerSkill)
		{
			triggerSkill = false;
			Skill.Execute(this, true);
			StopAnimMontage();
			skillTime = 0.f;
		}
		else
		{
			if (skillTime >= skillCoolTime)
			{
				Skill.Execute(this, false);
				skillTime = 0.f;
			}
		}
	}
	else
	{
		skillTime = 0.f;
	}
}

void ANPC::ChargingTypeSkill()
{

}