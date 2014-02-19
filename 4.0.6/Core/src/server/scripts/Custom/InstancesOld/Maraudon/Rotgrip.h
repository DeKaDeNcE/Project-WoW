/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/********
**Rotgrip
*********/

#define spell_fatal_bite 16495
#define spell_puncture 15976

class boss_rotgrip : public CreatureScript
{
public:
 boss_rotgrip() : CreatureScript("boss_rotgrip") {}
 
 struct boss_rotgripAI : public ScriptedAI
 {
 boss_rotgripAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fatal_bite;
 uint32 puncture;
 
 void Reset()
 {
 fatal_bite = 20000;
 puncture = urand(15000, 25000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (fatal_bite<= diff)
 {
    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 5.0f, true))
    DoCast(target, spell_fatal_bite);
    fatal_bite = 20000;
 } else fatal_bite -= diff;
 
 if (puncture<= diff)
 {
    DoCast(me->getVictim(), spell_puncture);
    puncture = urand(15000, 25000);
 } else puncture -= diff;
	
	DoMeleeAttackIfReady();
    }
    };
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_rotgripAI(pCreature);
 }

 };

void AddSC_boss_rotgrip()
{
    new boss_rotgrip();
}