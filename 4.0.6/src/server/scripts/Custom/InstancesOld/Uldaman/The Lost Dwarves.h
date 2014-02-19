/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By JeanClaude
*/

#include "ScriptPCH.h"
#include "uldaman.h"

/*****************
**The Lost Dwarves
******************/

/*******
**Baelog
********/

#define spell_shoot 15620
#define spell_strike 14516

class boss_baelog : public CreatureScript
{
public:
 boss_baelog() : CreatureScript("boss_baelog") {}
 
 struct boss_baelogAI : public ScriptedAI
 {
 boss_baelogAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shoot;
 uint32 strike;
 
 void Reset()
 {
 shoot = 3000;
 strike = 5000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (shoot <= diff)
 {
    Unit *pTarget = NULL;
    pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
    if (pTarget)
    DoCast(pTarget, spell_shoot);
    shoot = 3000;
 } else shoot -= diff;
 
 if(strike<= diff)
 {
    DoCast(me->getVictim(), spell_strike);
	strike = 5000 + rand()%8000;
 }else strike -= diff;
 
 	DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_baelogAI(pCreature);
 }
};

/*****************
**Eric "The Swift"
******************/

#define spell_rushing_charge 6268

class boss_eric : public CreatureScript
{
public:
 boss_eric() : CreatureScript("boss_eric") {}
 
 struct boss_ericAI : public ScriptedAI
 {
 boss_ericAI(Creature *c): ScriptedAI(c) {}
 
 uint32 rushing_charge;
 
 void Reset()
 {
 rushing_charge = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
  if (rushing_charge<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_rushing_charge);
 rushing_charge = 10000;
 } else rushing_charge -= diff;
 
 	DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_ericAI(pCreature);
 }
};

/*****
**Olaf
******/

#define spell_shield_slam 8242

class boss_olaf : public CreatureScript
{
public:
 boss_olaf() : CreatureScript("boss_olaf") {}
 
 struct boss_olafAI : public ScriptedAI
 {
 boss_olafAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shield_slam;
 
 void Reset()
 {
 shield_slam = 5000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shield_slam<= diff)
 {
    DoCast(me->getVictim(), spell_shield_slam);
	shield_slam = 5000 + rand()%8000;
 }else shield_slam -= diff;
 
 	DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_olafAI(pCreature);
 }
};

void AddSC_The_Lost_Dwarves()
{
   new boss_baelog();
   new boss_eric();
   new boss_olaf();
}



 
