/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/**********************
**Mekgineer Thermaplugg
***********************/

#define spell_pound 74720
#define spell_steam_blast 93655
#define spell_welding_beam 52778

class boss_mekgineer_thermaplugg : public CreatureScript
{
public:
 boss_mekgineer_thermaplugg() : CreatureScript("boss_mekgineer_thermaplugg") {}
 
 struct boss_mekgineer_thermapluggAI : public ScriptedAI
 {
 boss_mekgineer_thermapluggAI(Creature *c): ScriptedAI(c) {}
 
 uint32 pound;
 uint32 steam_blast;
 uint32 welding_beam;
 
 void Reset()
 {
    pound = 8000;
	steam_blast = 10000;
	welding_beam = urand(15000, 20000);
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if (pound<= diff)
       {
            DoCast(me->getVictim(), spell_pound);
            pound = 8000 + rand()%10000;
       } else pound -= diff;
	   
	if (steam_blast<= diff)
       {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 5.0f, true))
            DoCast(target, spell_steam_blast);
            steam_blast = 10000 + rand()%13000;
       }else steam_blast -= diff;
	   
	if(welding_beam<= diff)
       {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
            DoCast(pTarget, spell_welding_beam);
            welding_beam = urand(15000, 20000);
       } else welding_beam -= diff;
	   
	    	   DoMeleeAttackIfReady();
     }
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_mekgineer_thermapluggAI(pCreature);
 }

 };

void AddSC_boss_mekgineer_thermaplugg()
{
    new boss_mekgineer_thermaplugg();
}	