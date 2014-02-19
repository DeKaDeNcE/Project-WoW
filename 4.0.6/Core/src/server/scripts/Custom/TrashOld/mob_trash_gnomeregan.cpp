/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */

#include "ScriptPCH.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

/********************
**Mobile Alert System
*********************/

#define spell_flare 94528

class mob_mobile_alert_system : public CreatureScript
{
public:
 mob_mobile_alert_system() : CreatureScript("mob_mobile_alert_system") {}
 
 struct mob_mobile_alert_systemAI : public ScriptedAI
 {
 mob_mobile_alert_systemAI(Creature *c): ScriptedAI(c) {}
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_flare);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_mobile_alert_systemAI(pCreature);
 }
 
 };
 
/********************
**Caverndeep Burrower
*********************/

#define spell_strike 87081

class mob_caverndeep_burrower : public CreatureScript
{
public:
 mob_caverndeep_burrower() : CreatureScript("mob_caverndeep_burrower") {}
 
 struct mob_caverndeep_burrowerAI : public ScriptedAI
 {
 mob_caverndeep_burrowerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 strike;
 
 void Reset()
 {
 strike = urand(3000, 5000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(strike<= diff)
 {
  DoCast(me->getVictim(), spell_strike);
  strike = urand(3000, 5000);
 }else strike -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_caverndeep_burrowerAI(pCreature);
 }
 
 };
 
/********************
**Irradiated Pillager
*********************/

#define spell_frenzy 8269
#define spell_radiation 9798
#define spell_radiation_bolt 92266

class mob_irradiated_pillager : public CreatureScript
{
public:
 mob_irradiated_pillager() : CreatureScript("mob_irradiated_pillager") {}
 
 struct mob_irradiated_pillagerAI : public ScriptedAI
 {
 mob_irradiated_pillagerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 radiation;
 uint32 frenzy;
 uint32 radiation_bolt;
 
 void Reset()
 {
 radiation = 6000;
 radiation_bolt = urand(5000, 8000);
 frenzy = urand(10000, 12000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(radiation<= diff)
 {
  DoCast(me->getVictim(), spell_radiation);
  radiation = 6000;
 }else radiation -= diff;
 
 if (radiation_bolt<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_radiation_bolt);
 radiation_bolt = urand(5000, 8000);
 } else radiation_bolt -= diff;
 
 if(frenzy<= diff)
 {
    DoCast(me, spell_frenzy);
	frenzy = urand(10000, 12000);
 }else frenzy -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_irradiated_pillagerAI(pCreature);
 }
 
 };
 
/****************
**Burning Servant
*****************/

#define spell_summon_embers 10869

class mob_burning_servant : public CreatureScript
{
public:
 mob_burning_servant() : CreatureScript("mob_burning_servant") {}
 
 struct mob_burning_servantAI : public ScriptedAI
 {
 mob_burning_servantAI(Creature *c): ScriptedAI(c) {}
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(spell_summon_embers);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_burning_servantAI(pCreature);
 }
 
 };
 
/******************
**Caverndeep Reaver
*******************/

#define spell_cleave 15496

class mob_caverndeep_reaver : public CreatureScript
{
public:
 mob_caverndeep_reaver() : CreatureScript("mob_caverndeep_reaver") {}
 
 struct mob_caverndeep_reaverAI : public ScriptedAI
 {
 mob_caverndeep_reaverAI(Creature *c): ScriptedAI(c) {}
 
 uint32 cleave;
 
 void Reset()
 {
 cleave = urand(3000, 5000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(cleave<= diff)
 {
  DoCast(me->getVictim(), spell_cleave);
  cleave = urand(3000, 5000);
 }else cleave -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_caverndeep_reaverAI(pCreature);
 }
 
 };

/*****************
**Irradiated Slime
******************/

#define spell_radiation_cloud 10341
#define spell_toxic_nova 81039

class mob_irradiated_slime : public CreatureScript
{
public:
 mob_irradiated_slime() : CreatureScript("mob_irradiated_slime") {}
 
 struct mob_irradiated_slimeAI : public ScriptedAI
 {
 mob_irradiated_slimeAI(Creature *c): ScriptedAI(c) {}
 
 uint32 radiation_cloud;
 uint32 toxic_nova;
 
 void Reset()
 {
 radiation_cloud = 10000;
 toxic_nova = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if (radiation_cloud<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_radiation_cloud);
 radiation_cloud = 10000;
} else radiation_cloud-= diff;
	
 if(toxic_nova<= diff)
 {
    DoCast(spell_toxic_nova);
	toxic_nova = urand(5000, 8000);
 }else toxic_nova -= diff;
  
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_irradiated_slimeAI(pCreature);
 }
 
 };
 
/*********************
**Leprous Machinesmith
**********************/

#define spell_supercharge 10732
#define spell_throw_wrench 13398
#define spell_tune_up 10348

class mob_leprous_machinesmith : public CreatureScript
{
public:
 mob_leprous_machinesmith() : CreatureScript("mob_leprous_machinesmith") {}
 
 struct mob_leprous_machinesmithAI : public ScriptedAI
 {
 mob_leprous_machinesmithAI(Creature *c): ScriptedAI(c) {}
 
 uint32 supercharge;
 uint32 throw_wrench;
 uint32 tune_up;
 
 void Reset()
 {
 supercharge = 10000;
 throw_wrench = urand(3000, 5000);
 tune_up = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(supercharge<= diff)
 {
    DoCast(spell_supercharge);
	supercharge = 10000;
 }else supercharge -= diff;
 
 if (throw_wrench<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_throw_wrench);
 throw_wrench = urand(3000, 5000);
} else throw_wrench-= diff;
 
 if(tune_up <= diff)
 {
    DoCast(me, spell_tune_up);
	tune_up = 15000;
 }else tune_up -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_leprous_machinesmithAI(pCreature);
 }
 
 };
 
/*******************
**Leprous Technician
********************/

#define spell_supercharge 10732
#define spell_throw_wrench 13398
#define spell_tune_up 10348

class mob_leprous_technician : public CreatureScript
{
public:
 mob_leprous_technician() : CreatureScript("mob_leprous_technician") {}
 
 struct mob_leprous_technicianAI : public ScriptedAI
 {
 mob_leprous_technicianAI(Creature *c): ScriptedAI(c) {}
 
 uint32 supercharge;
 uint32 throw_wrench;
 uint32 tune_up;
 
 void Reset()
 {
 supercharge = 10000;
 throw_wrench = urand(3000, 5000);
 tune_up = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(supercharge<= diff)
 {
    DoCast(spell_supercharge);
	supercharge = 10000;
 }else supercharge -= diff;
 
 if (throw_wrench<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_throw_wrench);
 throw_wrench = urand(3000, 5000);
} else throw_wrench-= diff;
 
 if(tune_up <= diff)
 {
    DoCast(me, spell_tune_up);
	tune_up = 15000;
 }else tune_up -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_leprous_technicianAI(pCreature);
 }
 
 };
 
/*****************
**Corrosive Lurker
******************/

#define spell_corrosive_ooze 9460

class mob_corrosive_lurker : public CreatureScript
{
public:
 mob_corrosive_lurker() : CreatureScript("mob_corrosive_lurker") {}
 
 struct mob_corrosive_lurkerAI : public ScriptedAI
 {
 mob_corrosive_lurkerAI(Creature *c): ScriptedAI(c) {}
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_corrosive_ooze);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_corrosive_lurkerAI(pCreature);
 }
 
 };
 
/**************
**Holdout Medic
***************/

#define spell_heal 34945
#define spell_power_word_fortitude 13864
#define spell_renew 22168

class mob_holdout_medic : public CreatureScript
{
public:
 mob_holdout_medic() : CreatureScript("mob_holdout_medic") {}
 
 struct mob_holdout_medicAI : public ScriptedAI
 {
 mob_holdout_medicAI(Creature *c): ScriptedAI(c) {}
 
 uint32 heal;
 uint32 renew;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_power_word_fortitude);
 }
 
 void Reset()
 {
 heal = 8000;
 renew = urand(9000, 12000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(heal <= diff)
 {
    DoCast(me, spell_heal);
	heal = 8000;
 }else heal -= diff;
 
 if(renew<= diff)
 {
    DoCast(me, spell_renew);
	renew = urand(9000, 12000);
 }else renew -= diff;
 
   DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_holdout_medicAI(pCreature);
 }
 
 };
 
/*******************
**Holdout Technician
********************/

#define spell_bomb 8858
#define spell_shoot 6660

class mob_holdout_technician : public CreatureScript
{
public:
 mob_holdout_technician() : CreatureScript("mob_holdout_technician") {}
 
 struct mob_holdout_technicianAI : public ScriptedAI
 {
 mob_holdout_technicianAI(Creature *c): ScriptedAI(c) {}
 
 uint32 bomb;
 uint32 shoot;
 
 void Reset()
 {
 bomb = 8000;
 shoot = 2000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (bomb<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_bomb);
 bomb = 8000;
 } else bomb-= diff;
 
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
 return new mob_holdout_technicianAI(pCreature);
 }
 
 };
 
/****************
**Holdout Warrior
*****************/

#define spell_pummel 12555
#define spell_strike 11976

class mob_holdout_warrior : public CreatureScript
{
public:
 mob_holdout_warrior() : CreatureScript("mob_holdout_warrior") {}
 
 struct mob_holdout_warriorAI : public ScriptedAI
 {
 mob_holdout_warriorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 pummel;
 uint32 strike;
 
 void Reset()
 {
 pummel = 8000;
 strike = urand(4000, 6000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(pummel<= diff)
 {
  DoCast(me->getVictim(), spell_pummel);
  pummel = 8000;
 }else pummel -= diff;
 
 if(strike<= diff)
 {
  DoCast(me->getVictim(), spell_strike);
  strike = urand(4000, 6000);
 }else strike -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_holdout_warriorAI(pCreature);
 }
 
 };
 
/******************
**Irradiated Horror
*******************/

#define spell_poison 744

class mob_irradiated_horror : public CreatureScript
{
public:
 mob_irradiated_horror() : CreatureScript("mob_irradiated_horror") {}
 
 struct mob_irradiated_horrorAI : public ScriptedAI
 {
 mob_irradiated_horrorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 poison;
 
 void Reset()
 {
 poison = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (poison<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_poison);
 poison = urand(5000, 8000);
 } else poison-= diff;

  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_irradiated_horrorAI(pCreature);
 }
 
 };
 
/*****************
**Leprous Defender
******************/

#define spell_multishot 14443
#define spell_shoot 6660

class mob_leprous_defender : public CreatureScript
{
public:
 mob_leprous_defender() : CreatureScript("mob_leprous_defender") {}
 
 struct mob_leprous_defenderAI : public ScriptedAI
 {
 mob_leprous_defenderAI(Creature *c): ScriptedAI(c) {}
 
 uint32 multishot;
 uint32 shoot;
 
 void Reset()
 {
 multishot = urand(5000, 8000);
 shoot = 2000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (multishot<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_multishot);
 multishot = urand(5000, 8000);
 } else multishot -= diff;
 
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
 return new mob_leprous_defenderAI(pCreature);
 }
 
 };
 
/***************
**Mechano - Tank
****************/

#define spell_machine_gun 10346

class mob_mechano_tank : public CreatureScript
{
public:
 mob_mechano_tank() : CreatureScript("mob_mechano_tank") {}
 
 struct mob_mechano_tankAI : public ScriptedAI
 {
 mob_mechano_tankAI(Creature *c): ScriptedAI(c) {}
 
 uint32 machine_gun;
 
 void Reset()
 {
 machine_gun = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (machine_gun<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_machine_gun);
 machine_gun = urand(5000, 8000);
 } else machine_gun -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_mechano_tankAI(pCreature);
 }
 
 };
 
/**********************
**Arcane Nullifier X-21
***********************/

#define spell_mass_nullify 10832
#define spell_reflection_field 10831

class mob_arcane_nullifier : public CreatureScript
{
public:
 mob_arcane_nullifier() : CreatureScript("mob_arcane_nullifier") {}
 
 struct mob_arcane_nullifierAI : public ScriptedAI
 {
 mob_arcane_nullifierAI(Creature *c): ScriptedAI(c) {}
 
 uint32 mass_nullify;
 uint32 reflection_field;
 
 void Reset()
 {
 mass_nullify = urand(5000, 8000);
 reflection_field = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(mass_nullify<= diff)
 {
    DoCast(spell_mass_nullify);
	mass_nullify = urand(5000, 8000);
 }else mass_nullify -= diff;
 
 if(reflection_field<= diff)
 {
    DoCast(me, spell_reflection_field);
	reflection_field = 10000;
 }else reflection_field -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_arcane_nullifierAI(pCreature);
 }
 
 };
 
/****************
**Dark Iron Agent
*****************/

#define spell_dark_iron_land_mine 11802

class mob_dark_iron_agent : public CreatureScript
{
public:
 mob_dark_iron_agent() : CreatureScript("mob_dark_iron_agent") {}
 
 struct mob_dark_iron_agentAI : public ScriptedAI
 {
 mob_dark_iron_agentAI(Creature *c): ScriptedAI(c) {}
 
 uint32 dark_iron_land_mine;
 
 void Reset()
 {
 dark_iron_land_mine = 8000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (dark_iron_land_mine<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_dark_iron_land_mine);
 dark_iron_land_mine = 8000;
 } else dark_iron_land_mine -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_dark_iron_agentAI(pCreature);
 }
 
 };
 
/********************
**Mechanized Guardian
*********************/

#define spell_electrified_net 11820

class mob_mechanized_guardian : public CreatureScript
{
public:
 mob_mechanized_guardian() : CreatureScript("mob_mechanized_guardian") {}
 
 struct mob_mechanized_guardianAI : public ScriptedAI
 {
 mob_mechanized_guardianAI(Creature *c): ScriptedAI(c) {}
 
 uint32 electrified_net;
 
 void Reset()
 {
 electrified_net = urand(5000, 8000);
 }

 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (electrified_net<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_electrified_net);
 electrified_net = urand(5000, 8000);
 } else electrified_net -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_mechanized_guardianAI(pCreature);
 }
 
 };
 
/********************
**Mechano Flamewalker
*********************/

#define spell_fire_nova 11970
#define spell_flame_spray 10733

class mob_mechano_flamewalker : public CreatureScript
{
public:
 mob_mechano_flamewalker() : CreatureScript("mob_mechano_flamewalker") {}
 
 struct mob_mechano_flamewalkerAI : public ScriptedAI
 {
 mob_mechano_flamewalkerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fire_nova;
 uint32 flame_spray;
 
 void Reset()
 {
 fire_nova = urand(5000, 8000);
 flame_spray = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(fire_nova<= diff)
 {
    DoCast(me, spell_fire_nova);
	fire_nova = urand(5000, 8000);
 }else fire_nova -= diff;
 
 if(flame_spray<= diff)
 {
  DoCast(me->getVictim(), spell_flame_spray);
  flame_spray = 10000;
 }else flame_spray -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_mechano_flamewalkerAI(pCreature);
 }
 
 };
 
/********************
**Mechano Frostwalker
*********************/

#define spell_hail_storm 10734
#define spell_ice_blast 11264

class mob_mechano_frostwalker : public CreatureScript
{
public:
 mob_mechano_frostwalker() : CreatureScript("mob_mechano_frostwalker") {}
 
 struct mob_mechano_frostwalkerAI : public ScriptedAI
 {
 mob_mechano_frostwalkerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 hail_storm;
 uint32 ice_blast;
 
 void Reset()
 {
 ice_blast = urand(5000, 8000);
 hail_storm = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(ice_blast<= diff)
 {
    DoCast(me, spell_ice_blast);
	ice_blast = urand(5000, 8000);
 }else ice_blast -= diff;
 
 if (hail_storm<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_hail_storm);
 hail_storm = 10000;
 } else hail_storm -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_mechano_frostwalkerAI(pCreature);
 }
 
 };
 
/*************************
**Peacemaker Security Suit
**************************/

#define spell_net 6533
#define spell_pacify 10730

class mob_peacemaker_security_suit : public CreatureScript
{
public:
 mob_peacemaker_security_suit() : CreatureScript("mob_peacemaker_security_suit") {}
 
 struct mob_peacemaker_security_suitAI : public ScriptedAI
 {
 mob_peacemaker_security_suitAI(Creature *c): ScriptedAI(c) {}
 
 uint32 net;
 uint32 pacify;
 
 void Reset()
 {
 net = urand(5000, 8000);
 pacify = 7000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (net<= diff)
 {
 if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
 DoCast(pTarget, spell_net);
 net = urand(5000, 8000);
 } else net -= diff;
 
 if (pacify<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_pacify);
 pacify = 8000;
 } else pacify -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_peacemaker_security_suitAI(pCreature);
 }
 
 };
 
/********************
**Dark Iron Land Mine
*********************/

#define spell_detonation 92552

class mob_dark_iron_land_mine : public CreatureScript
{
public:
 mob_dark_iron_land_mine() : CreatureScript("mob_dark_iron_land_mine") {}
 
 struct mob_dark_iron_land_mineAI : public ScriptedAI
 {
 mob_dark_iron_land_mineAI(Creature *c): ScriptedAI(c) {}
 
 uint32 detonation;
 
  void JustDied(Unit * /*victim*/)
        {
            DoCast(me, spell_detonation);
		}
	};
	
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_dark_iron_land_mineAI(pCreature);
 }
 
 };
 
/*********************
**Dark Iron Ambassador
**********************/

#define spell_fire_shield 184
#define spell_fireball 9053
#define spell_summon_burning_servant 10870

class mob_dark_iron_ambassador : public CreatureScript
{
public:
 mob_dark_iron_ambassador() : CreatureScript("mob_dark_iron_ambassador") {}
 
 struct mob_dark_iron_ambassadorAI : public ScriptedAI
 {
 mob_dark_iron_ambassadorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fireball;
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_fire_shield); 
    DoCast(spell_summon_burning_servant);
 }
 
 void Reset()
 {
 fireball = urand(5000, 8000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(fireball<= diff)
 {
  DoCast(me->getVictim(), spell_fireball);
  fireball = urand(5000, 8000);
 }else fireball -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_dark_iron_ambassadorAI(pCreature);
 }
 
 };
 
void AddSC_mob_trash_gnomeregan()
{
    new mob_mobile_alert_system();
	new mob_caverndeep_burrower();
	new mob_irradiated_pillager();
	new mob_burning_servant();
	new mob_caverndeep_reaver();
	new mob_irradiated_slime();
	new mob_leprous_machinesmith();
	new mob_leprous_technician();
	new mob_corrosive_lurker();
	new mob_holdout_medic();
	new mob_holdout_technician();
	new mob_holdout_warrior();
	new mob_irradiated_horror();
	new mob_leprous_defender();
	new mob_mechano_tank();
	new mob_arcane_nullifier();
	new mob_dark_iron_agent();
	new mob_mechanized_guardian();
	new mob_mechano_flamewalker();
	new mob_mechano_frostwalker();
	new mob_peacemaker_security_suit();
	new mob_dark_iron_land_mine();
	new mob_dark_iron_ambassador();
}