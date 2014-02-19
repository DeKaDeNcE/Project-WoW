/*
* Copyright (C) 2011-2012 ProjectStudioMirage <http://www.studio-mirage.fr/>
* Copyright (C) 2011-2012 https://github.com/Asardial
*/

#include"ScriptPCH.h"
#include"baradin_hold.h"

class instance_baradin_hold: public InstanceMapScript
{
public:
    instance_baradin_hold() : InstanceMapScript("instance_baradin_hold", 757) { }

    InstanceScript* GetInstanceScript(InstanceMap *map) const
    {
        return new instance_baradin_hold_InstanceMapScript(map);
    }

    struct instance_baradin_hold_InstanceMapScript: public InstanceScript
    {
        instance_baradin_hold_InstanceMapScript(InstanceMap *map) : InstanceScript(map)
        {
            SetBossNumber(MAX_ENCOUNTER);
        }

        /*
        void Initialize()
        {
            memset(&guid, 0, sizeof(guid));
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case CREATURE_ARGALOTH: guid[DATA_ARGALOTH] = creature->GetGUID(); break;
            case CREATURE_OCCUTHAR: guid[DATA_OCCUTHAR] = creature->GetGUID(); break;
            }
        }

        uint64 GetData64(uint32 identifier) { return guid[identifier]; }

    private:
        uint64 guid[MAX_ENCOUNTER];
    */
    };
};

void AddSC_instance_baradin_hold()
{
    new instance_baradin_hold();
}