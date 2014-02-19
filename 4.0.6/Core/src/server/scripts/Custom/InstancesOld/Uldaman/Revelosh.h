/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By JeanClaude
*/

#include "ScriptPCH.h"
#include "uldaman.h"

/*********
**Revelosh
**********/

#define spell_chain_lightning 16006
#define spell_lightning_bolt 15801

class boss_revelosh : public CreatureScript
{
public:
 boss_revelosh() : CreatureScript("boss_revelosh") {}
 
 struct boss_reveloshAI : public ScriptedAI
 {
 boss_reveloshAI(Creature *c): ScriptedAI(c) {}
 
 uint32 lightning;
 
 void Reset()
 {
 lightning = urand(6000, 9000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (lightning <= diff)
 {
	if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
	DoCast(pTarget, RAND(spell_chain_lightning, spell_lightning_bolt));
	lightning = urand(6000, 9000);
 }else
	lightning -= diff;
	
	DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_reveloshAI(pCreature);
 }
};

void AddSC_boss_revelosh()
{
    new boss_revelosh();
}

