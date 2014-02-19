/*
* Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "firelands.h"

enum Yells
{
	SAY_AGGRO                                   = -1999971,
};

enum Spells
{
	// Blade Abilities
	SPELL_BLAZE_OF_GLORY						= 99252,
	SPELL_DECIMATION_BLADE						= 99352,
	SPELL_INFERNO_BLADE							= 99350,
};

enum Events
{
	EVENT_HIT_TARGET_WITH_BLADE = 1
};


/**** Baloroc ****/

class boss_baloroc_the_doorkeeper : public CreatureScript
{
public:
	boss_baloroc_the_doorkeeper() : CreatureScript("boss_baloroc_the_doorkeeper"){}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_baloroc_the_doorkeeperAI(creature);
	}

	struct boss_baloroc_the_doorkeeperAI : public BossAI
	{
		boss_baloroc_the_doorkeeperAI(Creature* c) : BossAI(c, DATA_BALOROC)
		{
			instance = me->GetInstanceScript();

			Reset();
		}

		InstanceScript* instance;
		
		void Reset()
		{
			events.Reset();
			_Reset();
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);
			summon->AI()->DoZoneInCombat();
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustReachedHome()
		{
			summons.DespawnAll();
		}

		void JustDied(Unit * /*victim*/)
		{
			summons.DespawnAll();

			_JustDied();
		}

		void EnterCombat(Unit* who)
		{
			events.ScheduleEvent(EVENT_HIT_TARGET_WITH_BLADE, 5000);
			_EnterCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->getVictim() || me->HasUnitState(UNIT_STAT_CASTING))
			{
				return;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_HIT_TARGET_WITH_BLADE:
					
					DoCastVictim(SPELL_INFERNO_BLADE);
					events.ScheduleEvent(EVENT_HIT_TARGET_WITH_BLADE, 5000);
					break;
				
				}

			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();


		}
	};
};


void AddSC_boss_baloroc_the_doorkeeper()
{
	//new boss_baloroc_the_doorkeeper();
}