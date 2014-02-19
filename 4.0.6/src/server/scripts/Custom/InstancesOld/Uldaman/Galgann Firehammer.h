/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By JeanClaude
*/

#include "ScriptPCH.h"
#include "uldaman.h"

/*******************
**Galgann Firehammer
********************/

#define spell_amplify_flames 9482
#define spell_fire_nova 11969
#define spell_flame_lash 3356

#define SAY_AGGRO "By Thaurissan's beard! Slay them!"

class boss_galgann_firehammer : public CreatureScript
{
public:
 boss_galgann_firehammer() : CreatureScript("boss_galgann_firehammer") {}
 
 struct boss_galgann_firehammerAI : public ScriptedAI
 {
 boss_galgann_firehammerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 amplify_flames;
 uint32 fire_nova;
 uint32 flame_lash;
 
 void EnterCombat(Unit * /*who*/)
 {
    DoScriptText(SAY_AGGRO, me);
 }

 void Reset()
 {
   amplify_flames = 10000;
   fire_nova = 15000;
   flame_lash = 8000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (amplify_flames<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 5.0f, true))
 DoCast(target, spell_amplify_flames);
 amplify_flames = 10000;
 } else amplify_flames -= diff;
 
 if(fire_nova<= diff)
 {
    DoCast(spell_fire_nova);
	fire_nova = 15000;
 }else fire_nova -= diff;
 
 if(flame_lash<= diff)
 {
  DoCast(me->getVictim(), spell_flame_lash);
  flame_lash = 8000;
 }else flame_lash -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_galgann_firehammerAI(pCreature);
 }
 
 };
 
 void AddSC_galgann_firehammer()
{
    new boss_galgann_firehammer();
}

 
 