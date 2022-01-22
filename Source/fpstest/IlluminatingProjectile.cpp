
#include "IlluminatingProjectile.h"

// Sets default values
AIlluminatingProjectile::AIlluminatingProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIlluminatingProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIlluminatingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

