-- MAJ 1
CREATE TABLE IF NOT EXISTS `custom_transmogrification` (
  `GUID` int(10) unsigned NOT NULL DEFAULT '0',
  `FakeEntry` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`GUID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='version 3.0';

-- Maj 2
CREATE TABLE IF NOT EXISTS `custom_transmogrification` (
	`GUID` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`FakeOwner` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`FakeEntry` INT(10) UNSIGNED NOT NULL DEFAULT '0'
)
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB;

REPLACE INTO custom_transmogrification (GUID, FakeOwner, FakeEntry) SELECT guid, FakeOwner, FakeEntry FROM item_instance WHERE FakeOwner != 0 AND FakeEntry != 0;
ALTER TABLE `item_instance`
	DROP COLUMN `FakeEntry`,
	DROP COLUMN `FakeOwner`;

-- Maj 3
ALTER TABLE `custom_transmogrification`
	DROP COLUMN `FakeOwner`;

REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11129, 'You don''t have enough %ss', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

-- Maj 4
SET
@Entry = 190010,
@Name = "Tisse-dimensions Dushar";
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(@Entry, 0, 0, 0, 0, 0, 17647, 0, 0, 0, @Name, 'Transmogrifieur', NULL, 0, 85, 85, 2, 35, 35, 1, 1, 1.14286, 1, 0, 500, 500, 0, 350, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 242434, 0, 2, 'NPC_Transmogrify', 0);

INSERT INTO `creature_equip_template` (`entry` ,`equipentry1` ,`equipentry2` ,`equipentry3`)VALUES ('242434', '61350', '0', '0');

INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(190010, 1, 1, 1, 0, 242434, 16201.1, 16257.2, 21.2523, 6.00139, 300, 0, 0, 7260, 0, 0, 0, 0, 0),
(190010, 1, 1, 1, 0, 242434, 1918.85, -4434.33, 24.788, 1.42898, 300, 0, 0, 7260, 0, 0, 0, 0, 0),
(190010, 0, 1, 1, 0, 242434, -8850.08, 801.308, 96.3345, 3.66109, 300, 0, 0, 7260, 0, 0, 0, 0, 0);

REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11100, 'Transmogrifications removed from equipped items', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11101, 'You have no transmogrified items equipped', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11102, '%s transmogrification removed', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11103, 'No transmogrification on %s slot', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11104, '%s transmogrified', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11105, 'Selected items are not suitable', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11106, 'Selected item does not exist', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11107, 'Equipment slot is empty', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11108, 'Head', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11109, 'Shoulders', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11110, 'Shirt', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11111, 'Chest', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11112, 'Waist', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11113, 'Legs', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11114, 'Feet', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11115, 'Wrists', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11116, 'Hands', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11117, 'Back', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11118, 'Main hand', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11119, 'Off hand', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11120, 'Ranged', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11121, 'Tabard', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11122, 'Back..', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11123, 'Remove all transmogrifications', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11124, 'Remove transmogrifications from all equipped items?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11125, 'Update menu', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11126, 'Remove transmogrification', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11127, 'Remove transmogrification from %s?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11128, 'Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\r\nDo you wish to continue?\r\n\r\n', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
REPLACE INTO `skyfire_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (11129, 'You don''t have enough %ss', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);