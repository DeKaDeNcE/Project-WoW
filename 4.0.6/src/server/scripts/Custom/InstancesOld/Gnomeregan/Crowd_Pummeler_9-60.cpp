/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/********************
**Crowd Pummeler 9-60
*********************/

#define spell_arcing_smash 8374
#define spell_crowd_pummel 10887
#define spell_trample 5568

class boss_crowd_pummeler : public CreatureScript
{
public:
 boss_crowd_pummeler() : CreatureScript("boss_crowd_pummeler") {}
 
 struct boss_crowd_pummelerAI : public ScriptedAI
 {
 boss_crowd_pummelerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 arcing_smash;
 uint32 crowd_pummel;
 uint32 trample;
 
 void Reset()
 {
    arcing_smash = 10000;
	trample = urand(8000, 16000);
	crowd_pummel = 18000;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if (arcing_smash<= diff)
       {
            DoCast(me->getVictim(), spell_arcing_smash);
            arcing_smash = 10000 + rand()%15000;
       } else arcing_smash -= diff;
	   
	if(trample<= diff)
       {
            DoCast(spell_trample);
            trample = urand(8000, 16000);
       }else trample -= diff;

    if(crowd_pummel<= diff)
       {
            DoCast(spell_crowd_pummel);
            crowd_pummel = 18000;
       }else crowd_pummel -= diff;

    	   DoMeleeAttackIfReady();
     }
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_crowd_pummelerAI(pCreature);
 }

 };

void AddSC_boss_crowd_pummeler()
{
    new boss_crowd_pummeler();
}	   