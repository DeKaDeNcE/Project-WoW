/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/**********
**Razorlash
***********/

#define spell_cleave 40504
#define spell_puncture 15976

class boss_razorlash : public CreatureScript
{
public:
 boss_razorlash() : CreatureScript("boss_razorlash") {}
 
 struct boss_razorlashAI : public ScriptedAI
 {
 boss_razorlashAI(Creature *c): ScriptedAI(c) {}
 
 uint32 cleave;
 uint32 puncture;
 
 void Reset()
 {
    cleave = 8000;
	puncture = urand(15000, 20000);
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if (cleave<= diff)
       {
            DoCast(me->getVictim(), spell_cleave);
            cleave = 8000 + rand()%10000;
       } else cleave -= diff;
	   
	if (puncture<= diff)
       {
            DoCast(me->getVictim(), spell_puncture);
            puncture = urand(15000, 20000);
       } else puncture -= diff;
	
			DoMeleeAttackIfReady();
    }
    };
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_razorlashAI(pCreature);
 }

 };

void AddSC_boss_razorlash()
{
    new boss_razorlash();
}