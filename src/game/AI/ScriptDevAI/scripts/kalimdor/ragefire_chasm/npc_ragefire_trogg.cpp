/* This file is part of the WoWClassic Project. See AUTHORS file for Copyright information
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "AI/ScriptDevAI/include/sc_common.h"

enum
{
    SPELL_STRIKE = 11976,
};

struct npc_ragefire_troggAI : public ScriptedAI
{
    explicit npc_ragefire_troggAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiRage;

    void Reset() override
    {
        m_uiRage = 0;
    }

    void DamageDeal(Unit* /*doneTo*/, uint32& damage, DamageEffectType damagetype, SpellEntry const* /*spellInfo*/) override
    {
        if (damage > 0 && damagetype == DIRECT_DAMAGE)
        {
            uint32 level = m_creature->GetLevel();

            float rageconversion = float((0.0091107836 * level * level) + 3.225598133 * level) + 4.2652911f;

            m_uiRage += uint32(float(damage) / rageconversion * 7.5f);
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
        {
            return;
        }

        if (m_uiRage >= 15)
        {
            if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_STRIKE) == CAST_OK)
            {
                m_uiRage -= 15;
            }
        }

        DoMeleeAttackIfReady();
    }
};

static UnitAI* GetAI_npc_ragefire_trogg(Creature* pCreature)
{
    return new npc_ragefire_troggAI(pCreature);
}

void AddSC_npc_ragefire_trogg()
{
    auto* pNewScript = new Script;
    pNewScript->Name = "npc_ragefire_trogg";
    pNewScript->GetAI = &GetAI_npc_ragefire_trogg;
    pNewScript->RegisterSelf(false);
}
