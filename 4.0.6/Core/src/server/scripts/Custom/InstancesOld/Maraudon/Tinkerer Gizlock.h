/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/*****************
**Tinkerer Gizlock
******************/

#define spell_bomb 9143
#define spell_flash_bomb 29419
#define spell_goblin_dragon_gun 21833
#define spell_shoot 16100

#define SAY_AGGRO "Mine! Mine! Mine! Gizlock is the ruler of this domain! You shall never reveal my presence!"

class boss_tinkerer_gizlock : public CreatureScript
{
public:
 boss_tinkerer_gizlock() : CreatureScript("boss_tinkerer_gizlock") {}
 
 struct boss_tinkerer_gizlockAI : public ScriptedAI
 {
 boss_tinkerer_gizlockAI(Creature *c): ScriptedAI(c) {}
 
 uint32 bomb;
 uint32 goblin_dragon_gun;
 uint32 shoot;
 
 void EnterCombat(Unit * /*who*/)
 {
    DoScriptText(SAY_AGGRO, me);
 }
 
 void Reset()
 {
    bomb = 15000;
	goblin_dragon_gun = 8000;
	shoot = 5000;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if (bomb<= diff)
    {
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
        DoCast(pTarget, RAND(spell_bomb, spell_flash_bomb));
        bomb = 15000;
    } else bomb -= diff;
	
	if (goblin_dragon_gun<= diff)
    {
        DoCast(me->getVictim(), spell_goblin_dragon_gun);
        goblin_dragon_gun = 8000 + rand()%10000;
    } else goblin_dragon_gun -= diff;
	
	if (shoot <= diff)
    {
        Unit *pTarget = NULL;
        pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
        if (pTarget)
        DoCast(pTarget, spell_shoot);
        shoot = 5000;
    } else shoot -= diff;
	
		DoMeleeAttackIfReady();
    }
    };
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_tinkerer_gizlockAI(pCreature);
 }

 };

void AddSC_boss_tinkerer_gizlock()
{
    new boss_tinkerer_gizlock();
}