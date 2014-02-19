/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/*****************
**Aggem Thorncurse
******************/

#define spell_battle_shout 30931
#define spell_chain_heal 14900
#define spell_summon_boar_spirit 8286

class boss_aggem_thorncurse : public CreatureScript
{
public:
 boss_aggem_thorncurse() : CreatureScript("boss_aggem_thorncurse") {}
 
 struct boss_aggem_thorncurseAI : public ScriptedAI
 {
 boss_aggem_thorncurseAI(Creature *c): ScriptedAI(c) {}
 
 uint32 battle_shout;
 uint32 chain_heal;
 uint32 summon_boar_spirit;
 
 void Reset()
 {
    battle_shout = urand(15000, 30000);
	chain_heal = urand(8000, 16000);
	summon_boar_spirit = 25000;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if(battle_shout<= diff)
	{
	    DoCast(spell_battle_shout);
		battle_shout = urand(15000, 30000);
	}else battle_shout -= diff;
	
	if(chain_heal<= diff)
	{
	    DoCast(me, spell_chain_heal);
		chain_heal = urand(8000, 16000);
	}else chain_heal -= diff;
	
	if(summon_boar_spirit<= diff)
	{
	    DoCast(spell_summon_boar_spirit);
		summon_boar_spirit = 25000;
	}else summon_boar_spirit -= diff;
	
	DoMeleeAttackIfReady();
    }
    };

CreatureAI* GetAI(Creature* pCreature) const
{
return new boss_aggem_thorncurseAI(pCreature);
}

};

void AddSC_boss_aggem_thorncurse()
{
    new boss_aggem_thorncurse();
}