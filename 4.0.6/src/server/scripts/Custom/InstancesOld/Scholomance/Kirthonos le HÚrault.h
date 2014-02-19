/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */

#include "ScriptPCH.h"
#include "scholomance.h"

/*********************
**Kirthonos Le Hérault
**********************/

//Bat Form
#define spell_wing_flap            12882
#define spell_pierce_armor         6016
#define spell_swoop                18144
#define spell_disarm               8379

//Changeform Spell
#define spell_kirthonos_transform  16467

//Vampire Form
#define spell_curse_of_tongues    12889
#define spell_dominate_mind        14515
#define spell_shadow_bolt_volley   17228

class boss_kirthonos_le_herault : public CreatureScript
{
public:
 boss_kirthonos_le_herault() : CreatureScript("boss_kirthonos_le_herault") {}
 
 struct boss_kirthonos_le_heraultAI : public ScriptedAI
 {
 boss_kirthonos_le_heraultAI(Creature *c): ScriptedAI(c) {}
 
 uint32 wing_flap;
 uint32 pierce_armor;
 uint32 swoop;
 uint32 disarm;
 
 uint32 kirthonos_transform;
 
 uint32 curse_of_thongue;
 uint32 dominate_mind;
 uint32 shadow_bolt_volley;
 
 bool Bat;
 bool Vampire;
 
 void Reset()
 { 
    wing_flap = 10000;
	pierce_armor = 15000;
	swoop = 5000;
	disarm = 8000;
	
	kirthonos_transform = 2000;
	
	curse_of_thongues = 5000;
	dominate_mind = 12000;
	shadow_bolt_volley = 10000;
	
	Bat = false;
	Vampire = false;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
        return;
	
	if (!Bat && !HealthAbovePct(100))
    {
	    if(wing_flap<= diff)
        {
            DoCast(me->getVictim(), spell_wing_flap);
            wing_flap = 10000;
        }else wing_flap -= diff;
		
		if(pierce_armor<= diff)
        {
            DoCast(me->getVictim(), spell_pierce_armor);
            pierce_armor = 15000;
        }else pierce_armor -= diff;
		
		if(swoop<= diff)
        {
            DoCast(me->getVictim(), spell_swoop);
            swoop = 8000;
        }else swoop -= diff;
		
		if(disarm<= diff)
        {
            DoCast(me->getVictim(), spell_disarm);
            disarm = 18000;
        }else disarm -= diff;
		
		Bat = true;
		Vampire = false;
		
	}
	
	if (!Vampire && !HealthAbovePct(50))
	{
	    if (!Vampire && kirthonos_transform <= diff)
		{
		    DoCast(me, spell_kirthonos_transform);
			kirthonos_transform = 3600000;
		}else kirthonos_transform -= diff;
		
		if(curse_of_tongues<= diff)
		{
		    DoCast(spell_curse_of_tongues);
			curse_of_tongues = 20000;
		}else curse_of_thongues -= diff;
		
		if(dominate_mind<= diff)
        {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                DoCast(pTarget, spell_dominate_mind);
                dominate_mind = 25000;
        } else dominate_mind -= diff;
		
		if(shadow_bolt_volley<= diff)
		{
		    DoCast(spell_shadow_bolt_volley);
			shadow_bolt_volley = 10000;
		}else shadow_bolt_volley -= diff;
		
		Vampire = true;
		Bat = false;
		
	}
	
	 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_kirthonos_le_heraultAI(pCreature);
 }
 
 };
 
void AddSC_boss_kirthonos_le_herault()
{
new boss_kirthonos_le_herault();()
}
 