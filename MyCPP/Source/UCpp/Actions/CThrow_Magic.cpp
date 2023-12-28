// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CThrow_Magic.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACThrow_Magic::ACThrow_Magic()
{

	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", Sphere);

}
