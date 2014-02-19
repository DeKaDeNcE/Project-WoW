-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `locales_gameobject`
	ADD COLUMN `name_loc9` VARCHAR(100) NOT NULL DEFAULT '' AFTER `name_loc8`,
	ADD COLUMN `name_loc10` VARCHAR(100) NOT NULL DEFAULT '' AFTER `name_loc9`,
	ADD COLUMN `name_loc11` VARCHAR(100) NOT NULL DEFAULT '' AFTER `name_loc10`,
	ADD COLUMN `castbarcaption_loc9` VARCHAR(100) NOT NULL DEFAULT '' AFTER `castbarcaption_loc8`,
	ADD COLUMN `castbarcaption_loc10` VARCHAR(100) NOT NULL DEFAULT '' AFTER `castbarcaption_loc9`,
	ADD COLUMN `castbarcaption_loc11` VARCHAR(100) NOT NULL DEFAULT '' AFTER `castbarcaption_loc10`;-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `locales_gossip_menu_option`
	ADD COLUMN `option_text_loc9` TEXT NULL AFTER `option_text_loc8`,
	ADD COLUMN `option_text_loc10` TEXT NULL AFTER `option_text_loc9`,
	ADD COLUMN `option_text_loc11` TEXT NULL AFTER `option_text_loc10`,
	ADD COLUMN `box_text_loc9` TEXT NULL AFTER `box_text_loc8`,
	ADD COLUMN `box_text_loc10` TEXT NULL AFTER `box_text_loc9`,
	ADD COLUMN `box_text_loc11` TEXT NULL AFTER `box_text_loc10`;-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `locales_item`
	ADD COLUMN `name_loc9` VARCHAR(100) NOT NULL DEFAULT '' AFTER `name_loc8`,
	ADD COLUMN `name_loc10` VARCHAR(100) NOT NULL DEFAULT '' AFTER `name_loc9`,
	ADD COLUMN `name_loc11` VARCHAR(100) NOT NULL DEFAULT '' AFTER `name_loc10`,
	ADD COLUMN `description_loc9` VARCHAR(255) NULL DEFAULT NULL AFTER `description_loc8`,
	ADD COLUMN `description_loc10` VARCHAR(255) NULL DEFAULT NULL AFTER `description_loc9`,
	ADD COLUMN `description_loc11` VARCHAR(255) NULL DEFAULT NULL AFTER `description_loc10`;-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `locales_npc_text`
	ADD COLUMN `Text0_0_loc9` LONGTEXT NULL AFTER `Text0_0_loc8`,
	ADD COLUMN `Text0_0_loc10` LONGTEXT NULL AFTER `Text0_0_loc9`,
	ADD COLUMN `Text0_0_loc11` LONGTEXT NULL AFTER `Text0_0_loc10`,
	ADD COLUMN `Text0_1_loc9` LONGTEXT NULL AFTER `Text0_1_loc8`,
	ADD COLUMN `Text0_1_loc10` LONGTEXT NULL AFTER `Text0_1_loc9`,
	ADD COLUMN `Text0_1_loc11` LONGTEXT NULL AFTER `Text0_1_loc10`,
	ADD COLUMN `Text1_0_loc9` LONGTEXT NULL AFTER `Text1_0_loc8`,
	ADD COLUMN `Text1_0_loc10` LONGTEXT NULL AFTER `Text1_0_loc9`,
	ADD COLUMN `Text1_0_loc11` LONGTEXT NULL AFTER `Text1_0_loc10`,
	ADD COLUMN `Text1_1_loc9` LONGTEXT NULL AFTER `Text1_1_loc8`,
	ADD COLUMN `Text1_1_loc10` LONGTEXT NULL AFTER `Text1_1_loc9`,
	ADD COLUMN `Text1_1_loc11` LONGTEXT NULL AFTER `Text1_1_loc10`,
	ADD COLUMN `Text2_0_loc9` LONGTEXT NULL AFTER `Text2_0_loc8`,
	ADD COLUMN `Text2_0_loc10` LONGTEXT NULL AFTER `Text2_0_loc9`,
	ADD COLUMN `Text2_0_loc11` LONGTEXT NULL AFTER `Text2_0_loc10`,
	ADD COLUMN `Text2_1_loc9` LONGTEXT NULL AFTER `Text2_1_loc8`,
	ADD COLUMN `Text2_1_loc10` LONGTEXT NULL AFTER `Text2_1_loc9`,
	ADD COLUMN `Text2_1_loc11` LONGTEXT NULL AFTER `Text2_1_loc10`,
	ADD COLUMN `Text3_0_loc9` LONGTEXT NULL AFTER `Text3_0_loc8`,
	ADD COLUMN `Text3_0_loc10` LONGTEXT NULL AFTER `Text3_0_loc9`,
	ADD COLUMN `Text3_0_loc11` LONGTEXT NULL AFTER `Text3_0_loc10`,
	ADD COLUMN `Text3_1_loc9` LONGTEXT NULL AFTER `Text3_1_loc8`,
	ADD COLUMN `Text3_1_loc10` LONGTEXT NULL AFTER `Text3_1_loc9`,
	ADD COLUMN `Text3_1_loc11` LONGTEXT NULL AFTER `Text3_1_loc10`,
	ADD COLUMN `Text4_0_loc9` LONGTEXT NULL AFTER `Text4_0_loc8`,
	ADD COLUMN `Text4_0_loc10` LONGTEXT NULL AFTER `Text4_0_loc9`,
	ADD COLUMN `Text4_0_loc11` LONGTEXT NULL AFTER `Text4_0_loc10`,
	ADD COLUMN `Text4_1_loc9` LONGTEXT NULL AFTER `Text4_1_loc8`,
	ADD COLUMN `Text4_1_loc10` LONGTEXT NULL AFTER `Text4_1_loc9`,
	ADD COLUMN `Text4_1_loc11` LONGTEXT NULL AFTER `Text4_1_loc10`,
	ADD COLUMN `Text5_0_loc9` LONGTEXT NULL AFTER `Text5_0_loc8`,
	ADD COLUMN `Text5_0_loc10` LONGTEXT NULL AFTER `Text5_0_loc9`,
	ADD COLUMN `Text5_0_loc11` LONGTEXT NULL AFTER `Text5_0_loc10`,
	ADD COLUMN `Text5_1_loc9` LONGTEXT NULL AFTER `Text5_1_loc8`,
	ADD COLUMN `Text5_1_loc10` LONGTEXT NULL AFTER `Text5_1_loc9`,
	ADD COLUMN `Text5_1_loc11` LONGTEXT NULL AFTER `Text5_1_loc10`,
	ADD COLUMN `Text6_0_loc9` LONGTEXT NULL AFTER `Text6_0_loc8`,
	ADD COLUMN `Text6_0_loc10` LONGTEXT NULL AFTER `Text6_0_loc9`,
	ADD COLUMN `Text6_0_loc11` LONGTEXT NULL AFTER `Text6_0_loc10`,
	ADD COLUMN `Text6_1_loc9` LONGTEXT NULL AFTER `Text6_1_loc8`,
	ADD COLUMN `Text6_1_loc10` LONGTEXT NULL AFTER `Text6_1_loc9`,
	ADD COLUMN `Text6_1_loc11` LONGTEXT NULL AFTER `Text6_1_loc10`,
	ADD COLUMN `Text7_0_loc9` LONGTEXT NULL AFTER `Text7_0_loc8`,
	ADD COLUMN `Text7_0_loc10` LONGTEXT NULL AFTER `Text7_0_loc9`,
	ADD COLUMN `Text7_0_loc11` LONGTEXT NULL AFTER `Text7_0_loc10`,
	ADD COLUMN `Text7_1_loc9` LONGTEXT NULL AFTER `Text7_1_loc8`,
	ADD COLUMN `Text7_1_loc10` LONGTEXT NULL AFTER `Text7_1_loc9`,
	ADD COLUMN `Text7_1_loc11` LONGTEXT NULL AFTER `Text7_1_loc10`;-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `locales_page_text`
	ADD COLUMN `Text_loc9` LONGTEXT NULL AFTER `Text_loc8`,
	ADD COLUMN `Text_loc10` LONGTEXT NULL AFTER `Text_loc9`,
	ADD COLUMN `Text_loc11` LONGTEXT NULL AFTER `Text_loc10`;-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `locales_points_of_interest`
	ADD COLUMN `icon_name_loc9` TEXT NULL AFTER `icon_name_loc8`,
	ADD COLUMN `icon_name_loc10` TEXT NULL AFTER `icon_name_loc9`,
	ADD COLUMN `icon_name_loc11` TEXT NULL AFTER `icon_name_loc10`;-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `locales_quest`
	ADD COLUMN `Title_loc9` TEXT NULL AFTER `Title_loc8`,
	ADD COLUMN `Title_loc10` TEXT NULL AFTER `Title_loc9`,
	ADD COLUMN `Title_loc11` TEXT NULL AFTER `Title_loc10`,
	ADD COLUMN `Details_loc9` TEXT NULL AFTER `Details_loc8`,
	ADD COLUMN `Details_loc10` TEXT NULL AFTER `Details_loc9`,
	ADD COLUMN `Details_loc11` TEXT NULL AFTER `Details_loc10`,
	ADD COLUMN `Objectives_loc9` TEXT NULL AFTER `Objectives_loc8`,
	ADD COLUMN `Objectives_loc10` TEXT NULL AFTER `Objectives_loc9`,
	ADD COLUMN `Objectives_loc11` TEXT NULL AFTER `Objectives_loc10`,
	ADD COLUMN `OfferRewardText_loc9` TEXT NULL AFTER `OfferRewardText_loc8`,
	ADD COLUMN `OfferRewardText_loc10` TEXT NULL AFTER `OfferRewardText_loc9`,
	ADD COLUMN `OfferRewardText_loc11` TEXT NULL AFTER `OfferRewardText_loc10`,
	ADD COLUMN `RequestItemsText_loc9` TEXT NULL AFTER `RequestItemsText_loc8`,
	ADD COLUMN `RequestItemsText_loc10` TEXT NULL AFTER `RequestItemsText_loc9`,
	ADD COLUMN `RequestItemsText_loc11` TEXT NULL AFTER `RequestItemsText_loc10`,
	ADD COLUMN `EndText_loc9` TEXT NULL AFTER `EndText_loc8`,
	ADD COLUMN `EndText_loc10` TEXT NULL AFTER `EndText_loc9`,
	ADD COLUMN `EndText_loc11` TEXT NULL AFTER `EndText_loc10`,
	ADD COLUMN `CompletedText_loc9` TEXT NULL AFTER `CompletedText_loc8`,
	ADD COLUMN `CompletedText_loc10` TEXT NULL AFTER `CompletedText_loc9`,
	ADD COLUMN `CompletedText_loc11` TEXT NULL AFTER `CompletedText_loc10`,
	ADD COLUMN `ObjectiveText1_loc9` TEXT NULL AFTER `ObjectiveText1_loc8`,
	ADD COLUMN `ObjectiveText1_loc10` TEXT NULL AFTER `ObjectiveText1_loc9`,
	ADD COLUMN `ObjectiveText1_loc11` TEXT NULL AFTER `ObjectiveText1_loc10`,
	ADD COLUMN `ObjectiveText2_loc9` TEXT NULL AFTER `ObjectiveText2_loc8`,
	ADD COLUMN `ObjectiveText2_loc10` TEXT NULL AFTER `ObjectiveText2_loc9`,
	ADD COLUMN `ObjectiveText2_loc11` TEXT NULL AFTER `ObjectiveText2_loc10`,
	ADD COLUMN `ObjectiveText3_loc9` TEXT NULL AFTER `ObjectiveText3_loc8`,
	ADD COLUMN `ObjectiveText3_loc10` TEXT NULL AFTER `ObjectiveText3_loc9`,
	ADD COLUMN `ObjectiveText3_loc11` TEXT NULL AFTER `ObjectiveText3_loc10`,
	ADD COLUMN `ObjectiveText4_loc9` TEXT NULL AFTER `ObjectiveText4_loc8`,
	ADD COLUMN `ObjectiveText4_loc10` TEXT NULL AFTER `ObjectiveText4_loc9`,
	ADD COLUMN `ObjectiveText4_loc11` TEXT NULL AFTER `ObjectiveText4_loc10`,
	ADD COLUMN `QuestGiverTextWindow_loc9` TEXT NULL AFTER `QuestGiverTextWindow_loc8`,
	ADD COLUMN `QuestGiverTextWindow_loc10` TEXT NULL AFTER `QuestGiverTextWindow_loc9`,
	ADD COLUMN `QuestGiverTextWindow_loc11` TEXT NULL AFTER `QuestGiverTextWindow_loc10`,
	ADD COLUMN `QuestGiverTargetName_loc9` TEXT NULL AFTER `QuestGiverTargetName_loc8`,
	ADD COLUMN `QuestGiverTargetName_loc10` TEXT NULL AFTER `QuestGiverTargetName_loc9`,
	ADD COLUMN `QuestGiverTargetName_loc11` TEXT NULL AFTER `QuestGiverTargetName_loc10`,
	ADD COLUMN `QuestTurnTextWindow_loc9` TEXT NULL AFTER `QuestTurnTextWindow_loc8`,
	ADD COLUMN `QuestTurnTextWindow_loc10` TEXT NULL AFTER `QuestTurnTextWindow_loc9`,
	ADD COLUMN `QuestTurnTextWindow_loc11` TEXT NULL AFTER `QuestTurnTextWindow_loc10`,
	ADD COLUMN `QuestTurnTargetName_loc9` TEXT NULL AFTER `QuestTurnTargetName_loc8`,
	ADD COLUMN `QuestTurnTargetName_loc10` TEXT NULL AFTER `QuestTurnTargetName_loc9`,
	ADD COLUMN `QuestTurnTargetName_loc11` TEXT NULL AFTER `QuestTurnTargetName_loc10`;-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `trinity_string`
	ADD COLUMN `content_loc9` TEXT NULL AFTER `content_loc8`,
	ADD COLUMN `content_loc10` TEXT NULL AFTER `content_loc9`,
	ADD COLUMN `content_loc11` TEXT NULL AFTER `content_loc10`;
-- Add Locale 9 = itIT, Locale 10 = ptBR, Locale 11= ptPT
ALTER TABLE `db_script_string`
	ADD COLUMN `content_loc9` TEXT NULL AFTER `content_loc8`,
	ADD COLUMN `content_loc10` TEXT NULL AFTER `content_loc9`,
	ADD COLUMN `content_loc11` TEXT NULL AFTER `content_loc10`;
-- Master Shang Xi
DELETE FROM `creature_template` WHERE `entry` IN (54786);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(54786, 0, 0, 0, 0, 0, 39574, 0, 0, 0, 'Master Shang Xi', '', '', 0, 90, 90, 0, 0, 35, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 0, 33536, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 17688);
-- Master Shang Xi
SET @CGUID :=258000;
DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID, 54786, 860, 1, 1, 960.0434, 3606.05, 196.414, 6.230825, 120, 0, 0);-- Training Target
DELETE FROM `creature_template` WHERE `entry` IN (57873);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(57873, 0, 0, 0, 53714, 0, 38459, 0, 0, 0, 'Training Target', '', '', 0, 1, 1, 0, 0, 7, 7, 0, 1, 1, 1, 5, 0, 0, 0, 0, 1, 2000, 2000, 0, 0, 32768, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 17688);
-- Training Target
SET @CGUID :=258001;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+5;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 57873, 860, 1, 1, 1495.623, 3426.017, 171.0507, 2.844887, 120, 0, 0), -- 57873 (Area: -1)
(@CGUID+1, 57873, 860, 1, 1, 1437.839, 3415.378, 170.9208, 0.4712389, 120, 0, 0), -- 57873 (Area: -1)
(@CGUID+2, 57873, 860, 1, 1, 1490.865, 3444.753, 171.2159, 3.926991, 120, 0, 0), -- 57873 (Area: -1)
(@CGUID+3, 57873, 860, 1, 1, 1455.573, 3444.194, 171.0521, 4.206244, 120, 0, 0), -- 57873 (Area: -1)
(@CGUID+4, 57873, 860, 1, 1, 1455.573, 3444.194, 171.0521, 4.206244, 120, 0, 0), -- 57873 (Area: -1)
(@CGUID+5, 57873, 860, 1, 1, 1455.573, 3444.194, 171.0521, 4.206244, 120, 0, 0); -- 57873 (Area: -1)-- Training Target
DELETE FROM `creature_template` WHERE `entry` IN (53714);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(53714, 0, 0, 0, 0, 0, 38459, 0, 0, 0, 'Training Target', '', '', 0, 1, 1, 0, 0, 7, 7, 0, 1, 1, 1, 5, 0, 0, 0, 0, 1, 2000, 2000, 0, 0, 32768, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 17688);
-- Training Target
SET @CGUID :=258007;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+20;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 53714, 860, 1, 1, 0, 0, 1433.03, 3423.23, 170.991, 0.610865, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+1, 53714, 860, 1, 1, 0, 0, 1434.5, 3420.98, 170.931, 0.610865, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+2, 53714, 860, 1, 1, 0, 0, 1438.95, 3412.89, 170.991, 0.506145, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+3, 53714, 860, 1, 1, 0, 0, 1439.49, 3455.07, 171.113, 3.92699, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+4, 53714, 860, 1, 1, 0, 0, 1441.35, 3453.07, 171.141, 3.90954, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+5, 53714, 860, 1, 1, 0, 0, 1446.66, 3449.3, 171.143, 4.15388, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+6, 53714, 860, 1, 1, 0, 0, 1448.89, 3447.72, 171.188, 4.11898, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+7, 53714, 860, 1, 1, 0, 0, 1453.05, 3445.25, 171.12, 4.20624, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+8, 53714, 860, 1, 1, 0, 0, 1458.93, 3417.62, 171.208, 4.74729, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+9, 53714, 860, 1, 1, 0, 0, 1461.63, 3417.96, 171.225, 4.86947, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+10, 53714, 860, 1, 1, 0, 0, 1465.81, 3422.04, 171.255, 5.58505, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+11, 53714, 860, 1, 1, 0, 0, 1466.32, 3442.13, 171.094, 4.74729, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+12, 53714, 860, 1, 1, 0, 0, 1468.5, 3399.89, 171.056, 1.50098, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+13, 53714, 860, 1, 1, 0, 0, 1469.04, 3442.39, 171.07, 4.71239, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+14, 53714, 860, 1, 1, 0, 0, 1471.21, 3399.65, 171.064, 1.51844, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+15, 53714, 860, 1, 1, 0, 0, 1477.18, 3444.04, 171.053, 5.13127, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+16, 53714, 860, 1, 1, 0, 0, 1480.81, 3448.06, 171.046, 4.79965, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+17, 53714, 860, 1, 1, 0, 0, 1483.52, 3448.32, 171.07, 4.85202, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+18, 53714, 860, 1, 1, 0, 0, 1488.99, 3446.74, 171.122, 3.94444, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+19, 53714, 860, 1, 1, 0, 0, 1492.83, 3416.03, 171.051, 2.68781, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+20, 53714, 860, 1, 1, 0, 0, 1493.68, 3418.64, 171.051, 2.77507, 120, 0, 0, 1, 0, 0, 0, 0, 0);
-- Aspiring Trainee
DELETE FROM `creature_template` WHERE `entry` IN (53565);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(53565, 0, 0, 0, 0, 0, 39887, 39890, 39888, 44073, 'Aspiring Trainee', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 0, 0, 33536, 2048, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 17688);
-- Aspiring Trainee
SET @CGUID :=258028;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+7;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 53565, 860, 1, 1, 1470.851, 3422.725, 171.245, 2.565634, 120, 0, 0), -- 53565 (Area: -1)
(@CGUID+1, 53565, 860, 1, 1, 1427.92, 3446.743, 171.2413, 0.122173, 120, 0, 0), -- 53565 (Area: -1)
(@CGUID+2, 53565, 860, 1, 1, 1424.134, 3447.63, 171.1559, 0.2792527, 120, 0, 0), -- 53565 (Area: -1)
(@CGUID+3, 53565, 860, 1, 1, 1422.655, 3451.949, 171.2222, 0.2443461, 120, 0, 0), -- 53565 (Area: -1)
(@CGUID+4, 53565, 860, 1, 1, 1425.458, 3443.495, 171.1704, 0.2094395, 120, 0, 0), -- 53565 (Area: -1)
(@CGUID+5, 53565, 860, 1, 1, 1440.648, 3417.011, 171.2169, 3.455752, 120, 0, 0), -- 53565 (Area: -1)
(@CGUID+6, 53565, 860, 1, 1, 1484.047, 3402.434, 171.3003, 2.827433, 120, 0, 0), -- 53565 (Area: -1)
(@CGUID+7, 53565, 860, 1, 1, 1482.182, 3400.925, 171.3264, 1.954769, 120, 0, 0); -- 53565 (Area: -1)
