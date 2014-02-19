/*
* Copyright (C) 2011-2012 TBEmu <http://www.trueblood-servers.com/>
* By Asardial
*/

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"

// Mastery Basy + Point All Class

// Warrior
// 76856 Unshackled Fury
/*class spell_war_unshackled_fury : public SpellScriptLoader
{
public:
    spell_war_unshackled_fury() : SpellScriptLoader("spell_war_unshackled_fury") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_2, 560);
        return script;
    }
};

// 76857 Critical Block
class spell_war_critical_block : public SpellScriptLoader
{
public:
    spell_war_critical_block() : SpellScriptLoader("spell_war_critical_block") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_MOD_BLOCK_CRIT_CHANCE);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_MOD_BLOCK_PERCENT);
        script->SetMasteryBaseAmount(EFFECT_2, 150);
        return script;
    }
};

// Mage
// 76595 Flashburn
class spell_mage_flashburn : public SpellScriptLoader
{
public:
    spell_mage_flashburn() : SpellScriptLoader("spell_mage_flashburn") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_1, 280);
        return script;
    }
};

// Chaman
// 77223 Enhanced Elements
class spell_sha_enhanced_elements : public SpellScriptLoader
{
public:
    spell_sha_enhanced_elements() : SpellScriptLoader("spell_sha_enhanced_elements") { }

    AuraScript *GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
        script->SetMasteryBaseAmount(EFFECT_1, 250);
        return script;
    }
};

// Hunter
// 76657 Master of Beasts
class spell_hun_master_of_beasts : public SpellScriptLoader
{
public:
    spell_hun_master_of_beasts() : SpellScriptLoader("spell_hun_master_of_beasts") { }

    AuraScript *GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_1, 170);
        return script;
    }
};

// Rogue
// 76803 Potent Poisons
class spell_rog_potent_poisons : public SpellScriptLoader
{
public:
    spell_rog_potent_poisons() : SpellScriptLoader("spell_rog_potent_poisons") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_2, 350);
        return script;
    }
};

// 76808 Executioner
class spell_rog_executioner : public SpellScriptLoader
{
public:
    spell_rog_executioner() : SpellScriptLoader("spell_rog_executioner") { }

    AuraScript* GetAuraScript() const
    {
        MasteryScript* script = new MasteryScript();
        script->SetMasteryAura(EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_1, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryAura(EFFECT_2, SPELL_AURA_ADD_PCT_MODIFIER);
        script->SetMasteryBaseAmount(EFFECT_0, 250);
        return script;
    }
};*/


void AddSC_mastery_spells()
{
    // Class Mastery
    /*new spell_rog_executioner;
    new spell_rog_potent_poisons;
    new spell_hun_master_of_beasts;
    new spell_sha_enhanced_elements;
    new spell_mage_flashburn;
    new spell_war_unshackled_fury;
    new spell_war_critical_block;*/
}