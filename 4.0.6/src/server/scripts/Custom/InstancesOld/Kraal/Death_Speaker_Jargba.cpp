/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/*********************
**Death Speaker Jargba
**********************/

#define spell_dominate_mind 7645
#define spell_shadow_bolt 20825

class boss_death_speaker_jargba : public CreatureScript
{
public:
 boss_death_speaker_jargba() : CreatureScript("boss_death_speaker_jargba") {}
 
 struct boss_death_speaker_jargbaAI : public ScriptedAI
 {
 boss_death_speaker_jargbaAI(Creature *c): ScriptedAI(c) {}
 
 uint32 dominate_mind;
 uint32 shadow_bolt;
 
 void Reset()
 {
    dominate_mind = urand(15000, 30000);
	shadow_bolt = 8000;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if(dominate_mind<= diff)
    {
       if(Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_dominate_mind);
       dominate_mind = urand(15000, 30000);
    } else dominate_mind -= diff;
	
	if(shadow_bolt<= diff)
    {
    DoCast(me->getVictim(), spell_shadow_bolt);
	shadow_bolt = 8000 + rand()%10000;
    }else shadow_bolt -= diff;
	
	DoMeleeAttackIfReady();
    }
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_death_speaker_jargbaAI(pCreature);
 }

 };

void AddSC_boss_death_speaker_jargba()
{
    new boss_death_speaker_jargba();
}