-- Ferocious inspiration
INSERT INTO `spell_pet_auras` (`spell`, `aura`) VALUES (34460, 75447);
-- Spirit Bond
INSERT INTO `spell_pet_auras` (`spell`, `aura`) VALUES (19578, 19579);
INSERT INTO `spell_pet_auras` (`spell`, `aura`) VALUES (20895, 24529);
-- Cobra Strikes Proc Chance & to only proc from arcane shot.
DELETE FROM `spell_proc_event` WHERE `entry` IN (53256);
INSERT INTO `spell_proc_event` VALUES (53256, 0x00, 0x09, 0x00020800, 0x00000000, 0x00000000, 0x00000100, 0x00000000, 0, 5, 0);
DELETE FROM `spell_proc_event` WHERE `entry` IN (53259);
INSERT INTO `spell_proc_event` VALUES (53259, 0x00, 0x09, 0x00020800, 0x00000000, 0x00000000, 0x00000100, 0x00000000, 0, 10, 0);
DELETE FROM `spell_proc_event` WHERE `entry` IN (53260);
INSERT INTO `spell_proc_event` VALUES (53260, 0x00, 0x09, 0x00020800, 0x00000000, 0x00000000, 0x00000100, 0x00000000, 0, 15, 0);
-- Glyph of Aimed Shot( earlier with this glyph, you were gaining +5 focus on every attack)
DELETE FROM `spell_proc_event` WHERE `entry` IN (56824);
INSERT INTO `spell_proc_event` VALUES (56824, 0x00, 0x09, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0, 100, 0);
-- Master Marksman - the Proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (34485);
INSERT INTO `spell_proc_event` VALUES (34485, 0x00, 0x09, 0x00000000, 0x00000001, 0x00000000, 0x00000100, 0x00000000, 0, 20, 0);
DELETE FROM `spell_proc_event` WHERE `entry` IN (34486);
INSERT INTO `spell_proc_event` VALUES (34486, 0x00, 0x09, 0x00000000, 0x00000001, 0x00000000, 0x00000100, 0x00000000, 0, 40, 0);
DELETE FROM `spell_proc_event` WHERE `entry` IN (34487);
INSERT INTO `spell_proc_event` VALUES (34487, 0x00, 0x09, 0x00000000, 0x00000001, 0x00000000, 0x00000100, 0x00000000, 0, 60, 0);
-- sic 'em proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (83340);
INSERT INTO `spell_proc_event` VALUES (83340, 0x00, 0x09, 0x00020800, 0x80000000, 0x00000000, 0x00041100, 0x00000002, 0, 100, 0);
DELETE FROM `spell_proc_event` WHERE `entry` IN (83356);
INSERT INTO `spell_proc_event` VALUES (83356, 0x00, 0x09, 0x00020800, 0x80000000, 0x00000000, 0x00041100, 0x00000002, 0, 100, 0);
