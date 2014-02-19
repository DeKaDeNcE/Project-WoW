/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By JeanClaude
*/

#include "ScriptPCH.h"
#include "uldaman.h"

/********
**Grimlok
*********/

#define spell_bloodlust 6742
#define spell_chain_bolt 8292
#define spell_lightning_bolt 12167
#define spell_shrink 11892

class boss_grimlok : public CreatureScript
{
public:
 boss_grimlok() : CreatureScript("boss_grimlok") {}
 
 struct boss_grimlokAI : public ScriptedAI
 {
 boss_grimlokAI(Creature *c): ScriptedAI(c) {}
 
 uint32 bloodlust;
 uint32 chain_bolt;
 uint32 lightning_bolt;
 uint32 shrink;
 
 void Reset()
 {
 bloodlust = 40000;
 chain_bolt = urand(8000, 12000);
 lightning_bolt = urand(5000, 8000);
 shrink = 25000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(bloodlust <= diff)
 {
    DoCast(spell_bloodlust);
	bloodlust = 40000;
 }else bloodlust -= diff;
 
 if (chain_bolt<= diff)
 {
    DoCast(me->getVictim(), spell_chain_bolt);
    chain_bolt = urand(8000, 12000);
 } else chain_bolt -= diff;
 
 if (lightning_bolt<= diff)
 {
    DoCast(me->getVictim(), spell_lightning_bolt);
    lightning_bolt = urand(5000, 8000);
 } else lightning_bolt -= diff;
 
 if(shrink<= diff)
 {
    DoCast(spell_shrink);
	shrink = 25000;
 }else shrink -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_grimlokAI(pCreature);
 }
 
 };
 
void AddSC_boss_grimlok()
{
    new boss_grimlok();
}