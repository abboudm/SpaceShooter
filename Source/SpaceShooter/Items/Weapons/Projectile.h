#pragma once
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS(config=Game, Blueprintable, BlueprintType, Abstract)
class AProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class UStaticMeshComponent* Mesh;
	//Radial Force Component
		UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

public:
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	float GetHitDamage();
	//CanDamage
	//Damage

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class UHDamageType> DamageType;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		float HitDamage;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		float DamageRadius;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		bool bSticky;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		bool bBounce;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		int BounceLimit;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		float HitImpulseStrength;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		UParticleSystem* ExplosionFX;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		USoundCue* ExplosionSound;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AImpactEffect> ImpactTemplate;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		UParticleSystem* TrailFX;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		FVector TrailScale;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		bool bExplosive;
	

protected:
	void SpawnTrailEffects();
	void Stick(UPrimitiveComponent* OtherComp);
	void Detonate();
	void SpawnImpactEffects();
	bool bStuck;
	int CurrentBounce;
	TArray<AActor *> IgnoreDamageActors;
	void OnDestroy();

	virtual float TakeDamage(
		float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator,
		AActor * DamageCauser) override;


};

