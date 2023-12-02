// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/CapsuleComponent.h"
#include "NPCAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러 회전 사용X
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 무브먼트 방향으로 회전
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("IgnoreCameraPawn"));
	GetMesh()->SetCollisionProfileName(TEXT("IgnoreCameraMesh"));

	BehaviorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BehaviorWidget"));
	BehaviorWidget->SetupAttachment(RootComponent);
	BehaviorWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> BPUserWidget(L"Blueprint'/Game/ThirdPerson/Blueprints/BP_BehaviorUI.BP_BehaviorUI_C'");
	if (BPUserWidget.Class != NULL)
	{
		BehaviorWidget->SetWidgetClass(BPUserWidget.Class);
	}

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

	myController = ANPCAIController::StaticClass();
	AIControllerClass = myController;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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
	FVector cameraLoction = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();

	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(UILocation, cameraLoction);

	BehaviorWidget->SetWorldRotation(newRotation);
}

UBehaviorTree* ANPC::GetBehaviorTree()const
{
	return Tree;
}
