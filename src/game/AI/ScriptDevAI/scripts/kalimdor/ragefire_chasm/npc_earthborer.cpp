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
    SPELL_EARTHBORER_ACID = 18070,
};

struct npc_earthborerAI : public ScriptedAI
{
    explicit npc_earthborerAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiEarthborerAcidTimer;

    void Reset() override
    {
        m_uiEarthborerAcidTimer = urand(0, 500);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
        {
            return;
        }

        if (m_uiEarthborerAcidTimer < uiDiff)
        {
            if (m_creature->GetVictim()->GetAuraCount(SPELL_EARTHBORER_ACID) < 5 || m_creature->GetVictim()->GetSpellAuraHolder(SPELL_EARTHBORER_ACID)->GetAuraDuration() < 5000)
            {
                if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_EARTHBORER_ACID) == CAST_OK)
                {
                    m_uiEarthborerAcidTimer = 1500;
                }
            }
        }
        else
        {
            m_uiEarthborerAcidTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

static UnitAI* GetAI_npc_earthborer(Creature* pCreature)
{
    return new npc_earthborerAI(pCreature);
}

void AddSC_npc_earthborer()
{
    auto* pNewScript = new Script;
    pNewScript->Name = "npc_earthborer";
    pNewScript->GetAI = &GetAI_npc_earthborer;
    pNewScript->RegisterSelf(false);
}
