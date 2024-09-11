#ifndef SKILLEFFECTTYPE_H
#define SKILLEFFECTTYPE_H

// ����Ч������ö��
enum skillEffectType {
    none,                   // ��Ч��

    selfAttackBoost,        // ����������
    selfDefenseBoost,       // �����������
    selfHitRateBoost,       // ��������������
    selfEvationBoost,       // ��������������
    selfComatose,           // �������
    selfCharge,             // �������
    selfAnticipate,         // ����Ԥ��
    selfDamage,             // �����˺�

    giveAttackWeaken,       // ���蹥������
    giveHitRateWeaken,      // ��������������
    giveDefenseWeaken,      // �����������
    giveEvationWeaken,      // ��������������
    giveComatose            // �������
};

#endif // SKILLEFFECTTYPE_H
