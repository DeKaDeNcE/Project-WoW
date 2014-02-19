/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Nizza
*/

#include "ScriptPCH.h"

#define spell_twilight_blast 89280 // Twilight blast
#define spell_remedy 77912 // Remedy
#define spell_shadowflame_breath 77826 // Shadowflame Breath
#define spell_bone_spike_graveyard 690547 // empaler
#define spell_ground_slam 92410 // Ground Slam
#define spell_berserker 47008 // enrage

/*
-- Boss Nizza display 19372
*/

#define SAY_AGGRO "If u want , try to kill me !"
#define SAY_DIED "Oh... NOOOOOOO !"
#define SAY_SPELL "Take This !"

class boss_nizza: public CreatureScript
{
public:
 boss_nizza() : CreatureScript("boss_nizza") {}
 
struct boss_nizzaAI : public ScriptedAI
{
        boss_nizzaAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 twilight_blast;
		uint32 remedy;
		uint32 shadowflame_breath;
		uint32 bone_spike_graveyard;
		uint32 ground_slam;
		uint32 berserker;
		
		void Reset()
		{
		        twilight_blast = 15000;
				remedy = 30000;
				shadowflame_breath = 10000;
				ground_slam = 20000;
				bone_spike_graveyard = 25000;
				berserker = 360000; 
		}
		
		void EnterCOmbat(Unit* /*who*/)
		{
		        me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
		}
		
		void JustDied(Unit* /*killer*/)
		{
		        me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (twilight_blast<= diff)
				{
				        DoCast(me->getVictim(), spell_twilight_blast);
						twilight_blast = 15000;
				} else twilight_blast -= diff;
				
				if (remedy<= diff)
				{
				        DoCast(me, spell_remedy);
						remedy = 30000;
				} else remedy -= diff;
				
				if (shadowflame_breath<= diff)
				{
				        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
						DoCast(pTarget, spell_shadowflame_breath);
						shadowflame_breath = 10000;
				} else shadowflame_breath -= diff;
				
				if (ground_slam<= diff)
				{
				        DoCast(me->getVictim(), spell_ground_slam);
						ground_slam = 20000;
				} else ground_slam -= diff;
				
				if (bone_spike_graveyard<= diff)
				{
				        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
						DoCast(pTarget, spell_bone_spike_graveyard);
						bone_spike_graveyard = 25000;
				} else bone_spike_graveyard -= diff;
				
				if (berserker<= diff)
				{
				        DoCast(me->getVictim(), spell_berserker, true);
						berserker = 360000;
				} else berserker -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new boss_nizzaAI(pCreature);
		}
};

void AddSC_boss_nizza()
{
    new boss_nizza();
}