/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/****************
**Vicious Fallout
*****************/

#define spell_toxic_volley 21687

class boss_vicious_fallout : public CreatureScript
{
public:
 boss_vicious_fallout() : CreatureScript("boss_vicious_fallout") {}
 
 struct boss_vicious_falloutAI : public ScriptedAI
 {
 boss_vicious_falloutAI(Creature *c): ScriptedAI(c) {}
 
 uint32 toxic_volley;
 
 void Reset()
 {
    toxic_volley = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if (toxic_volley<= diff)
       {
            DoCast(me->getVictim(), spell_toxic_volley);
            toxic_volley = urand(5000, 8000);
       } else toxic_volley -= diff;
	   
	DoMeleeAttackIfReady();
    }
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_vicious_falloutAI(pCreature);
 }

 };

void AddSC_boss_vicious_fallout()
{
    new boss_vicious_fallout();
}