/*
* Copyright (C) 2011-2012 Project TBEmu <http://www.trueblood-servers.com/>
* By Nizza
*/

#include "ScriptPCH.h"

/***************
**Akumai Servant
****************/
#define spell_frostbolt_volley 8398 // Frostbolt volley
class mob_akumai_servant: public CreatureScript
{
public:
 mob_akumai_servant() : CreatureScript("mob_akumai_servant") {}
 
struct mob_akumai_servantAI : public ScriptedAI
{
        mob_akumai_servantAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 frostbolt_volley;
		
		void Reset()
		{
		        frostbolt_volley = 4000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (frostbolt_volley<= diff)
				{
				        DoCast(me->getVictim(), spell_frostbolt_volley);
						frostbolt_volley = 4000;
				} else frostbolt_volley -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_akumai_servantAI(pCreature);
		}
};


/***************
**Akumai Snapjaw
****************/
#define spell_ravage 8391 // Ravage
class mob_akumai_snapjaw: public CreatureScript
{
public:
 mob_akumai_snapjaw() : CreatureScript("mob_akumai_snapjaw") {}
 
struct mob_akumai_snapjawAI : public ScriptedAI
{
        mob_akumai_snapjawAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 ravage;
		
		void Reset()
		{
		        ravage = 3000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (ravage<= diff)
				{
				        DoCast(me->getVictim(), spell_ravage);
						ravage = 3000;
				} else ravage -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_akumai_snapjawAI(pCreature);
		}
};

/*********************
**Blackfathom Myrmidon
**********************/
#define spell_strike 87081 // Strike
class mob_blackfathom_myrmidon: public CreatureScript
{
public:
 mob_blackfathom_myrmidon() : CreatureScript("mob_blackfathom_myrmidon") {}
 
struct mob_blackfathom_myrmidonAI : public ScriptedAI
{
        mob_blackfathom_myrmidonAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 strike;
		
		void Reset()
		{
		        strike = 3000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (strike<= diff)
				{
				        DoCast(me->getVictim(), spell_strike);
						strike = 3000;
				} else strike -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_blackfathom_myrmidonAI(pCreature);
		}
};

/**********************
**Blackfathom Sea Witch
***********************/
#define spell_blizzard 8364 // Blizzard
#define spell_chilled 6136 // Chilled
#define spell_frost_armor 12544 // Frost Armor
#define spell_frost_nova 15532 // Frost Nova
class mob_blackfathom_sea_witch: public CreatureScript
{
public:
 mob_blackfathom_sea_witch() : CreatureScript("mob_blackfathom_sea_witch") {}
 
struct mob_blackfathom_sea_witchAI : public ScriptedAI
{
        mob_blackfathom_sea_witchAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 blizzard;
		uint32 chilled;
		uint32 frost_armor;
		uint32 frost_nova;
		
		void Reset()
		{
		        blizzard = 8000;
				chilled = 5000;
				frost_armor = 1800;
				frost_nova = 8000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (blizzard<= diff)
				{
				        DoCast(me->getVictim(), spell_blizzard);
						blizzard = 8000;
				} else blizzard -= diff;
				
				if (chilled<= diff)
				{
				        DoCast(me, spell_chilled);
						chilled = 5000;
				} else chilled -= diff;
				
				if (frost_armor<= diff)
				{
				        DoCast(me, spell_frost_armor);
						frost_armor = 1800;
				} else frost_armor -= diff;
				
				if (frost_nova<= diff)
				{
				        DoCast(me->getVictim(), spell_frost_nova);
						frost_nova = 8000;
				} else frost_nova -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_blackfathom_sea_witchAI(pCreature);
		}
};

/***********************
**Blindlight Muckdweller
************************/
#define spell_leech_poison 8382 // Leech Poison
class mob_blindlight_muckdweller: public CreatureScript
{
public:
 mob_blindlight_muckdweller() : CreatureScript("mob_blindlight_muckdweller") {}
 
struct mob_blindlight_muckdwellerAI : public ScriptedAI
{
        mob_blindlight_muckdwellerAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 leech_poison;
		
		void Reset()
		{
		        leech_poison = 15000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (leech_poison<= diff)
				{
				        DoCast(me->getVictim(), spell_leech_poison);
						leech_poison = 15000;
				} else leech_poison -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const 
		{
		        return new mob_blindlight_muckdwellerAI(pCreature);
		}
};

/******************
**Blindlight Murloc
*******************/
#define spell_sunder_armor 11971 // Sunder Armor
class mob_blindlight_murloc: public CreatureScript
{
public:
 mob_blindlight_murloc() : CreatureScript("mob_blindlight_murloc") {}
 
struct mob_blindlight_murlocAI : public ScriptedAI
{
        mob_blindlight_murlocAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 sunder_armor;
		
		void Reset()
		{
		        sunder_armor = 20000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if(!UpdateVictim())
				return;
				
				if (sunder_armor<= diff)
				{
				        DoCast(me->getVictim(), spell_sunder_armor);
						sunder_armor = 20000;
				} else sunder_armor -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const 
		{
		        return new mob_blindlight_murlocAI(pCreature);
		}
};


/******************
**Blindlight Oracle
*******************/
#define spell_lightning_bolt 12167 // Lightning Blot
#define spell_renew 8362 // Renew
class mob_blindlight_oracle: public CreatureScript
{
public:
 mob_blindlight_oracle() : CreatureScript("mob_blindlight_oracle") {}
 
struct mob_blindlight_oracleAI : public ScriptedAI
{
        mob_blindlight_oracleAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 lightning_bolt;
		uint32 renew;
		
		void Reset()
		{
		        lightning_bolt = 3000;
				renew = 15000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (lightning_bolt<= diff)
				{
				        DoCast(me->getVictim(), spell_lightning_bolt);
						lightning_bolt = 3000;
				} else lightning_bolt -= diff;
				
				if (renew<= diff)
				{
				        DoCast(me, spell_renew);
						renew = 15000;
				} else renew -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const 
		{
		        return new mob_blindlight_oracleAI(pCreature);
		}
};

/********************
**Deep Pool Threshfin
*********************/
#define spell_tendon_rip 3604 // Tendon Rip
class mob_deep_pool_threshfin: public CreatureScript
{
public:
 mob_deep_pool_threshfin() : CreatureScript("mob_deep_pool_threshfin") {}
 
struct mob_deep_pool_threshfinAI : public ScriptedAI
{
        mob_deep_pool_threshfinAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 tendon_rip;
		
		void Reset()
		{
		        tendon_rip = 5000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (tendon_rip<= diff)
				{
				        DoCast(me->getVictim(), spell_tendon_rip);
						tendon_rip = 5000;
				} else tendon_rip -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_deep_pool_threshfinAI(pCreature);
		}
};

/**********************
**Fallenroot Hellcaller
***********************/
#define spell_shadow_bolt 12471 // Shadow Bolt
class mob_fallenroot_hellcaller: public CreatureScript
{
public:
 mob_fallenroot_hellcaller() : CreatureScript("mob_fallenroot_hellcaller") {}
 
struct mob_fallenroot_hellcallerAI : public ScriptedAI
{
        mob_fallenroot_hellcallerAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 shadow_bolt;
		
		void Reset()
		{
		        shadow_bolt = 3000;
	    }
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (shadow_bolt<= diff)
				{
				        DoCast(me->getVictim(), spell_shadow_bolt);
						shadow_bolt = 3000;
				} else shadow_bolt -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const 
		{
		        return new mob_fallenroot_hellcallerAI(pCreature);
		}
};

/*************************
**Fallenroot Shadowstalker
**************************/
#define spell_sneak 22766 // Sneak
class mob_fallenroot_shadowstalker: public CreatureScript
{
public:
 mob_fallenroot_shadowstalker() : CreatureScript("mob_fallenroot_shadowstalker") {}
 
struct mob_fallenroot_shadowstalkerAI : public ScriptedAI
{
        mob_fallenroot_shadowstalkerAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 sneak;
		
		void Reset()
		{
		        sneak = 3000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (sneak<= diff)
				{
				        DoCast(me, spell_sneak);
						sneak = 3000;
				} else sneak -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const 
		{
		        return new mob_fallenroot_shadowstalkerAI(pCreature);
		}
};

/*********************
**Murkshallow Snapclaw
**********************/
#define spell_disarm 6713 // Disarm
class mob_murkshallow_snapclaw: public CreatureScript
{
public:
 mob_murkshallow_snapclaw() : CreatureScript("mob_murkshallow_snapclaw") {}
 
struct mob_murkshallow_snapclawAI : public ScriptedAI
{
        mob_murkshallow_snapclawAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 disarm;
		
		void Reset()
		{
		        disarm = 5000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (disarm<= diff)
				{
				        DoCast(me->getVictim(), spell_disarm);
						disarm = 5000;
				} else disarm -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_murkshallow_snapclawAI(pCreature);
		}
};


/*****************
**Twilight Acolyte
******************/
#define spell_renew 8362 // Renew
class mob_twilight_acolyte: public CreatureScript
{
public:
 mob_twilight_acolyte() : CreatureScript("mob_twilight_acolyte") {}
 
struct mob_twilight_acolyteAI : public ScriptedAI
{
        mob_twilight_acolyteAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 renew;
		
		void Reset()
		{
		        renew = 15000;
	    }
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (renew<= diff)
				{
				        DoCast(me, spell_renew);
						renew = 15000;
				} else renew -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_twilight_acolyteAI(pCreature);
		}
};

/********************
**Twilight Aquamancer
*********************/
#define spell_frostbolt 9672 // Frostbolt
#define spell_summon_aqua_guardian 8372 // Summon aqua guardian
class mob_twilight_aquamancer: public CreatureScript
{
public:
 mob_twilight_aquamancer() : CreatureScript("mob_twilight_aquamancer") {}
 
struct mob_twilight_aquamancerAI : public ScriptedAI
{
        mob_twilight_aquamancerAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 frostbolt;
		uint32 summon_aqua_guardian;
		
		void Reset()
		{
		        frostbolt = 4000;
				summon_aqua_guardian = 8000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (frostbolt<= diff)
				{
				        DoCast(me->getVictim(), spell_frostbolt);
						frostbolt = 4000;
				} else frostbolt -= diff;
				
				if (summon_aqua_guardian<= diff)
				{
				        DoCast(me, spell_summon_aqua_guardian);
						summon_aqua_guardian = 8000;
				} else summon_aqua_guardian -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_twilight_aquamancerAI(pCreature);
		}
};

/**********************
**Twilight Elementalist
***********************/
#define spell_earth_shock 13281 // Earth Shock
#define spell_flame_shock 15039 // Flame Shock
#define spell_frost_shock 12548 // Frost Shock
#define spell_shock 11824 // Shock
class mob_twilight_elementalist: public CreatureScript
{
public:
 mob_twilight_elementalist() : CreatureScript("mob_twilight_elementalist") {}
 
struct mob_twilight_elementalistAI : public ScriptedAI
{
        mob_twilight_elementalistAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 earth_shock;
		uint32 flame_shock;
		uint32 frost_shock;
		uint32 shock;
		
		void Reset()
		{
		        earth_shock = 8000;
				flame_shock = 12000;
				frost_shock = 8000;
				shock = 3000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (earth_shock<= diff)
				{
				        DoCast(me->getVictim(), spell_earth_shock);
						earth_shock = 8000;
				} else earth_shock -= diff;
				
				if (flame_shock<= diff)
				{
				        DoCast(me->getVictim(), spell_flame_shock);
						flame_shock = 12000;
				} else flame_shock -= diff;
				
				if (frost_shock<= diff)
				{
				        DoCast(me->getVictim(), spell_frost_shock);
						frost_shock = 8000;
				} else frost_shock -= diff;
				
				if (shock<= diff)
				{
				        DoCast(me->getVictim() , spell_shock);
						shock = 3000;
				} else shock -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_twilight_elementalistAI(pCreature);
		}
};

/********************
**Twilight Loreseeker
*********************/
#define spell_enlarge 8365 // Enlarge
#define spell_slow 25603 // Slow
class mob_twilight_loreseeker: public CreatureScript
{
public:
 mob_twilight_loreseeker() : CreatureScript ("mob_twilight_loreseeker") {}
 
struct mob_twilight_loreseekerAI : public ScriptedAI
{
        mob_twilight_loreseekerAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 enlarge;
		uint32 slow;
		
		void Reset ()
		{
		        enlarge = 10000;
				slow = 5000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (enlarge<= diff)
				{
				        DoCast(me, spell_enlarge);
						enlarge = 10000;
				} else enlarge -= diff;
				
				if (slow<= diff)
				{
				        DoCast(me->getVictim(), spell_slow);
						slow = 5000;
				} else slow -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_twilight_loreseekerAI(pCreature);
	    }
};

/****************
**Twilight Reaver
*****************/
#define spell_arcing_smash 8374 // Arcing Smash
class mob_twilight_reaver: public CreatureScript
{
public:
 mob_twilight_reaver() : CreatureScript("mob_twilight_reaver") {}
 
struct mob_twilight_reaverAI : public ScriptedAI
{
        mob_twilight_reaverAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 arcing_smash;
		
		void Reset()
		{
		        arcing_smash = 3000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if(!UpdateVictim())
				return;
				
				if (arcing_smash<= diff)
				{
				        DoCast(me->getVictim(), spell_arcing_smash);
						arcing_smash = 3000;
			    } else arcing_smash -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_twilight_reaverAI(pCreature);
		}
};

/********************
**Twilight Shadowmage
*********************/
#define spell_dominate_mind 15859 // Dominate Mind
#define spell_shadow_bolt 12471 // Shadow Bolt
#define spell_summon_voidwalker 12746 // Summon Voidwalker
class mob_twilight_shadowmage: public CreatureScript
{
public:
 mob_twilight_shadowmage() : CreatureScript("mob_twilight_shadowmage") {}
 
struct mob_twilight_shadowmageAI : public ScriptedAI
{
        mob_twilight_shadowmageAI(Creature *c) : ScriptedAI(c) {}
		
		uint32 dominate_mind;
		uint32 shadow_bolt;
		uint32 summon_voidwalker;
		
		void Reset()
		{
		        dominate_mind = 5000;
				shadow_bolt = 3000;
				summon_voidwalker = 3000;
		}
		
		void UpdateAI(const uint32 diff)
		{
		        if (!UpdateVictim())
				return;
				
				if (dominate_mind<= diff)
				{
				        DoCast(me->getVictim(), spell_dominate_mind);
						dominate_mind = 5000;
				} else dominate_mind -= diff;
				
				if (shadow_bolt<= diff)
				{
				        DoCast(me->getVictim(), spell_shadow_bolt);
						shadow_bolt = 3000;
			    } else shadow_bolt -= diff;
				
				if (summon_voidwalker<= diff)
				{
				        DoCast(me, spell_summon_voidwalker);
						summon_voidwalker = 3000;
				} else summon_voidwalker -= diff;
				
				DoMeleeAttackIfReady();
		}
};

        CreatureAI* GetAI(Creature* pCreature) const
		{
		        return new mob_twilight_shadowmageAI(pCreature);
		}
};

void AddSC_mob_profondeur_de_brassenoire()
{
new mob_akumai_servant();
new mob_akumai_snapjaw();
new mob_blackfathom_myrmidon();
new mob_blackfathom_sea_witch();
new mob_blindlight_muckdweller();
new mob_blindlight_murloc();
new mob_blindlight_oracle();
new mob_deep_pool_threshfin();
new mob_fallenroot_hellcaller();
new mob_fallenroot_shadowstalker();
new mob_murkshallow_snapclaw();
new mob_twilight_acolyte();
new mob_twilight_aquamancer();
new mob_twilight_elementalist();
new mob_twilight_loreseeker();
new mob_twilight_reaver();
new mob_twilight_shadowmage();
}