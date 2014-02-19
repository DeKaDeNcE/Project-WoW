/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"

#define spell_fireball 62859 // Tremblement de terre
#define spell_blizzard 92944 // Flamme de Valiona
#define spell_shock 74367 // Fracas Armure
#define spell_heal 71052 // Aura de givre
#define spell_valkyr 74384 // Fear
#define spell_berserk 47008 // Enrage
#define spell_tour 91501

#define SAY_AGGRO "A sacrifice for you, Master."
#define SAY_DIED "They will be countless falling for my death. This weight is on your shoulders."
#define SAY_SPELL "BURN !!!"

class boss_asardial: public CreatureScript
{
public: 
 boss_asardial() : CreatureScript("boss_asardial") { } 

 struct boss_asardialAI : public ScriptedAI
    {
        boss_asardialAI(Creature *c) : ScriptedAI(c) {}

		uint32 shock;
        uint32 fireball;
        uint32 blizzard;
		uint32 heal;
        uint32 valkyr;
        uint32 tour;
		uint32 Berserk_Timer;

        void Reset()
        {
           fireball = 30000;
           blizzard = 48000;
		   shock = 12000;
		   heal = 3000;
		   valkyr = 25000;
		   tour = 15000;
		   Berserk_Timer = 360000; //6 minutes
           
        }

        void EnterCombat(Unit* /*who*/) 
        {
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
        }

        void JustDied(Unit* /*killer*/)
        {
			me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
			
			if (IsHeroic()) {
			    me->SummonGameObject(211112, 4247.42f, -4239.8f, 131.801f, 6.22832f,0,0,0,0,0);
			} else {
			    me->SummonGameObject(211110, 4247.42f, -4239.8f, 131.801f, 6.22832f,0,0,0,0,0);
			}
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (fireball<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_fireball);
                fireball   = 30000; 
            }
            else
                fireball -= diff; 
           
            if (blizzard <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_blizzard);
				me->MonsterYell(SAY_SPELL, LANG_UNIVERSAL, NULL);
                blizzard = 48000;
            }
            else
                blizzard -= diff;
			           
            if (shock<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_shock);
                shock   = 12000; 
            }
            else
                shock -= diff; 
						
			if (valkyr<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_valkyr);
                valkyr   = 25000; 
            }
            else
                valkyr -= diff; 

			if (tour<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_tour);
                tour   = 15000; 
            }
            else
                tour -= diff;

			 if (heal<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_heal);
                heal   = 3000; 
            }
            else
                heal -= diff; 

			                if (!UpdateVictim())
                    return;
					
			if (Berserk_Timer <= diff)
            {
                DoCast(me->getVictim(), spell_berserk, true);

                Berserk_Timer = 360000;
            } else Berserk_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_asardialAI (pCreature);
    }

};

void AddSC_boss_asardial() 
{
    new boss_asardial();
}