/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"

#define spell_buff 687 // Armure démoniaque
#define spell_shield 90762 // Voile du Ciel
#define spell_dot 71937 // Corruption
#define spell_ombre 90915 // Trait d'Ombre
#define spell_fear 74384 // Fear
#define spell_meteor 90023 // Météor
#define spell_flamme 78621 // Ombreflamme
#define spell_stopcast 62859 // StopCast
#define spell_berserk 47008 // Enrage 7min

#define SAY_AGGRO "Annihilate...."
#define SAY_DIED "Impossible...."
#define SAY_SPELL "CHAOS!!!"
#define SAY_STOP "Silence..."
#define SAY_SHIELD "FEEL THE POWER!"

class boss_zethos: public CreatureScript
{
public: 
 boss_zethos() : CreatureScript("boss_zethos") { } 

 struct boss_zethosAI : public ScriptedAI
    {
        boss_zethosAI(Creature *c) : ScriptedAI(c) {}

		uint32 ombre;
		uint32 shield;
        uint32 dot;
		uint32 fear;
        uint32 meteor;
        uint32 flamme;
		uint32 silence;
		uint32 Berserk_Timer;

        void Reset()
        {
		   shield = 5000;
           dot = 6000;
		   ombre = 2000;
		   fear = 20000;
		   meteor = 15000;
		   flamme = 12000;
		   silence = 40000;
		   Berserk_Timer = 420000; //7 minutes
           
        }

        void EnterCombat(Unit* /*who*/) 
        {
			me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
            DoCast(me, spell_buff);
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
		
            if (shield<= diff)
            {
                DoCast(me, spell_shield);
				me->MonsterYell(SAY_SHIELD, LANG_UNIVERSAL, NULL);
                shield   = 5000; 
            }
            else
                shield -= diff; 
           
            if (dot <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_dot);
                dot = 6000;
            }
            else
                dot -= diff;
			           
            if (ombre<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_ombre);
                ombre   = 2000; 
            }
            else
                ombre -= diff; 
						
			if (meteor<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_meteor);
				me->MonsterYell(SAY_SPELL, LANG_UNIVERSAL, NULL);
                meteor   = 15000; 
            }
            else
                meteor -= diff; 

			if (flamme<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_flamme);
				flamme   = 12000; 
            }
            else
                flamme -= diff;
				
			if (silence<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_stopcast);
				me->MonsterYell(SAY_STOP, LANG_UNIVERSAL, NULL);
				silence   = 10000; 
            }
            else
                silence -= diff;

			 if (fear<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_fear);
                fear   = 20000; 
            }
            else
                fear -= diff; 
					
			if (Berserk_Timer <= diff)
            {
                DoCast(me->getVictim(), spell_berserk, true);

                Berserk_Timer = 420000;
            } else Berserk_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_zethosAI (pCreature);
    }

};

void AddSC_boss_zethos() 
{
    new boss_zethos();
}