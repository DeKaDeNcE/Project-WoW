/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */

#include "ScriptPCH.h"
#include "scholomance.h"

/***********
**Rattlegore
************/

#define spell_knock_away 10101
#define spell_strike 18368
#define spell_war_stomp 16727

class boss_rattlegore : public CreatureScript
{
public:
 boss_rattlegore() : CreatureScript("boss_rattlegore") {}
 
 struct boss_rattlegoreAI : public ScriptedAI
 {
 boss_rattlegoreAI(Creature *c): ScriptedAI(c) {}
 
 uint32 knock_away;
 uint32 strike;
 uint32 war_stomp;
 
 void Reset()
 { 
    knock_away = 10000;
	strike = 5000;
	war_stomp = 18000;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
        return;

	if(knock_away<= diff)
    {
        DoCast(me->getVictim(), spell_knock_away);
        knock_away = 12000;
    }else knock_away -= diff;
	
	if(strike<= diff)
    {
        DoCast(me->getVictim(), spell_strike);
        strike = 8000;
    }else strike -= diff;
	
	if(war_stomp <= diff)
	{
	   DoCast(spell_war_stomp);
	   war_stomp = 20000;
	}else war_stomp -= diff;
	
		 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_rattlegoreAI(pCreature);
 }
 
 };
 
void AddSC_boss_rattlegore()
{
new boss_rattlegore();
}