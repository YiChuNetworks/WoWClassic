UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_molten_elemental' WHERE (`Entry`='11321');
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`='11321');
UPDATE `creature_template_addon` SET `auras`='11966' WHERE (`entry`='11321');
