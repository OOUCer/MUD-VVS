#ifndef SKILLEFFECTTYPE_H
#define SKILLEFFECTTYPE_H

// 技能效果类型枚举
enum skillEffectType {
    none,                   // 无效果

    selfAttackBoost,        // 自身攻击提升
    selfDefenseBoost,       // 自身防御提升
    selfHitRateBoost,       // 自身命中率提升
    selfEvationBoost,       // 自身闪避率提升
    selfComatose,           // 自身昏迷
    selfCharge,             // 自身充能
    selfAnticipate,         // 自身预判
    selfDamage,             // 自身伤害

    giveAttackWeaken,       // 给予攻击削弱
    giveHitRateWeaken,      // 给予命中率削弱
    giveDefenseWeaken,      // 给予防御削弱
    giveEvationWeaken,      // 给予闪避率削弱
    giveComatose            // 给予昏迷
};

#endif // SKILLEFFECTTYPE_H
