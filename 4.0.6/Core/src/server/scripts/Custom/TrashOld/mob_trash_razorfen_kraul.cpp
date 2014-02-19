/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */

#include "ScriptPCH.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

/********
**Agam'ar
*********/

#define spell_rushing_charge 6268

class mob_agamar : public CreatureScript
{
public:
 mob_agamar() : CreatureScript("mob_agamar") {}
 
 struct mob_agamarAI : public ScriptedAI
 {
 mob_agamarAI(Creature *c): ScriptedAI(c) {}
 
 uint32 rushing_charge;
 
 void Reset()
 {
 rushing_charge = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (rushing_charge<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_rushing_charge);
 rushing_charge = urand(5000, 8000);
 } else rushing_charge -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_agamarAI(pCreature);
 }
 
 };
 
/********************
**Death's Head Priest
*********************/

#define spell_heal 12039
#define spell_power_word_fortitude 13864
#define spell_shadow_bolt 20825

class mob_death_head_priest : public CreatureScript
{
public:
 mob_death_head_priest() : CreatureScript("mob_death_head_priest") {}
 
 struct mob_death_head_priestAI : public ScriptedAI
 {
 mob_death_head_priestAI(Creature *c): ScriptedAI(c) {}
 
 uint32 heal;
 uint32 shadow_bolt;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_power_word_fortitude);
 }
 
 void Reset()
 {
 heal = 10000;
 shadow_bolt = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(heal<= diff)
 {
    DoCast(me, spell_heal);
	heal = 10000;
 }else heal -= diff;
 
  if(shadow_bolt<= diff)
 {
  DoCast(me->getVictim(), spell_shadow_bolt);
  shadow_bolt = urand(5000, 8000);
 }else shadow_bolt -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_death_head_priestAI(pCreature);
 }
 
 };
 
/***************
**Raging Agam'ar
****************/

#define spell_frenzy 8269

class mob_raging_agamar : public CreatureScript
{
public:
 mob_raging_agamar() : CreatureScript("mob_raging_agamar") {}
 
 struct mob_raging_agamarAI : public ScriptedAI
 {
 mob_raging_agamarAI(Creature *c): ScriptedAI(c) {}
 
 uint32 frenzy;

 void Reset()
 {
 frenzy = urand(8000, 10000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(frenzy<= diff)
 {
    DoCast(me, spell_frenzy);
	frenzy = urand(8000, 10000);
 }else frenzy -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_raging_agamarAI(pCreature);
 }
 
 };
 
/*******************
**Razorfen Geomancer
********************/

#define spell_lightning_bolt 20824
#define spell_summon_earth_rumbler 8270

class mob_razorfen_geomancer : public CreatureScript
{
public:
 mob_razorfen_geomancer() : CreatureScript("mob_razorfen_geomancer") {}
 
 struct mob_razorfen_geomancerAI : public ScriptedAI
 {
 mob_razorfen_geomancerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 lightning_bolt;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(spell_summon_earth_rumbler);
 }
 
 void Reset()
 {
 lightning_bolt = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(lightning_bolt<= diff)
 {
  DoCast(me->getVictim(), spell_lightning_bolt);
  lightning_bolt = urand(5000, 8000);
 }else lightning_bolt -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_geomancerAI(pCreature);
 }
 
 };
 
/*****************
**Razorfen Handler
******************/

#define spell_shoot 6660
#define spell_summon_tamed_battleboar 8274

class mob_razorfen_handler : public CreatureScript
{
public:
 mob_razorfen_handler() : CreatureScript("mob_razorfen_handler") {}
 
 struct mob_razorfen_handlerAI : public ScriptedAI
 {
 mob_razorfen_handlerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shoot;
 
  void EnterCombat(Unit* pWho)
 {
   DoCast(spell_summon_tamed_battleboar);
 }   
 
 void Reset()
 {
 shoot = 2000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shoot<= diff)
 {
  DoCast(me->getVictim(), spell_shoot);
  shoot = 2000;
 }else shoot -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_handlerAI(pCreature);
 }
 
 };
 
/*******************
**Razorfen Quilguard
********************/

#define spell_devotion_aura 8258
#define spell_thunderclap 15548

class mob_razorfen_quilguard : public CreatureScript
{
public:
 mob_razorfen_quilguard() : CreatureScript("mob_razorfen_quilguard") {}
 
 struct mob_razorfen_quilguardAI : public ScriptedAI
 {
 mob_razorfen_quilguardAI(Creature *c): ScriptedAI(c) {}
 
 uint32 thunderclap;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_devotion_aura);
 }
 
 void Reset()
 {
 thunderclap = urand(6000, 10000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(thunderclap<= diff)
 {
    DoCast(spell_thunderclap);
	thunderclap = urand(6000, 10000);
 }else thunderclap -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_quilguardAI(pCreature);
 }
 
 };
 
/****************
**Razorfen Warden
*****************/

#define spell_net 6533

class mob_razorfen_warden : public CreatureScript
{
public:
 mob_razorfen_warden() : CreatureScript("mob_razorfen_warden") {}
 
 struct mob_razorfen_wardenAI : public ScriptedAI
 {
 mob_razorfen_wardenAI(Creature *c): ScriptedAI(c) {}
 
 uint32 net;
 
 void Reset()
 {
 net = 6000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(net<= diff)
 {
  DoCast(me->getVictim(), spell_net);
  net = 6000;
 }else net -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_wardenAI(pCreature);
 }
 
 };
 
/*******************
**Death Head Acolyte
********************/

#define spell_mana_burn 15785
#define spell_renew 8362

class mob_death_head_acolyte : public CreatureScript
{
public:
 mob_death_head_acolyte() : CreatureScript("mob_death_head_acolyte") {}
 
 struct mob_death_head_acolyteAI : public ScriptedAI
 {
 mob_death_head_acolyteAI(Creature *c): ScriptedAI(c) {}
 
 uint32 mana_burn;
 uint32 renew;
 
 void Reset()
 {
 mana_burn = 6000;
 renew = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (mana_burn<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_mana_burn);
 mana_burn = 6000;
 } else mana_burn -= diff;
 
 if(renew<= diff)
 {
    DoCast(me, spell_renew);
	renew = urand(5000, 8000);
 }else renew -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_death_head_acolyteAI(pCreature);
 }
 
 };
 
/*****************
**Death Head Adept
******************/

#define spell_chains_of_ice 113
#define spell_frostbolt 20822

class mob_death_head_adept : public CreatureScript
{
public:
 mob_death_head_adept() : CreatureScript("mob_death_head_adept") {}
 
 struct mob_death_head_adeptAI : public ScriptedAI
 {
 mob_death_head_adeptAI(Creature *c): ScriptedAI(c) {}
 
 uint32 chains_of_ice;
 uint32 frostbolt;
 
 void Reset()
 {
 chains_of_ice = 6000;
 frostbolt = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (chains_of_ice<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_chains_of_ice);
 chains_of_ice = 6000;
 } else chains_of_ice -= diff;
 
 if(frostbolt<= diff)
 {
  DoCast(me->getVictim(), spell_frostbolt);
  frostbolt = urand(5000, 8000);
 }else frostbolt -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_death_head_adeptAI(pCreature);
 }
 
 };
 
/******************
**Death's Head Sage
*******************/

#define spell_elemental_protection_totem 8262
#define spell_healing_ward 4971

class mob_death_head_sage : public CreatureScript
{
public:
 mob_death_head_sage() : CreatureScript("mob_death_head_sage") {}
 
 struct mob_death_head_sageAI : public ScriptedAI
 {
 mob_death_head_sageAI(Creature *c): ScriptedAI(c) {}
 
 uint32 elemental_protection_totem;
 uint32 healing_ward;
 
 void Reset()
 {
 elemental_protection_totem = urand(6000, 10000);
 healing_ward = urand(8000, 16000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(elemental_protection_totem<= diff)
 {
    DoCast(spell_elemental_protection_totem);
	elemental_protection_totem = urand(6000, 10000);
 }else elemental_protection_totem -= diff;
 
 if(healing_ward<= diff)
 {
    DoCast(spell_healing_ward);
	healing_ward = urand(8000, 16000);
 }else healing_ward -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_death_head_sageAI(pCreature);
 }
 
 };
 
/******************
**Death's Head Seer
*******************/

#define spell_healing_ward 4971
#define spell_lava_spout_totem 8264

class mob_death_head_seer : public CreatureScript
{
public:
 mob_death_head_seer() : CreatureScript("mob_death_head_seer") {}
 
 struct mob_death_head_seerAI : public ScriptedAI
 {
 mob_death_head_seerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 healing_ward;
 uint32 lava_spout_totem;
 
 void Reset()
 {
 healing_ward = urand(6000, 10000);
 lava_spout_totem = urand(8000, 16000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(healing_ward<= diff)
 {
    DoCast(spell_healing_ward);
	healing_ward = urand(6000, 10000);
 }else healing_ward -= diff;
 
 if(lava_spout_totem<= diff)
 {
    DoCast(spell_lava_spout_totem);
	lava_spout_totem = urand(8000, 16000);
 }else lava_spout_totem -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_death_head_seerAI(pCreature);
 }
 
 };
 
/***********************
**Razorfen Beast Trainer
************************/

#define spell_frost_shot 6984
#define spell_shoot 6660
#define spell_summon_tamed_battleboar 8274

class mob_razorfen_beast_trainer : public CreatureScript
{
public:
 mob_razorfen_beast_trainer() : CreatureScript("mob_razorfen_beast_trainer") {}
 
 struct mob_razorfen_beast_trainerAI : public ScriptedAI
 {
 mob_razorfen_beast_trainerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 frost_shot;
 uint32 shoot;
 
 void EnterCombat(Unit* pWho)
  {
    DoCast(spell_summon_tamed_battleboar);
  }
 
 void Reset()
 {
 frost_shot = urand(6000, 8000);
 shoot = 2000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shoot<= diff)
 {
  DoCast(me->getVictim(), spell_shoot);
  shoot = 2000;
 }else shoot -= diff;
 
 if (frost_shot<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_frost_shot);
 frost_shot = urand(6000, 8000);
 } else frost_shot -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_beast_trainerAI(pCreature);
 }
 
 };
 
/******************
**Razorfen Defender
*******************/

#define spell_improved_blocking 3248
#define spell_shield_bash 11972

class mob_razorfen_defender : public CreatureScript
{
public:
 mob_razorfen_defender() : CreatureScript("mob_razorfen_defender") {}
 
 struct mob_razorfen_defenderAI : public ScriptedAI
 {
 mob_razorfen_defenderAI(Creature *c): ScriptedAI(c) {}
 
 uint32 improved_blocking;
 uint32 shield_bash;
 
 void Reset()
 {
 improved_blocking = urand(6000, 10000);
 shield_bash = urand(4000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(improved_blocking<= diff)
 {
     DoCast(me, spell_improved_blocking);
	 improved_blocking = urand(6000, 10000);
 }else improved_blocking -= diff;
 
 if(shield_bash<= diff)
 {
  DoCast(me->getVictim(), spell_shield_bash);
  shield_bash = urand(4000, 8000);
 }else shield_bash -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_defenderAI(pCreature);
 }
 
 };
 
/********************
**Razorfen Dustweaver
*********************/

#define spell_enveloping_winds 6728
#define spell_summon_wind_howler 8271

class mob_razorfen_dustweaver : public CreatureScript
{
public:
 mob_razorfen_dustweaver() : CreatureScript("mob_razorfen_dustweaver") {}
 
 struct mob_razorfen_dustweaverAI : public ScriptedAI
 {
 mob_razorfen_dustweaverAI(Creature *c): ScriptedAI(c) {}
 
 uint32 enveloping_winds;
 
 void EnterCombat(Unit* pWho)
  {
    DoCast(spell_summon_wind_howler);
  }
 
 void Reset()
 {
 enveloping_winds = urand(6000, 10000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (enveloping_winds<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_enveloping_winds);
 enveloping_winds = urand(6000, 10000);
 } else enveloping_winds -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_dustweaverAI(pCreature);
 }
 
 };
/**********************
**Razorfen GroundShaker
***********************/

#define spell_earth_shock 13281
#define spell_ground_tremor 6524

class mob_razorfen_groundshaker : public CreatureScript
{
public:
 mob_razorfen_groundshaker() : CreatureScript("mob_razorfen_groundshaker") {}
 
 struct mob_razorfen_groundshakerAI : public ScriptedAI
 {
 mob_razorfen_groundshakerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 earth_shock;
 uint32 ground_tremor;
 
 void Reset()
 {
 earth_shock = urand(5000, 8000);
 ground_tremor = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(earth_shock<= diff)
 {
  DoCast(me->getVictim(), spell_earth_shock);
  earth_shock = urand(5000, 8000);
 }else earth_shock -= diff;
 
 if(ground_tremor<= diff)
 {
    DoCast(spell_ground_tremor);
	ground_tremor = 10000;
 }else ground_tremor -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_groundshakerAI(pCreature);
 }
 
 };
 
/*******************
**Razorfen Spearhide
********************/

#define spell_thorns_aura 8148
#define spell_whirling_barrage 8259

class mob_razorfen_spearhide : public CreatureScript
{
public:
 mob_razorfen_spearhide() : CreatureScript("mob_razorfen_spearhide") {}
 
 struct mob_razorfen_spearhideAI : public ScriptedAI
 {
 mob_razorfen_spearhideAI(Creature *c): ScriptedAI(c) {}
 
 uint32 whirling_barrage;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_thorns_aura);
 }
 
 void Reset()
 {
 whirling_barrage = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(whirling_barrage<= diff)
 {
  DoCast(me->getVictim(), spell_whirling_barrage);
  whirling_barrage = 10000;
 }else whirling_barrage -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_spearhideAI(pCreature);
 }
 
 };
 
/*****************
**Razorfen Stalker
******************/

#define spell_backstab 7159

class mob_razorfen_stalker : public CreatureScript
{
public:
 mob_razorfen_stalker() : CreatureScript("mob_razorfen_stalker") {}
 
 struct mob_razorfen_stalkerAI : public ScriptedAI
 {
 mob_razorfen_stalkerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 backstab;
 
 void Reset()
 {
 backstab = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(backstab<= diff)
 {
  DoCast(me->getVictim(), spell_backstab);
  backstab = urand(5000, 8000);
 }else backstab -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_stalkerAI(pCreature);
 }
 
 };
 
/*****************
**Razorfen Totemic
******************/

#define spell_earthgrab_totem 8376
#define spell_healing_ward 4971

class mob_razorfen_totemic : public CreatureScript
{
public:
 mob_razorfen_totemic() : CreatureScript("mob_razorfen_totemic") {}
 
 struct mob_razorfen_totemicAI : public ScriptedAI
 {
 mob_razorfen_totemicAI(Creature *c): ScriptedAI(c) {}
 
 uint32 earthgrab_totem;
 uint32 healing_ward;
 
 void Reset()
 {
 healing_ward = urand(6000, 10000);
 earthgrab_totem = urand(8000, 16000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(healing_ward<= diff)
 {
    DoCast(spell_healing_ward);
	healing_ward = urand(6000, 10000);
 }else healing_ward -= diff;
 
 if(earthgrab_totem<= diff)
 {
    DoCast(spell_earthgrab_totem);
	earthgrab_totem = urand(8000, 16000);
 }else earthgrab_totem -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_totemicAI(pCreature);
 }
 
 };
 
/*******************
**Blood Of Agamaggan
********************/

#define spell_curse_of_blood 8282

class mob_blood_of_agamaggan : public CreatureScript
{
public:
 mob_blood_of_agamaggan() : CreatureScript("mob_blood_of_agamaggan") {}
 
 struct mob_blood_of_agamagganAI : public ScriptedAI
 {
 mob_blood_of_agamagganAI(Creature *c): ScriptedAI(c) {}
 
 uint32 curse_of_blood;
 
 void Reset()
 {
 curse_of_blood = urand(4000, 6000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(curse_of_blood<= diff)
 {
  DoCast(me->getVictim(), spell_curse_of_blood);
  curse_of_blood = urand(4000, 6000);
 }else curse_of_blood -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_blood_of_agamagganAI(pCreature);
 }
 
 };
 
/******************
**Greater Kraul Bat
*******************/

#define spell_sonic_burst 8281

class mob_greater_kraul_bat : public CreatureScript
{
public:
 mob_greater_kraul_bat() : CreatureScript("mob_greater_kraul_bat") {}
 
 struct mob_greater_kraul_batAI : public ScriptedAI
 {
 mob_greater_kraul_batAI(Creature *c): ScriptedAI(c) {}
 
 uint32 sonic_burst;
 
 void Reset()
 {
 sonic_burst = urand(6000, 9000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(sonic_burst<= diff)
 {
    DoCast(spell_sonic_burst);
	sonic_burst = urand(6000, 9000);
 }else sonic_burst -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_greater_kraul_batAI(pCreature);
 }
 
 };
 
/*******************
**Quilguard Champion
********************/

#define spell_defensive_stance 7164
#define spell_devotion_aura 8258
#define spell_sunder_armor 15572

class mob_quilguard_champion : public CreatureScript
{
public:
 mob_quilguard_champion() : CreatureScript("mob_quilguard_champion") {}
 
 struct mob_quilguard_championAI : public ScriptedAI
 {
 mob_quilguard_championAI(Creature *c): ScriptedAI(c) {}
 
 uint32 sunder_armor;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_defensive_stance);
	DoCast(me, spell_devotion_aura);
 }
 
 void Reset()
 {
 sunder_armor = urand(3000, 4000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(sunder_armor<= diff)
 {
  DoCast(me->getVictim(), spell_sunder_armor);
  sunder_armor = urand(3000, 4000);
 }else sunder_armor -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_quilguard_championAI(pCreature);
 }
 
 };
 
/*********************
**Razorfen Beastmaster
**********************/

#define spell_poisoned_shot 8275
#define spell_shoot 6660
#define spell_summon_tamed_hyena 8276

class mob_razorfen_beastmaster : public CreatureScript
{
public:
 mob_razorfen_beastmaster() : CreatureScript("mob_razorfen_beastmaster") {}
 
 struct mob_razorfen_beastmasterAI : public ScriptedAI
 {
 mob_razorfen_beastmasterAI(Creature *c): ScriptedAI(c) {}
 
 uint32 poisoned_shot;
 uint32 shoot;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(spell_summon_tamed_hyena);
 }
 
 void Reset()
 {
 poisoned_shot = urand(6000, 9000);
 shoot = 2000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (poisoned_shot<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_poisoned_shot);
 poisoned_shot = urand(6000, 9000);
 } else poisoned_shot -= diff;
 
 if (shoot<= diff)
 {
  DoCast(me->getVictim(), spell_shoot);
  shoot = 2000;
 }else shoot -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_beastmasterAI(pCreature);
 }
 
 };

/**********************
**Razorfen EarthBreaker
***********************/

#define spell_earth_shock 15501
#define spell_mind_tremor 8272

class mob_razorfen_earthbreaker : public CreatureScript
{
public:
 mob_razorfen_earthbreaker() : CreatureScript("mob_razorfen_earthbreaker") {}
 
 struct mob_razorfen_earthbreakerAI : public ScriptedAI
 {
 mob_razorfen_earthbreakerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 earth_shock;
 uint32 mind_tremor;
 
 void Reset()
 {
 earth_shock = urand(5000, 8000);
 mind_tremor = urand(8000, 10000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if (earth_shock<= diff)
 {
  DoCast(me->getVictim(), spell_earth_shock);
  earth_shock = urand(5000, 8000);
 }else earth_shock -= diff;
 
 if(mind_tremor<= diff)
 {
    DoCast(spell_mind_tremor);
	mind_tremor = urand(8000, 10000);
 }else mind_tremor -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_razorfen_earthbreakerAI(pCreature);
 }
 
 };
 
/****************
**Rotting Agam'ar
*****************/

#define spell_cursed_blood 8267

class mob_rotting_agamar : public CreatureScript
{
public:
 mob_rotting_agamar() : CreatureScript("mob_rotting_agamar") {}
 
 struct mob_rotting_agamarAI : public ScriptedAI
 {
 mob_rotting_agamarAI(Creature *c): ScriptedAI(c) {}
 
 uint32 cursed_blood;
 
 void Reset()
 {
 cursed_blood = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(cursed_blood<= diff)
 {
    DoCast(spell_cursed_blood);
	cursed_blood = urand(5000, 8000);
 }else cursed_blood -= diff;
 
    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_rotting_agamarAI(pCreature);
 }
 
 };
 
/**************
**Ward Guardian
***************/

#define spell_healing_wave 12491

class mob_ward_guardian : public CreatureScript
{
public:
 mob_ward_guardian() : CreatureScript("mob_ward_guardian") {}
 
 struct mob_ward_guardianAI : public ScriptedAI
 {
 mob_ward_guardianAI(Creature *c): ScriptedAI(c) {}
 
 uint32 healing_wave;
 
 void Reset()
 {
 healing_wave = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(healing_wave<= diff)
 {
    DoCast(me, spell_healing_wave);
	healing_wave = urand(5000, 8000);
 }else healing_wave -= diff;
 
    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_ward_guardianAI(pCreature);
 }
 
 };
 
 void AddSC_mob_trash_razorfen_kraul()
{
    new mob_agamar();
	new mob_death_head_priest();
	new mob_raging_agamar();
	new mob_razorfen_geomancer();
	new mob_razorfen_handler();
	new mob_razorfen_quilguard();
	new mob_razorfen_warden();
	new mob_death_head_acolyte();
	new mob_death_head_adept();
	new mob_death_head_sage();
	new mob_death_head_seer();
	new mob_razorfen_beast_trainer();
	new mob_razorfen_defender();
	new mob_razorfen_dustweaver();
	new mob_razorfen_groundshaker();
	new mob_razorfen_spearhide();
	new mob_razorfen_stalker();
	new mob_razorfen_totemic();
	new mob_blood_of_agamaggan();
	new mob_greater_kraul_bat();
	new mob_quilguard_champion();
	new mob_razorfen_beastmaster();
	new mob_razorfen_earthbreaker();
	new mob_rotting_agamar();
	new mob_ward_guardian();
}