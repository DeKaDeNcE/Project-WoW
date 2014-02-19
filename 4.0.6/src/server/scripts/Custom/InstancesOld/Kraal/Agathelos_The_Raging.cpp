/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/*********************
**Agathelos The Raging
**********************/

#define spell_frenzy 8269
#define spell_left_for_dead 8555
#define spell_rampage 8285
#define spell_rushing_charge 8260

class boss_agathelos_the_raging : public CreatureScript
{
public:
 boss_agathelos_the_raging() : CreatureScript("boss_agathelos_the_raging") {}
 
 struct boss_agathelos_the_ragingAI : public ScriptedAI
 {
 boss_agathelos_the_ragingAI(Creature *c): ScriptedAI(c) {}
 
 uint32 left_for_dead;
 uint32 rampage;
 uint32 rushing_charge;
 bool Enrage;
 
 void Reset()
 {
    left_for_dead = 30000;
	rampage = 10000;
	rushing_charge = 35000;
	Enrage = false;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if(left_for_dead<= diff)
    {
       if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
           DoCast(pTarget, spell_left_for_dead);
           left_for_dead = 30000;
    } else left_for_dead -= diff;
	
	if(rampage<= diff)
    {
        DoCast(me->getVictim(), spell_rampage);
	    rampage = 10000;
    }else rampage -= diff;
	
	if (rushing_charge<= diff)
    {
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
        DoCast(target, spell_rushing_charge);
        rushing_charge = 35000;
    } else rushing_charge -= diff;
	
	if (!Enrage && HealthBelowPct(30))
    {
        DoCast(me, spell_frenzy);
        Enrage = true;
    }
	
		DoMeleeAttackIfReady();
    }
    };

 CreatureAI* GetAI(Creature *pCreature) const
 {
 return new boss_agathelos_the_ragingAI(pCreature);
 }

 };

void AddSC_boss_agathelos_the_raging()
{
    new boss_agathelos_the_raging();
}