DELETE FROM `spell_proc_event` WHERE `entry` IN (77794, 77795, 77796);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(77794, 0, 11, 2416967680, 0, 0, 0, 0, 0, 0, 0), -- Focused Insight (Rank 1)
(77795, 0, 11, 2416967680, 0, 0, 0, 0, 0, 0, 0), -- Focused Insight (Rank 2)
(77796, 0, 11, 2416967680, 0, 0, 0, 0, 0, 0, 0); -- Focused Insight (Rank 3)

INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(73681, 0, 0, 0, 0, 0, 0, 65536, 0, 0, 0), -- Unleash Wind (charges consume)
(87935, 0, 0, 4096, 0, 0, 0, 0, 0, 0, 0), -- Serpent Spread (Rank 1)
(87934, 0, 0, 4096, 0, 0, 0, 0, 0, 0, 0); -- Serpent Spread (Rank 2)

