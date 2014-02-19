/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By JeanClaude
*/

#include "ScriptPCH.h"
#include "uldaman.h"

/******************
**Obsidian Sentinel
*******************/

#define spell_frost_fever 55095
#define spell_obsidian_reflection 9941
#define spell_splintered_obsidian 10072
#define spell_summon_obsidian_shard 10061

class boss_obsidian_sentinel : public CreatureScript
{
public:
 boss_obsidian_sentinel() : CreatureScript("boss_obsidian_sentinel") {}
 
 struct boss_obsidian_sentinelAI : public ScriptedAI
 {
 boss_obsidian_sentinelAI(Creature *c): ScriptedAI(c) {}
 
 uint32 frost_fever;
 uint32 obsidian_reflection;
 uint32 summon_obsidian_shard;
 
 bool splintered;
 
 void Reset()
 {
    frost_fever = 5000;
	obsidian_reflection = 15000;
	summon_obsidian_shard = 20000;
	
	splintered = false;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(frost_fever<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_frost_fever);
       frost_fever = 5000 + rand()%20000;
 } else frost_fever -= diff;
 
 if(obsidian_reflection <= diff)
 {
    DoCast(me, spell_obsidian_reflection);
	obsidian_reflection = 15000;
 }else obsidian_reflection -= diff;
 
 if(summon_obsidian_shard <= diff)
 {
    DoCast(spell_summon_obsidian_shard);
	summon_obsidian_shard = 20000;
 }else summon_obsidian_shard -= diff;
 
 if (!splintered && !HealthAbovePct(20))
 {
    DoCast(me, spell_splintered_obsidian);
	splintered = true;
 }
	
	DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_obsidian_sentinelAI(pCreature);
 }

};
void AddSC_obsidian_sentinel()
{
   new boss_obsidian_sentinel();
}