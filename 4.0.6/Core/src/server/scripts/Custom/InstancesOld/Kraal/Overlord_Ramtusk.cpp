/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/*****************
**Overlord Ramtusk
******************/

#define spell_battle_shout 9128
#define spell_battle_stance 7165
#define spell_thunderclap 15548

#define SAY_AGGRO "Victory! For Agamaggan!"

class boss_overlord_ramtusk : public CreatureScript
{
public:
 boss_overlord_ramtusk() : CreatureScript("boss_overlord_ramtusk") {}
 
 struct boss_overlord_ramtuskAI : public ScriptedAI
 {
 boss_overlord_ramtuskAI(Creature *c): ScriptedAI(c) {}
 
 uint32 battle_shout;
 uint32 thunderclap;
 
 void EnterCombat(Unit * /*who*/)
 {
    me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
    DoCast(me, spell_battle_stance); 
 }
 
 void Reset()
 {
    battle_shout = 15000;
	thunderclap = urand(10000, 18000);
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if(battle_shout<= diff)
	{
	    DoCast(spell_battle_shout);
		battle_shout = 15000;
    }else battle_shout -= diff;
	
	if (thunderclap<= diff)
    {
        DoCast(me->getVictim(), spell_thunderclap);
        thunderclap = urand(10000, 18000);
    } else thunderclap -= diff;
	
		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_overlord_ramtuskAI(pCreature);
 }

 };

void AddSC_boss_overlord_ramtusk()
{
    new boss_overlord_ramtusk();
}