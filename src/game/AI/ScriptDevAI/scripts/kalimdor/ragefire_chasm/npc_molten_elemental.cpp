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
    SPELL_FIRE_SHIELD = 11966,
};

struct npc_molten_elementalAI : public ScriptedAI
{
    explicit npc_molten_elementalAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset() override
    {
        DoCastSpellIfCan(m_creature, SPELL_FIRE_SHIELD, CAST_TRIGGERED | CAST_AURA_NOT_PRESENT);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
        {
            return;
        }

        DoMeleeAttackIfReady();
    }
};

static UnitAI* GetAI_npc_molten_elemental(Creature* pCreature)
{
    return new npc_molten_elementalAI(pCreature);
}

void AddSC_npc_molten_elemental()
{
    auto* pNewScript = new Script;
    pNewScript->Name = "npc_molten_elemental";
    pNewScript->GetAI = &GetAI_npc_molten_elemental;
    pNewScript->RegisterSelf(false);
}
