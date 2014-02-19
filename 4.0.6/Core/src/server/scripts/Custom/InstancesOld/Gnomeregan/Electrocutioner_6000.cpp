/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/*********************
**Electrocutioner 6000
**********************/

#define spell_chain_bolt 11085
#define spell_megavolt 11082
#define spell_shock 11084

#define SAY_AGGRO "Electric justice!"

class boss_electrocutioner_6000 : public CreatureScript
{
public:
 boss_electrocutioner_6000() : CreatureScript("boss_electrocutioner_6000") {}
 
 struct boss_electrocutioner_6000AI : public ScriptedAI
 {
 boss_electrocutioner_6000AI(Creature *c): ScriptedAI(c) {}
 
 uint32 chain_bolt;
 uint32 megavolt;
 uint32 shock;
 
 void Reset()
 {
    chain_bolt = 10000;
	megavolt = urand(8000, 16000);
	shock = 18000;
 }
 
 void EnterCombat(Unit * /*who*/)
 {
    me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	
	if (chain_bolt<= diff)
       {
            DoCast(me->getVictim(), spell_chain_bolt);
            chain_bolt = 10000 + rand()%10000;
       } else chain_bolt -= diff;
	   
	if (megavolt<= diff)
       {
            DoCast(me->getVictim(), spell_megavolt);
            megavolt = urand(8000, 16000);
       } else megavolt -= diff;
	
	if (shock<= diff)
       {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
            DoCast(target, spell_shock);
            shock = 18000;
       }else shock -= diff;
	
	   DoMeleeAttackIfReady();
     }
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_electrocutioner_6000AI(pCreature);
 }

 };

void AddSC_boss_electrocutioner_6000()
{
    new boss_electrocutioner_6000();
}