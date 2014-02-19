/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"

/*******************
**Charlga Razorflank
********************/

#define spell_chain_bolt 8292
#define spell_mana_spike 8358
#define spell_purity 8361
#define spell_renew 25058

#define SAY_AGGRO "You outsiders will pay for encroaching on our land!"
#define SAY_KILL "Who's next?"
#define SAY_DEAD "Our new allies will avenge us!"
#define SAY_MANA "Bah! My power rules here!"

class boss_charlga_razorflank : public CreatureScript
{
public:
 boss_charlga_razorflank() : CreatureScript("boss_charlga_razorflank") {}
 
 struct boss_charlga_razorflankAI : public ScriptedAI
 {
 boss_charlga_razorflankAI(Creature *c): ScriptedAI(c) {}
 
 uint32 chain_bolt;
 uint32 renew;
 
 bool Manaspike;
 
 void EnterCombat(Unit * /*who*/)
 {
    me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
 }
 
 void KilledUnit(Unit* /*Victim*/)
 {
    me->MonsterYell(SAY_KILL, LANG_UNIVERSAL, NULL);
 }
 
 void JustDied(Unit* /*Killer*/)
 {
    me->MonsterYell(SAY_DEAD, LANG_UNIVERSAL, NULL);
 }
 
 void Reset()
 {
    chain_bolt = 5000;
	renew = 8000;
    Manaspike = false;
 }
 
 void UpdateAI(const uint32 diff)
 {
    if (!UpdateVictim())
    return;
	
	if (chain_bolt<= diff)
       {
            DoCast(me->getVictim(), spell_chain_bolt);
            chain_bolt = 5000 + rand()%10000;
       } else chain_bolt -= diff;
	   
	if (!HealthAbovePct(50) && !me->IsNonMeleeSpellCasted(false) && renew <= diff)
       {
            DoCast(me, spell_renew);
            renew = 8000;
       } else renew -= diff;
	   
	if (!Manaspike && !HealthAbovePct(25))
       {
            me->MonsterYell(SAY_MANA, LANG_UNIVERSAL, NULL);
		    DoCast(me, spell_mana_spike);
            DoCast(me, spell_purity);
		    Manaspike = true;
       }
	   
	DoMeleeAttackIfReady();
    }
};

 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new boss_charlga_razorflankAI(pCreature);
 }

};

void AddSC_boss_charlga_razorflank()
{
    new boss_charlga_razorflank();
}