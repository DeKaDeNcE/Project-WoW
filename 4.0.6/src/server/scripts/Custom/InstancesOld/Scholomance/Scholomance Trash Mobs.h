/*
 * Copyright (C) 2010-2012 Project TBEmu <http://www.trueblood-servers.com/>
 * by JeanClaute
 */
 
#include "ScriptPCH.h"
#include "scholomance.h"

/*****************
**Risen Aberration
******************/

#define spell_fixate 12021

class mob_risen_aberration : public CreatureScript
{
public:
 mob_risen_aberration() : CreatureScript("mob_risen_aberration") {}
 
 struct mob_risen_aberrationAI : public ScriptedAI
 {
 mob_risen_aberrationAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fixate;
 
 void Reset()
 {
 fixate = 5000 ;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
if(fixate<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_fixate);
       fixate = 5000 ;
 } else fixate -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_risen_aberrationAI(pCreature);
 }
 
 };
 
/****************
**Unstable Corpse
*****************/

#define spell_disease_burst 17690

class mob_unstable_corpse : public CreatureScript
{
public:
 mob_unstable_corpse() : CreatureScript("mob_unstable_corpse") {}
 
 struct mob_unstable_corpseAI : public ScriptedAI
 {
 mob_unstable_corpseAI(Creature *c): ScriptedAI(c) {}
 
 void EnterCombat(Unit* pWho)
 {
    DoCast(me, spell_desease_burst);
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
 return new mob_unstable_corpseAI(pCreature);
 }
 
 };
 
/******************
**Plagued Hatchling
*******************/

#define spell_diseased_spit 81236

class mob_plagued_hatchling : public CreatureScript
{
public:
 mob_plagued_hatchling() : CreatureScript("mob_plagued_hatchling") {}
 
 struct mob_plagued_hatchlingAI : public ScriptedAI
 {
 mob_plagued_hatchlingAI(Creature *c): ScriptedAI(c) {}

 uint32 diseased_spit;
 
 void Reset()
 {
 disease_spit = 5000 ;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(disease_spit<= diff)
 {
  DoCast(me->getVictim(), spell_disease_spit);
  disease_spit = 5000 ;
 }else disease_spit -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_plagued_hatchlingAI(pCreature);
 }
 
 };
 
/******************
**Reanimated Corpse
*******************/

#define spell_dark_plague 18270

class mob_reanimated_corpse : public CreatureScript
{
public:
 mob_reanimated_corpse() : CreatureScript("mob_reanimated_corpse") {}
 
 struct mob_reanimated_corpseAI : public ScriptedAI
 {
 mob_reanimated_corpseAI(Creature *c): ScriptedAI(c) {}

 uint32 dark_plague;
 
 void Reset()
 {
 dark_plague = 5000 ;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(dark_plague<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_dark_plague);
       dark_plague = 5000 ;
 } else dark_plague -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_reanimated_corpseAI(pCreature);
 }
 
 };
 
/***************
**Diseased Ghoul
****************/

#define spell_cloud_of_disease 81285

class mob_diseased_ghoul : public CreatureScript
{
public:
 mob_diseased_ghoul() : CreatureScript("mob_diseased_ghoul") {}
 
 struct mob_diseased_ghoulAI : public ScriptedAI
 {
 mob_diseased_ghoulAI(Creature *c): ScriptedAI(c) {}

 void JustDied(Unit* /*Killer*/)
 {
    DoCast(spell_cloud_of_disease);
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
 return new mob_diseased_ghoulAI(pCreature);
 }
 
 };
 
/********************
**Scholomance Acolyte
*********************/

#define spell_cripple 11443
#define spell_dark_mending 17613
#define spell_mind_flay  17165


class mob_scholomance_acolyte : public CreatureScript
{
public:
 mob_scholomance_acolyte() : CreatureScript("mob_scholomance_acolyte") {}
 
 struct mob_scholomance_acolyteAI : public ScriptedAI
 {
 mob_scholomance_acolyteAI(Creature *c): ScriptedAI(c) {}
 
 uint32 cripple;
 uint32 dark_mending;
 uint32 mind_flay;
 
 void Reset()
 {
    cripple = urand(8000, 10000); 
    dark_mending = urand(6000, 9000)
	mind_flay = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (cripple<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 5.0f, true))
 DoCast(target, spell_cripple);
 cripple = urand(8000, 10000);
 } else cripple -= diff;
 
 if (!HealthAbovePct(50) && !me->IsNonMeleeSpellCasted(false) && dark_mending <= diff)
    {
        DoCast(me, spell_dark_mending);
        dark_mending = urand(6000, 9000)
    } else dark_mending -= diff;
	
 if(mind_flay<= diff)
 {
  DoCast(me->getVictim(), spell_mind_flay);
  mind_flay = 15000;
 }else mind_flay -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_acolyteAI(pCreature);
 }
 
 };
 
/**********************
**Scholomance Necrolyte
***********************/

#define spell_shadow_barrier 17151
#define spell_shadow_bolt 12739
#define spell_shadow_shock 17439

class mob_scholomance_necrolyte : public CreatureScript
{
public:
 mob_scholomance_necrolyte() : CreatureScript("mob_scholomance_necrolyte") {}
 
 struct mob_scholomance_necrolyteAI : public ScriptedAI
 {
 mob_scholomance_necrolyteAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shadow_barrier;
 uint32 shadow_bolt;
 uint32 shadow_shock;
 
 void Reset()
 {
    shadow_barrier = 20000; 
    shadow_bolt = 5000;
	shadow_shock = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shadow_barrier <= diff)
 {
    DoCast(me, spell_shadow_barrier);
	shadow_barrier = 20000; 
 }else shadow_barrier -= diff;
 
 if(shadow_bolt<= diff)
 {
  DoCast(me->getVictim(), spell_shadow_bolt);
  shadow_bolt = 5000 + rand()%8000;
 }else shadow_bolt -= diff;
 
 if (shadow_shock<= diff)
 {
 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
 DoCast(target, spell_shadow_shock);
 shadow_shock = 10000 + rand()%15000;
 } else shadow_shock -= diff;
 
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_necrolyteAI(pCreature);
 }
 
 };
 
/*********************
**Scholomance Neophyte
**********************/

#define spell_fear 12542
#define spell_mind_flay 17165
#define spell_shadow_bolt 12739

class mob_scholomance_neophyte : public CreatureScript
{
public:
 mob_scholomance_neophyte() : CreatureScript("mob_scholomance_neophyte") {}
 
 struct mob_scholomance_neophyteAI : public ScriptedAI
 {
 mob_scholomance_neophyteAI(Creature *c): ScriptedAI(c) {}
 
 uint32 fear;
 uint32 mind_flay;
 uint32 shadow_bolt;
 
 void Reset()
 {
    fear = 8000; 
    shadow_bolt = 5000;
	mind_flay = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(fear<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_fear);
       fear = 8000 ;
 } else fear -= diff;
 
 if(shadow_bolt<= diff)
 {
  DoCast(me->getVictim(), spell_shadow_bolt);
  shadow_bolt = 5000 + rand()%8000;
 }else shadow_bolt -= diff;
 
 if(mind_flay<= diff)
 {
  DoCast(me->getVictim(), spell_mind_flay);
  mind_flay = 10000;
 }else mind_flay -= diff;
 
 DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_neophyteAI(pCreature);
 }
 
 };
 
/*****************
**Risen Bonewarder
******************/

#define spell_bone_armor 80850
#define spell_consuming_shadows 17715
#define spell_drain_life 17620

class mob_risen_bonewarder : public CreatureScript
{
public:
 mob_risen_bonewarder() : CreatureScript("mob_risen_bonewarder") {}
 
 struct mob_risen_bonewarderAI : public ScriptedAI
 {
 mob_risen_bonewarderAI(Creature *c): ScriptedAI(c) {}
 
 uint32 consuming_shadows;
 uint32 drain_life;
 
 void EnterCombat(Unit* pWho)
 {
   DoCast(me, spell_bone_armor);
 }
 
 void Reset()
 { 
    consuming_shadows = urand(8000, 10000);
	drain_life = 8000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;

 if(consuming_shadows<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_consuming_shadows);
       consuming_shadows = urand(8000, 10000);
 } else consuming_shadows -= diff;
 
 if (!HealthAbovePct(50) && !me->IsNonMeleeSpellCasted(false) && drain_life <= diff)
    {
        DoCast(me->getVictim(), spell_drain_life);
        drain_life = 8000;
    }else drain_life -= diff;
	
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_risen_bonewarderAI(pCreature);
 }
 
 };

/************
**Risen Guard
*************/

#define spell_shield_slam 15655
#define spell_sunder_armor 11971

class mob_risen_guard : public CreatureScript
{
public:
 mob_risen_guard() : CreatureScript("mob_risen_guard") {}
 
 struct mob_risen_guardAI : public ScriptedAI
 {
 mob_risen_guardAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shield_slam;
 uint32 sunder_armor;

 void Reset()
 { 
    shield_slam = urand(8000, 10000);
	sunder_armor = 5000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shield_slam<= diff)
 {
    DoCast(me->getVictim(), spell_shield_slam);
    shield_slam = urand(8000, 10000);
 }else shield_slam -= diff;
 
 if(sunder_armor<= diff)
 {
    DoCast(me->getVictim(), spell_sunder_armor);
    sunder_armor = 5000;
 }else sunder_armor -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_risen_guardAI(pCreature);
 }
 
 };
 
/***************
**Risen Guardian
****************/

#define spell_cripple 11443
#define spell_shadow_shock  16583
#define spell_shrink 7289
#define spell_veil_of_shadow 7068
#define spell_wither_touch 4974

class mob_risen_guardian : public CreatureScript
{
public:
 mob_risen_guardian() : CreatureScript("mob_risen_guardian") {}
 
 struct mob_risen_guardianAI : public ScriptedAI
 {
 mob_risen_guardianAI(Creature *c): ScriptedAI(c) {}
 
 uint32 cripple;
 uint32 shadow_shock;
 uint32 veil_of_shadow;
 
 void EnterCombat(Unit* pWho)
 {
   DoCast(me->getVictim(), spell_wither_touch);
 }
 
 void Reset()
 { 
    cripple = urand(8000, 20000);
	shadow_shock = 5000;
	veil_of_shadow = urand(15000, 20000);
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if (cripple <= diff)
 {
    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 5.0f, true))
	    DoCast(target, RAND(spell_cripple, spell_shrink));
	    cripple = urand(8000, 20000);
 }else cripple -= diff;
 
 if(shadow_shock<= diff)
 {
    DoCast(me->getVictim(), spell_shadow_shock);
    shadow_shock = 5000 + rand()%8000;
 }else shadow_shock -= diff;

  if(veil_of_shadow<= diff)
 {
    DoCast(me->getVictim(), spell_veil_of_shadow);
    veil_of_shadow = urand(15000, 20000);
 }else veil_of_shadow -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_risen_guardianAI(pCreature);
 }
 
 };
 
/***********
**Necrofiend
************/

#define spell_deadly_poison 3583
#define spell_web_explosion 15474

class mob_necrofiend : public CreatureScript
{
public:
 mob_necrofiend() : CreatureScript("mob_necrofiend") {}
 
 struct mob_necrofiendAI : public ScriptedAI
 {
 mob_necrofiendAI(Creature *c): ScriptedAI(c) {}
 
 uint32 deadly_poison;
 uint32 web_explosion;
 
 void Reset()
 { 
    deadly_poison = urand(8000, 20000);
	web_explosion = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
  if(deadly_poison<= diff)
 {
    DoCast(me->getVictim(), spell_deadly_poison);
    deadly_poison = urand(8000, 20000);
 }else deadly_poison -= diff;
 
 if(web_explosion<= diff)
 {
    DoCast(spell_web_explosion);
	web_explosion = 10000;
 }else web_explosion -= diff;
 
  DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_necrofiendAI(pCreature);
 }
 
 };
 
/****************
**Risen Construct
*****************/

#define spell_arcing_smash 16169
#define spell_thrash 3391
#define spell_frenzy 8269

class mob_risen_construct : public CreatureScript
{
public:
 mob_risen_construct() : CreatureScript("mob_risen_construct") {}
 
 struct mob_risen_constructAI : public ScriptedAI
 {
 mob_risen_constructAI(Creature *c): ScriptedAI(c) {}
 
 uint32 arcing_smash;
 uint32 thrash;
 
 bool frenzy;
 
 void Reset()
 { 
    arcing_smash = urand(6000, 8000);
	thrash = 10000;
	
	frenzy = false;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(arcing_smash<= diff)
 {
    DoCast(me->getVictim(), spell_arcing_smash);
    arcing_smash = urand(6000, 8000);
 }else arcing_smash -= diff;
 
 if(thrash <= diff)
 {
    DoCast(me, spell_thrash);
	thrash = 10000;
 }else thrash -= diff;

 if (!frenzy && !HealthAbovePct(25))
       {
            DoCast(me, spell_frenzy);
            frenzy = true;
       } 
 
    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_risen_constructAI(pCreature);
 }
 
 };
 
/****************
**Risen Protector
*****************/

#define spell_shadow_shock 17439
#define spell_shadow_word_pain 15654
#define spell_silence 6726

class mob_risen_protector : public CreatureScript
{
public:
 mob_risen_protector() : CreatureScript("mob_risen_protector") {}
 
 struct mob_risen_protectorAI : public ScriptedAI
 {
 mob_risen_protectorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shadow_shock;
 uint32 shadow_word_pain;
 uint32 silence;
 
 void Reset()
 { 
    shadow_shock = 5000;
	shadow_word_pain = 10000;
	silence = 8000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shadow_shock<= diff)
 {
    DoCast(me->getVictim(), spell_shadow_shock);
    shadow_shock = 5000 + rand()%8000;
 }else shadow_shock -= diff;
 
 if(shadow_word_pain<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_shadow_word_pain);
       shadow_word_pain = 10000;
 } else shadow_word_pain -= diff;
 
 if (silence <= diff)
 {
    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
	    DoCast(target, spell_silence);
	    silence = 8000;
 }else silence -= diff;
 
    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_risen_protectorAI(pCreature);
 }
 
 };
 
/**************
**Risen Warrior
***************/

#define spell_knockdown 11428
#define spell_rend 16509
#define spell_strike 14516
#define spell_thunderclap 15588

class mob_risen_warrior : public CreatureScript
{
public:
 mob_risen_warrior() : CreatureScript("mob_risen_warrior") {}
 
 struct mob_risen_warriorAI : public ScriptedAI
 {
 mob_risen_warriorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 knockdown;
 uint32 rend;
 uint32 strike;
 uint32 thunderclap;
 
 void Reset()
 { 
    knockdown = 20000;
	rend = 10000;
	strike = 5000;
	thunderclap = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(knockdown<= diff)
 {
    DoCast(me->getVictim(), spell_knockdown);
    knockdown = 20000;
 }else knockdown -= diff;
 
 if(rend<= diff)
 {
    DoCast(me->getVictim(), spell_rend);
    rend = 10000;
 }else rend -= diff;
 
 if(strike<= diff)
 {
    DoCast(me->getVictim(), spell_strike);
    strike = 5000;
 }else strike -= diff;
 
 if(thunderclap <= diff)
 {
    DoCast(spell_thunderclap);
	thunderclap = 15000;
 }
 
    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_risen_warriorAI(pCreature);
 }
 
 };
 
/******************
**Scholomance Adept
*******************/

#define spell_cone_of_cold 15244
#define spell_frost_shock 15499
#define spell_frostbolt 15043

class mob_scholomance_adept : public CreatureScript
{
public:
 mob_scholomance_adept() : CreatureScript("mob_scholomance_adept") {}
 
 struct mob_scholomance_adeptAI : public ScriptedAI
 {
 mob_scholomance_adeptAI(Creature *c): ScriptedAI(c) {}
 
 uint32 cone_of_cold;
 uint32 frost_shock;
 uint32 frostbolt;
 
 void Reset()
 { 
    cone_of_cold = 15000;
	frost_shock = 9000;
	frostbolt = 5000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(cone_of_cold<= diff)
 {
    DoCast(me->getVictim(), spell_cone_of_cold);
    cone_of_cold = 15000;
 }else cone_of_cold -= diff;
 
 if(frost_shock<= diff)
 {
    DoCast(me->getVictim(), spell_frost_shock);
    frost_shock = 9000 + rand()%15000;
 }else frost_shock -= diff;
 
 if(frostbolt<= diff)
 {
    DoCast(me->getVictim(), spell_frostbolt);
    frostbolt = 5000 + rand()%8000;
 }else frostbolt -= diff;
 
 
    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_adeptAI(pCreature);
 }
 
 };
 
/**************************
**Scholomance Dark Summoner
***************************/

#define spell_curse_of_blood 12279
#define spell_drain_life 17620
#define spell_summon_risen_lackey 17618

class mob_scholomance_dark_summoner : public CreatureScript
{
public:
 mob_scholomance_dark_summoner() : CreatureScript("mob_scholomance_dark_summoner") {}
 
 struct mob_scholomance_dark_summonerAI : public ScriptedAI
 {
 mob_scholomance_dark_summonerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 curse_of_blood;
 uint32 drain_life;
 
 void EnterCombat(Unit* pWho)
 {
   DoCast(spell_summon_risen_lackey);
 } 

 void Reset()
 { 
    curse_of_blood = 15000;
	drain_life = 9000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(curse_of_blood<= diff)
 {
    DoCast(me->getVictim(), spell_curse_of_blood);
    curse_of_blood = 15000;
 }else curse_of_blood -= diff;
 
 if (!HealthAbovePct(50) && !me->IsNonMeleeSpellCasted(false) && drain_life <= diff)
       {
            DoCast(me->getVictim(), spell_drain_life);
            drain_life = 9000;
       } else drain_life -= diff;
 
    DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_dark_summonerAI(pCreature);
 }
 
 };
 
/********************
**Scholomance Handler
*********************/

#define spell_arcane_blast 10833
#define spell_blast_wave 17145
#define spell_cone_of_cold 15244

class mob_scholomance_handler : public CreatureScript
{
public:
 mob_scholomance_handler() : CreatureScript("mob_scholomance_handler") {}
 
 struct mob_scholomance_handlerAI : public ScriptedAI
 {
 mob_scholomance_handlerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 arcane_blast;
 uint32 blast_wave;
 uint32 cone_of_cold;
 
  void Reset()
 { 
    arcane_blast = 12000;
	blast_wave = 15000;
	cone_of_cold = 20000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(arcane_blast<= diff)
 {
    DoCast(me->getVictim(), spell_arcane_blast);
    arcane_blast = 12000;
 }else arcane_blast -= diff;
 
 if(blast_wave <= diff)
 {
    DoCast(spell_blast_wave);
	blast_wave = 15000;
 }else blast_wave -= diff;
 
 if(cone_of_cold<= diff)
 {
    DoCast(me->getVictim(), spell_cone_of_cold);
    cone_of_cold = 20000;
 }else cone_of_cold -= diff;
 
     DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_handlerAI(pCreature);
 }
 
 };
 
/************************
**Scholomance Necromancer
*************************/

#define spell_call_of_the_grave 12020
#define spell_shadow_bolt_volley 14887

class mob_scholomance_necromancer : public CreatureScript
{
public:
 mob_scholomance_necromancer() : CreatureScript("mob_scholomance_necromancer") {}
 
 struct mob_scholomance_necromancerAI : public ScriptedAI
 {
 mob_scholomance_necromancerAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shadow_bolt_volley;
 
 void EnterCombat(Unit* pWho)
 {
   DoCast(me, spell_call_of_the_grave);
 }
 
 void Reset()
 { 
    shadow_bolt_volley = 10000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shadow_bolt_volley<= diff)
 {
    DoCast(spell_shadow_bolt_volley);
	shadow_bolt_volley = 10000;
 }else shadow_bolt_volley -= diff;
 
     DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_necromancerAI(pCreature);
 }
 
 };
 
/**********************
**Scholomance Occultist
***********************/

#define spell_bone_armor 80850
#define spell_counterspell 15122
#define spell_drain_mana 17682
#define spell_shadow_bolt_volley 17228

class mob_scholomance_occultist : public CreatureScript
{
public:
 mob_scholomance_occultist() : CreatureScript("mob_scholomance_occultist") {}
 
 struct mob_scholomance_occultistAI : public ScriptedAI
 {
 mob_scholomance_occultistAI(Creature *c): ScriptedAI(c) {}
 
 uint32 shadow_bolt_volley;
 uint32 drain_mana;
 uint32 counterspell;
 
 void EnterCombat(Unit* pWho)
 {
   DoCast(me, spell_bone_armor);
 }
 
 void Reset()
 { 
    shadow_bolt_volley = 10000;
	counterspell = 15000;
	drain_mana = 25000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(shadow_bolt_volley<= diff)
 {
    DoCast(spell_shadow_bolt_volley);
	shadow_bolt_volley = 10000;
 }else shadow_bolt_volley -= diff;
 
 if (counterspell <= diff)
 {
    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
	    DoCast(target, spell_counterspell);
	    counterspell = 15000;
 }else counterspell -= diff;
 
 if (counterspell <= diff)
 {
    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, -5.0f, true))
	    DoCast(target, spell_drain_mana);
	    drain_mana = 25000;
 }else drain_mana -= diff;
 
     DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_scholomance_occultistAI(pCreature);
 }
 
 };
 
/********************
**Spectral Researcher
*********************/

#define spell_wail_of_souls 17631

class mob_spectral_researcher : public CreatureScript
{
public:
 mob_spectral_researcher() : CreatureScript("mob_spectral_researcher") {}
 
 struct mob_spectral_researcherAI : public ScriptedAI
 {
 mob_spectral_researcherAI(Creature *c): ScriptedAI(c) {}
 
 uint32 wail_of_souls;
 
 void Reset()
 { 
    wail_of_souls = 15000;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(wail_of_souls <= diff)
 {
    DoCast(spell_wail_of_souls);
	wail_of_souls = 15000;
 }else wail_of_souls -= diff;
 
     DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_spectral_researcherAI(pCreature);
 }
 
 };
 
/***************
**Spectral Tutor
****************/

#define spell_image_projection  17651
#define spell_silence 12528

class mob_spectral_tutor : public CreatureScript
{
public:
 mob_spectral_tutor() : CreatureScript("mob_spectral_tutor") {}
 
 struct mob_spectral_tutorAI : public ScriptedAI
 {
 mob_spectral_tutorAI(Creature *c): ScriptedAI(c) {}
 
 uint32 silence;
 
 bool projection;
 
 void Reset()
 { 
    silence = 10000;
	
	projection = false;
 }
 
 void UpdateAI(const uint32 diff)
 {
 if (!UpdateVictim())
 return;
 
 if(silence<= diff)
 {
   if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
       DoCast(pTarget, spell_silence);
       silence = 10000;
 } else silence -= diff;
 
 if (!projection && !HealthAbovePct(50))
       {
            DoCast(me, spell_image_projection);
            projection = true;
       }
	
     DoMeleeAttackIfReady();
 }
 
 };
 
 CreatureAI* GetAI(Creature* pCreature) const
 {
 return new mob_spectral_tutorAI(pCreature);
 }
 
 };	
  
void AddSC_mob_trash_scholomance()
{
   new mob_risen_aberration();
   new mob_unstable_corpse();
   new mob_plagued_hatchling();
   new mob_reanimated_corpse();
   new mob_diseased_ghoul();
   new mob_scholomance_acolyte();
   new mob_scholomance_necrolyte();
   new mob_scholomance_neophyte();
   new mob_risen_bonewarder();
   new mob_risen_guard();
   new mob_risen_guardian();
   new mob_necrofiend();
   new mob_risen_construct();
   new mob_risen_protector();
   new mob_risen_warrior();
   new mob_scholomance_adept();
   new mob_scholomance_dark_summoner();
   new mob_scholomance_handler();
   new mob_scholomance_necromancer();
   new mob_scholomance_occultist();
   new mob_spectral_researcher();
   new mob_spectral_tutor();
}
 
 
 
 
 
    
 
 



 
 