#ifndef SKILLEFFECTTYPE_H
#define SKILLEFFECTTYPE_H
enum skillEffectType {
	none,

	selfAttackBoost,
	selfDefenseBoost,
	selfHitRateBoost,
	selfEvationBoost,
	selfComatose,
	selfCharge,
	selfAnticipate,
	selfDamage,

	giveAttackWeaken,
	giveHitRateWeaken,
	giveDefenseWeaken,
	giveEvationWeaken,
	giveComatose
};
#endif