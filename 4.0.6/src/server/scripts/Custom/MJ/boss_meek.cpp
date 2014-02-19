/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"

#define spell_fireball 72502 // Eclair de givre
#define spell_blizzard 28560 // Image Mirroir
#define spell_shock 66012 // Faire détoner mana
#define spell_heal 72110 // Bombe d'eau
#define spell_valkyr 88813 // Massacre
#define spell_berserk 47008 // Enrage

/*
-- Boss Meek display 34515
DELETE FROM creature_template WHERE entry=57102;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(57102, 0, 0, 0, 0, 0, 34515, 0, 0, 0, 'Meek', 'Serviteur du MJ Meek', NULL, 0, 88, 88, 1, 16, 16, 0, 1, 1.14286, 18, 1, 6950, 8520, 4, 22630, 4, 2000, 2000, 8, 32832, 8, 0, 0, 0, 0, 0, 6950, 8520, 22630, 6, 108, 57100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 669530, 12305599, '', 1, 3, 9.65232e+06, 9.65232e+06, 22000, 0, 0, 0, 0, 0, 0, 0, 164, 1, 56018, 617299803, 1, 'boss_smeek', 1);
-- Arme de Meek
DELETE FROM creature_equip_template WHERE entry=56018;
INSERT INTO creature_equip_template VALUE (56018, 65013, 65111, 0);
*/

#define SAY_AGGRO "Who are you ? What do you want ? Do not come near me !"
#define SAY_DIED "Finally, this nightmare is over ..."
#define SAY_SPELL "I am not defeated ! No, I still have a trick up my sleeve ..."

class boss_meek: public CreatureScript
{
public: 
 boss_meek() : CreatureScript("boss_meek") { } 

 struct boss_meekAI : public ScriptedAI
    {
        boss_meekAI(Creature *c) : ScriptedAI(c) {}

		uint32 shock;
        uint32 fireball;
        uint32 blizzard;
		uint32 heal;
        uint32 valkyr;
		uint32 Berserk_Timer;

        void Reset()
        {
           fireball = 15000;
           blizzard = 10000;
		   shock = 2000;
		   heal = 12000;
		   valkyr = 10000;
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
                fireball   = 15000; 
            }
            else
                fireball -= diff; 
           
            if (blizzard <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_blizzard);
                blizzard = 10000;
            }
            else
                blizzard -= diff;
			           
            if (shock<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_shock);
                shock   = 2000; 
            }
            else
                shock -= diff; 
						
			if (valkyr<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_valkyr);
                valkyr   = 10000; 
            }
            else
                valkyr -= diff; 

			 if (heal<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_heal);
				me->MonsterYell(SAY_SPELL, LANG_UNIVERSAL, NULL);
                heal   = 12000; 
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
        return new boss_meekAI (pCreature);
    }

};

void AddSC_boss_meek() 
{
    new boss_meek();
}