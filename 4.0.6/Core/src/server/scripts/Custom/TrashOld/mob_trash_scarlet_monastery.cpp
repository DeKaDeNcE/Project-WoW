/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By JeanClaude
*/

#include "ScriptPCH.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

/*****************
**Scarlet Torturer
******************/

#define spell_immolate 9275 // Immolate 

class mob_scarlet_torturer : public CreatureScript
{
public:
 mob_scarlet_torturer() : CreatureScript("mob_scarlet_torturer") {}
 
 struct mob_scarlet_torturerAI : public ScriptedAI
 {
 mob_scarlet_torturerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 immolate;
 
 void Reset()
 {
 immolate = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(immolate<= diff)
 {
    DoCast(me->getVictim(), spell_immolate);
	immolate = urand(5000, 8000);
 }else immolate -= diff;
 
  DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_torturerAI(pCreature);
 }
};

/***************
**Scarlet Scryer
****************/

#define spell_sleep 77773 // Sleep
#define spell_shadow_bolt 9613 // Shadow Bolt

class mob_scarlet_scryer : public CreatureScript
{
public:
 mob_scarlet_scryer() : CreatureScript("mob_scarlet_scryer") {}
 
 struct mob_scarlet_scryerAI : public ScriptedAI
 {
 mob_scarlet_scryerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 sleep;
 uint32 shadow_bolt;
 
 void Reset()
 {
 sleep = urand(6000, 10000);
 shadow_bolt = urand(4000, 6000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(sleep<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_sleep);
       sleep = urand(6000, 10000);
 } else sleep -= diff;
 
 if(shadow_bolt<= diff)
 {
    DoCast(me->getVictim(), spell_shadow_bolt);
	shadow_bolt = urand(4000, 6000);
 }else shadow_bolt -= diff;
 
   DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_scryerAI(pCreature);
 }
};

/***************
**Anguished Dead
****************/

#define spell_veil_of_shadow 7068 // Veil of Shadow

class mob_anguished_dead : public CreatureScript
{
public:
 mob_anguished_dead() : CreatureScript("mob_anguished_dead") {}
 
 struct mob_anguished_deadAI : public ScriptedAI
 {
 mob_anguished_deadAI(Creature *c): ScriptedAI(c) {}
 
 uint32 veil_of_shadow;
 
 void Reset()
 {
 veil_of_shadow = urand(8000, 13000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(veil_of_shadow<= diff)
 {
    DoCast(me->getVictim(), spell_veil_of_shadow);
	veil_of_shadow = urand(8000, 13000);
 }else veil_of_shadow -= diff;
 
   DoMeleeAttackIfReady();
 }
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_anguished_deadAI(pCreature);
 }
};

/******************
**Haunting Phantasm
*******************/

#define spell_summon_illusionary_phantasm 8986 // Summon Illusionary Phantasm

class mob_haunting_phantasm : public CreatureScript
{
public:
 mob_haunting_phantasm() : CreatureScript("mob_haunting_phantasm") {}
 
 struct mob_haunting_phantasmAI : public ScriptedAI
 {
 mob_haunting_phantasmAI(Creature *c): ScriptedAI(c) {}
 
 uint32 summon_illusionary_phantasm;
 
 void Reset()
 {
 summon_illusionary_phantasm = urand(15000, 20000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(summon_illusionary_phantasm<= diff)
 {
    DoCast(spell_summon_illusionary_phantasm);
	summon_illusionary_phantasm = urand(15000, 20000);
 }else summon_illusionary_phantasm -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_haunting_phantasmAI(pCreature);
 }
 
 };

/**************
**Scarlet Adept
***************/

#define spell_heal 11642
#define spell_holy_smite 20820

class mob_scarlet_adept : public CreatureScript
{
public:
 mob_scarlet_adept() : CreatureScript("mob_scarlet_adept") {}
 
 struct mob_scarlet_adeptAI : public ScriptedAI
 {
 mob_scarlet_adeptAI(Creature *c): ScriptedAI(c) {}
 
 uint32 heal;
 uint32 holy_smite;
 
 void Reset()
 {
 heal = 10000;
 holy_smite = urand(4000, 6000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (heal <= diff)
 {
    DoCast(me, spell_heal);
    heal = 10000;
 } else heal -= diff;
 
 if (holy_smite <= diff)
 {
    DoCast(me->getVictim(), spell_holy_smite);
	holy_smite = urand(4000, 6000);
 }else holy_smite -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_adeptAI(pCreature);
 }
 
 };
 
/********************
**Scarlet BeastMaster
*********************/

#define spell_exploding_shot 7896
#define spell_shoot 6660

class mob_scarlet_beastmaster : public CreatureScript
{
public:
 mob_scarlet_beastmaster() : CreatureScript("mob_scarlet_beastmaster") {}
 
 struct mob_scarlet_beastmasterAI : public ScriptedAI
 {
 mob_scarlet_beastmasterAI(Creature *c): ScriptedAI(c) {}
 
 uint32 exploding_shot;
 uint32 shoot;
 
 void Reset()
 {
 exploding_shot = 10000;
 shoot = 2000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (exploding_shot <= diff)
 {
   DoCast(me->getVictim(), spell_exploding_shot);
   exploding_shot = 10000;
 }else exploding_shot -= diff;
 
 if (shoot <= diff)
 {
   DoCast(me->getVictim(), spell_shoot);
   shoot = 2000;
 }else shoot -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_beastmasterAI(pCreature);
 }
 
 };
 
/****************
**Scarlet Gallant
*****************/

#define spell_crusader_strike 14517
#define spell_hammer_of_justice 77787

class mob_scarlet_gallant : public CreatureScript
{
public:
 mob_scarlet_gallant() : CreatureScript("mob_scarlet_gallant") {}
 
 struct mob_scarlet_gallantAI : public ScriptedAI
 {
 mob_scarlet_gallantAI(Creature *c): ScriptedAI(c) {}
 
 uint32 crusader_strike;
 uint32 hammer_of_justice;
 
 void Reset()
 {
 crusader_strike = urand(5000, 10000);
 hammer_of_justice = 12000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(crusader_strike<= diff)
 {
  DoCast(me->getVictim(), spell_crusader_strike);
  crusader_strike = urand(5000, 10000);
 }else crusader_strike -= diff;
 
 if(hammer_of_justice<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_hammer_of_justice);
       hammer_of_justice = 12000;
 } else hammer_of_justice -= diff;

DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_gallantAI(pCreature);
 }
 
 }; 
 
/*****************
**Scarlet Chaplain
******************/

#define spell_power_word_shield 22187
#define spell_renew 25058

class mob_scarlet_chaplain : public CreatureScript
{
public:
 mob_scarlet_chaplain() : CreatureScript("mob_scarlet_chaplain") {}
 
 struct mob_scarlet_chaplainAI : public ScriptedAI
 {
 mob_scarlet_chaplainAI(Creature *c): ScriptedAI(c) {}
 
 uint32 power_word_shield;
 uint32 renew;
 
 void Reset()
 {
 power_word_shield = 10000;
 renew = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if (power_word_shield <= diff)
 {
    DoCast(me, spell_power_word_shield);
    power_word_shield = 10000;
 } else power_word_shield -= diff;
 
  if (renew <= diff)
 {
    DoCast(me, spell_renew);
    renew = urand(5000, 8000);
 } else renew -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_chaplainAI(pCreature);
 }
 
 };
 
/****************
**Scarlet Diviner
*****************/

#define spell_fireball 20815
#define spell_mana_burn 11981

class mob_scarlet_diviner : public CreatureScript
{
public:
 mob_scarlet_diviner() : CreatureScript("mob_scarlet_diviner") {}
 
 struct mob_scarlet_divinerAI : public ScriptedAI
 {
 mob_scarlet_divinerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fireball;
 uint32 mana_burn;
 
 void Reset()
 {
 fireball = urand(6000, 10000);
 mana_burn = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(fireball<= diff)
 {
  DoCast(me->getVictim(), spell_fireball);
  fireball = urand(6000, 10000);
 }else fireball -= diff;
 
 if (mana_burn<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_mana_burn);
 mana_burn = urand(5000, 8000);
 } else mana_burn -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_divinerAI(pCreature);
 }
 
 };
 
/*************
**Scarlet Monk
**************/

#define spell_kick 76583
#define spell_thrash 3391

class mob_scarlet_monk : public CreatureScript
{
public:
 mob_scarlet_monk() : CreatureScript("mob_scarlet_monk") {}
 
 struct mob_scarlet_monkAI : public ScriptedAI
 {
 mob_scarlet_monkAI(Creature *c): ScriptedAI(c) {}
 
 uint32 kick;
 uint32 thrash;
 
 void Reset()
 {
 kick = 6000;
 thrash = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(kick<= diff)
 {
  DoCast(me->getVictim(), spell_kick);
  kick = 6000;
 }else kick -= diff;
 
 if(thrash<= diff)
 {
 DoCast(me, spell_thrash);
 thrash = urand(8000, 10000);
 }else thrash -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_monkAI(pCreature);
 }
 
 };
 
/*****************
**Scarlet Conjuror
******************/

#define spell_fireball 20823
#define spell_summon_fire_elemental 8985

class mob_scarlet_conjuror : public CreatureScript
{
public:
 mob_scarlet_conjuror() : CreatureScript("mob_scarlet_conjuror") {}
 
 struct mob_scarlet_conjurorAI : public ScriptedAI
 {
 mob_scarlet_conjurorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fireball;
 uint32 summon_fire_elemental;
 
 void Reset()
 {
 fireball = urand(4000, 6000);
 summon_fire_elemental = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(fireball<= diff)
 {
  DoCast(me->getVictim(), spell_fireball);
  fireball = urand(4000, 6000);
 }else fireball -= diff;
 
 if(summon_fire_elemental<= diff)
 {
   DoCast(spell_summon_fire_elemental);
   summon_fire_elemental = 15000;
 }else summon_fire_elemental -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_conjurorAI(pCreature);
 }
 
 };
 
/****************
**Scarlet Soldier
*****************/

#define spell_improved_blocking 3639

class mob_scarlet_soldier : public CreatureScript
{
public:
 mob_scarlet_soldier() : CreatureScript("mob_scarlet_soldier") {}
 
 struct mob_scarlet_soldierAI : public ScriptedAI
 {
 mob_scarlet_soldierAI(Creature *c): ScriptedAI(c) {}
 
 uint32 improved_blocking;

 void Reset()
 {
 improved_blocking = urand(8000, 10000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(improved_blocking<= diff)
 {
    DoCast(me, spell_improved_blocking);
	improved_blocking = urand(8000, 10000);
 }else improved_blocking -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_soldierAI(pCreature);
 }
 
 };

/***************
**Scarlet Evoker
****************/

#define spell_fire_shield 18968
#define spell_fireball 20815
#define spell_flamestrike 20296

class mob_scarlet_evoker : public CreatureScript
{
public:
 mob_scarlet_evoker() : CreatureScript("mob_scarlet_evoker") {}
 
 struct mob_scarlet_evokerAI : public ScriptedAI
 {
 mob_scarlet_evokerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fire_shield;
 uint32 fireball;
 uint32 flamestrike;
 
 void Reset()
 {
 fire_shield = 10000;
 fireball = urand(5000, 8000);
 flamestrike = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (fire_shield <= diff)
 {
    DoCast(me, spell_fire_shield);
    fire_shield = 10000;
 } else fire_shield -= diff;
 
 if(fireball<= diff)
 {
  DoCast(me->getVictim(), spell_fireball);
  fireball = urand(5000, 8000);
 }else fireball -= diff;
 
 if (flamestrike<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_flamestrike);
 flamestrike = 15000;
} else flamestrike -= diff;

 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_evokerAI(pCreature);
 }
 
 };
 
/******************
**Scarlet Guardsman
*******************/

#define spell_disarm 6713

class mob_scarlet_guardsman : public CreatureScript
{
public:
 mob_scarlet_guardsman() : CreatureScript("mob_scarlet_guardsman") {}
 
 struct mob_scarlet_guardsmanAI : public ScriptedAI
 {
 mob_scarlet_guardsmanAI(Creature *c): ScriptedAI(c) {}
 
 uint32 disarm;

 void Reset()
 {
 disarm = urand(7000, 10000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(disarm<= diff)
 {
  DoCast(me->getVictim(), spell_disarm);
  disarm = urand(7000, 10000);
 }else disarm -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_guardsmanAI(pCreature);
 }
 
 };
 
/******************
**Scarlet Protector
*******************/

#define spell_devotion_aura 8258
#define spell_holy_light 31713

class mob_scarlet_protector : public CreatureScript
{
public:
 mob_scarlet_protector() : CreatureScript("mob_scarlet_protector") {}
 
 struct mob_scarlet_protectorAI : public ScriptedAI
 {
 mob_scarlet_protectorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 devotion_aura;
 uint32 holy_light;
 
 void Reset()
 {
 devotion_aura = 8000;
 holy_light = urand(6000, 10000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(devotion_aura<= diff)
 {
    DoCast(me, spell_devotion_aura);
	devotion_aura = 8000;
 }else devotion_aura -= diff;
 
 if (holy_light <= diff)
 {
    DoCast(me, spell_holy_light);
    holy_light = urand(6000, 10000);
 } else holy_light -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_protectorAI(pCreature);
 }
 
 };
 
/*****************
**Scarlet Defender
******************/

#define spell_improved_blocking 3639
#define spell_shield_bash 11972

class mob_scarlet_defender : public CreatureScript
{
public:
 mob_scarlet_defender() : CreatureScript("mob_scarlet_defender") {}
 
 struct mob_scarlet_defenderAI : public ScriptedAI
 {
 mob_scarlet_defenderAI(Creature *c): ScriptedAI(c) {}
 
 uint32 improved_blocking;
 uint32 shield_bash;
 
 void Reset()
 {
 improved_blocking = 8000;
 shield_bash = urand(5000, 9000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (improved_blocking<= diff)
 {
    DoCast(me, spell_improved_blocking);
	improved_blocking = 8000;
 }else improved_blocking -= diff;
 
 if(shield_bash<= diff)
 {
  DoCast(me->getVictim(), spell_shield_bash);
  shield_bash = urand(5000, 9000);
 }else shield_bash -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_defenderAI(pCreature);
 }
 
 };
 
/*****************
**Scarlet Myrmidon
******************/

#define spell_frenzy 8269

class mob_scarlet_myrmidon : public CreatureScript
{
public:
 mob_scarlet_myrmidon() : CreatureScript("mob_scarlet_myrmidon") {}
 
 struct mob_scarlet_myrmidonAI : public ScriptedAI
 {
 mob_scarlet_myrmidonAI(Creature *c): ScriptedAI(c) {}
 
 uint32 frenzy;

 void Reset()
 {
 frenzy = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(frenzy<= diff)
 {
    DoCast(me, spell_frenzy);
	frenzy = 15000;
 }else frenzy -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_myrmidonAI(pCreature);
 }
 
 };
 
/*****************
**Scarlet Sorcerer
******************/

#define spell_blizzard 8364
#define spell_frostbolt 20819
#define spell_slow 6146

class mob_scarlet_sorcerer : public CreatureScript
{
public:
 mob_scarlet_sorcerer() : CreatureScript("mob_scarlet_sorcerer") {}
 
 struct mob_scarlet_sorcererAI : public ScriptedAI
 {
 mob_scarlet_sorcererAI(Creature *c): ScriptedAI(c) {}
 
 uint32 blizzard;
 uint32 frostbolt;
 uint32 slow;
 
 void Reset()
 {
 blizzard = 10000;
 frostbolt = urand(5000, 8000);
 slow = urand(8000, 12000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (blizzard<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_blizzard);
 blizzard = 10000;
 } else blizzard -= diff;
 
 if(frostbolt<= diff)
 {
  DoCast(me->getVictim(), spell_frostbolt);
  frostbolt = urand(5000, 8000);
 }else frostbolt -= diff;
 
 if (slow<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_slow);
 slow = urand(8000, 12000);
 } else slow -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_sorcererAI(pCreature);
 }
 
 };
 
/******************
**Scarlet Centurion
*******************/

#define spell_battle_shout 31403

class mob_scarlet_centurion : public CreatureScript
{
public:
 mob_scarlet_centurion() : CreatureScript("mob_scarlet_centurion") {}
 
 struct mob_scarlet_centurionAI : public ScriptedAI
 {
 mob_scarlet_centurionAI(Creature *c): ScriptedAI(c) {}
 
 uint32 battle_shout;

 void Reset()
 {
 battle_shout = 6000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(battle_shout<= diff)
 {
    DoCast(spell_battle_shout);
	battle_shout = 6000;
 }else battle_shout -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_centurionAI(pCreature);
 }
 
 };
 
/***************
**Scarlet Wizard
****************/

#define spell_arcane_explosion 34517
#define spell_fire_shield 32749

class mob_scarlet_wizard : public CreatureScript
{
public:
 mob_scarlet_wizard() : CreatureScript("mob_scarlet_wizard") {}
 
 struct mob_scarlet_wizardAI : public ScriptedAI
 {
 mob_scarlet_wizardAI(Creature *c): ScriptedAI(c) {}
 
 uint32 arcane_explosion;
 uint32 fire_shield;
 
 void Reset()
 {
 arcane_explosion = 8000;
 fire_shield = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(arcane_explosion<= diff)
 {
    DoCast(me, spell_arcane_explosion);
	arcane_explosion = 8000;
 }else arcane_explosion -= diff;
 
 if(fire_shield<= diff)
 {
    DoCast(me, spell_fire_shield);
	fire_shield = 10000;
 }else fire_shield -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_wizardAI(pCreature);
 }
 
 };
 
/**************
**Scarlet Abbot
***************/

#define spell_heal 12039
#define spell_renew 8362

class mob_scarlet_abbot : public CreatureScript
{
public:
 mob_scarlet_abbot() : CreatureScript("mob_scarlet_abbot") {}
 
 struct mob_scarlet_abbotAI : public ScriptedAI
 {
 mob_scarlet_abbotAI(Creature *c): ScriptedAI(c) {}
 
 uint32 heal;
 uint32 renew;
 
 void Reset()
 {
 heal = 8000;
 renew = urand(5000, 9000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (heal <= diff)
 {
    DoCast(me, spell_heal);
    heal = 8000;
 } else heal -= diff;
 
 if (renew <= diff)
 {
    DoCast(me, spell_renew);
    renew = urand(5000, 9000);
 } else renew -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_abbotAI(pCreature);
 }
 
 };
 
/*****************
**Scarlet Champion
******************/

#define spell_holy_strike 17143

class mob_scarlet_champion : public CreatureScript
{
public:
 mob_scarlet_champion() : CreatureScript("mob_scarlet_champion") {}
 
 struct mob_scarlet_championAI : public ScriptedAI
 {
 mob_scarlet_championAI(Creature *c): ScriptedAI(c) {}
 
 uint32 holy_strike;

 void Reset()
 {
 holy_strike = 6000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(holy_strike<= diff)
 {
    DoCast(me, spell_holy_strike);
	holy_strike = 6000;
 }else holy_strike -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scarlet_championAI(pCreature);
 }
 
 };
 
void AddSC_mob_trash_scarlet_monastery()
{
  new mob_scarlet_torturer();
  new mob_scarlet_scryer();
  new mob_anguished_dead();
  new mob_haunting_phantasm();
  new mob_scarlet_adept();
  new mob_scarlet_beastmaster();
  new mob_scarlet_gallant();
  new mob_scarlet_chaplain();
  new mob_scarlet_diviner();
  new mob_scarlet_monk();
  new mob_scarlet_conjuror();
  new mob_scarlet_soldier();
  new mob_scarlet_evoker();
  new mob_scarlet_guardsman();
  new mob_scarlet_protector();
  new mob_scarlet_defender();
  new mob_scarlet_myrmidon();
  new mob_scarlet_sorcerer();
  new mob_scarlet_centurion();
  new mob_scarlet_wizard();
  new mob_scarlet_abbot();
  new mob_scarlet_champion();
}