/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "firelands.h"

enum Yells
{
SAY_AGGRO = -1999971,
SAY_SOFT_ENRAGE = -1999972, //TODO Add Sound
SAY_ON_DOGS_FALL = -1999973, //TODO Add Sound
SAY_ON_DEAD = -1999974, //TODO Add Sound
};

enum Spells
{

};

enum Events
{

};

// ######### Lord Rhyolith #########

class boss_rhyolith : public CreatureScript
{
public:
boss_rhyolith() : CreatureScript("boss_rhyolith"){}

CreatureAI* GetAI(Creature* creature) const
{
return new boss_rhyolithAI(creature);
}

struct boss_rhyolithAI : public BossAI
{
boss_rhyolithAI(Creature* c) : BossAI(c, DATA_SHANNOX)
{
instance = me->GetInstanceScript();
}

InstanceScript* instance;
bool enrage;

void Reset()
{
instance->SetBossState(DATA_RHYOLITH, NOT_STARTED);
events.Reset();

me->GetMotionMaster()->MoveTargetedHome();

}

/*void JustSummoned(Creature* summon)
{
summons.Summon(summon);
summon->setActive(true);
}*/

void KilledUnit(Unit * /*victim*/)
{
}

void JustDied(Unit * /*victim*/)
{

instance->SetBossState(DATA_RHYOLITH, DONE);
DoScriptText(SAY_ON_DEAD, me);
_JustDied();
}

void EnterCombat(Unit* who)
{

_EnterCombat();
}

void UpdateAI(const uint32 diff)
{


}
};
};

void AddSC_boss_rhyolith()
{
new boss_rhyolith();
}