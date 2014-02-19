/*
* Copyright (C) 2011-2012 ProjectStudioMirage <http://www.studio-mirage.fr/>
* Copyright (C) 2011-2012 https://github.com/Asardial
*/

#include "ScriptPCH.h"
#include "baradin_hold.h"


enum Spells
{
    SPELL_BERSERK = 47008,
    SPELL_FEU_FOCALISER = 96884,
    SPELL_OMBRES_INCENDIAIRES = 96913,
    SPELL_REGARD = 97028,
};

enum Events
{
    EVENT_BERSERK = 1,
    EVENT_FEU_FOCALISER,
    EVENT_OMBRES_INCENDIAIRES,
    EVENT_REGARD1,
    EVENT_REGARD2,
    EVENT_REGARD3,
    EVENT_REGARD4,
};

class boss_occuthar: public CreatureScript
{
    public:
        boss_occuthar() : CreatureScript("boss_occuthar") { }

    struct boss_occutharAI: public BossAI
    {
        boss_occutharAI(Creature* creature) : BossAI(creature, DATA_OCCUTHAR) { }

        uint32 fel_firestorm_casted;

        void Reset()
        {
            _Reset();
            me->RemoveAurasDueToSpell(SPELL_BERSERK);
            events.ScheduleEvent(EVENT_BERSERK, 300 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_FEU_FOCALISER, 18 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_OMBRES_INCENDIAIRES, 10 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_REGARD1, 40 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_REGARD2, 40 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_REGARD3, 40 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_REGARD4, 40 *IN_MILLISECONDS);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;
                
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FEU_FOCALISER:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_FEU_FOCALISER);
                    events.RescheduleEvent(EVENT_FEU_FOCALISER, 16 *IN_MILLISECONDS);
                    return;
                case EVENT_OMBRES_INCENDIAIRES:
                    DoCast(me->getVictim(), SPELL_OMBRES_INCENDIAIRES);
                    events.RescheduleEvent(EVENT_OMBRES_INCENDIAIRES, 24 *IN_MILLISECONDS);
                    return;
                case EVENT_REGARD1:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_REGARD);
                    events.RescheduleEvent(EVENT_REGARD1, 57.5 *IN_MILLISECONDS);
                    return;
                case EVENT_REGARD2:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_REGARD);
                    events.RescheduleEvent(EVENT_REGARD2, 57.5 *IN_MILLISECONDS);
                    return;
                case EVENT_REGARD3:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_REGARD);
                    events.RescheduleEvent(EVENT_REGARD3, 57.5 *IN_MILLISECONDS);
                    return;
                case EVENT_REGARD4:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_REGARD);
                    events.RescheduleEvent(EVENT_REGARD4, 57.5 *IN_MILLISECONDS);
                    return;
                case EVENT_BERSERK:
                    DoCast(me, SPELL_BERSERK);
                    return;
                }
            }

            DoMeleeAttackIfReady();
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_occutharAI(creature);
    }
};


void AddSC_boss_occuthar()
{
    new boss_occuthar();
}