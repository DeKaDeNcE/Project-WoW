/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */

#include "ScriptPCH.h"
#include "scholomance.h"

/*****************
**Marduk Blackpool
******************/

#define spell_cleave               15284
#define spell_defiling_aura        17695
#define spell_shadow_bolt_volley   17228
#define spell_shadow_shield        12040

class boss_marduk_blackpool : public CreatureScript
{
public:
 boss_marduk_blackpool() : CreatureScript("boss_marduk_blackpool") {}
 
 struct boss_marduk_blackpoolAI : public ScriptedAI
 {
 boss_marduk_blackpoolAI(Creature *c): ScriptedAI(c) {}
 
 uint32 cleave;
 uint32 defiling_aura;
 uint32 shadow_bolt_volley
 
 bool Shadow;
 
 void Reset()
 { 
    cleave = 8000;
	defiling_aura = 25000;
	shadow_bolt_volley = 15000;
	
	Shadow = false;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
        return;
		
    if(cleave<= diff)
    {
        DoCast(me->getVictim(), spell_cleave);
        cleave = 10000;
    }else cleave -= diff;
	
	if(defiling_aura<= diff)
	{
	    DoCast(me, spell_defiling_aura);
		defiling_aura = 30000;
	}else defiling_aura -= diff;
	
	if(shadow_bolt_volley<= diff)
	{
	    DoCast(spell_shadow_bolt_volley);
		shadow_bolt_volley = 15000;
	}else shadow_bolt_volley -= diff;
	
	if (!Shadow && !HealthAbovePct(20))
	{
	    DoCast(me, spell_shadow_shield);
		Shadow = true;
	}
	
			 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_marduk_blackpoolAI(pCreature);
 }
 
 };
 
void AddSC_boss_marduk_blackpool()
{
new boss_marduk_blackpool();()
}
	

