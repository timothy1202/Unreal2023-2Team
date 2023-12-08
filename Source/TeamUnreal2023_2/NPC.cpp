// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "NPCAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TeamUnreal2023_2Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// AI공격범위 Attach
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(GetMesh());
	
	// AI공격범위 위치 및 범위, 프로필설정
	AttackRange->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	AttackRange->InitSphereRadius(50.0f);
	AttackRange->SetCollisionProfileName(TEXT("AttackRange"));

	// 컨트롤러 회전 사용X
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// 무브먼트 방향으로 회전
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// 메시 적절히 배치
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	
	// 카메라 부딪힘 방지
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("IgnoreCameraPawn"));
	GetMesh()->SetCollisionProfileName(TEXT("IgnoreCameraMesh"));

	// WidgetComponent할당
	BehaviorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BehaviorWidget"));

	// 플레이어가 UI Window에 부딪히는 현상 방지
	BehaviorWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 루트에 결합
	BehaviorWidget->SetupAttachment(RootComponent);

	// UI위치 적절히 배치
	BehaviorWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> BPUserWidget(L"Blueprint'/Game/ThirdPerson/Blueprints/BP_BehaviorUI.BP_BehaviorUI_C'");
	if (BPUserWidget.Class != NULL)
	{
		BehaviorWidget->SetWidgetClass(BPUserWidget.Class);
	}

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

	AttackRange->SetGenerateOverlapEvents(true);
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBeginOverlapAttack);

	myController = ANPCAIController::StaticClass();
	AIControllerClass = myController;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	isFindPlayer = false;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	BehaviorWidget->InitWidget();

	if (UBehaviorUI* const ref = Cast<UBehaviorUI>(BehaviorWidget->GetUserWidgetObject()))
	{
		behaviorUIRef = ref;
	}

	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBeginOverlapPlayer);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnEndOverlapPlayer);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->UILookCamera();
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::OnBeginOverlapAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetCollisionProfileName() == FName("Fist"))
	{
		if (GotHitMontage)
		{
			SetBehavior(EMonsterBehavior::GOTHIT);
			PlayMontageOnBehavior(EMonsterBehavior::GOTHIT);
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

void ANPC::SetUI_Implementation(const EMonsterBehavior& behavior)
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
	}
}

bool ANPC::IsPlayingMontage()
{
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage) || GetMesh()->GetAnimInstance()->Montage_IsPlaying(GotHitMontage))
		return true;
	else
		return false;
}
