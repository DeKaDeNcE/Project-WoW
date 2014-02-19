-- Heroic: Sinestra title fix
DELETE FROM achievement_reward WHERE entry = 5121;
INSERT INTO `achievement_reward` (`entry`, `title_A`, `title_H`, `item`, `sender`, `subject`, `text`) VALUES
(5121, 228, 228, 0, 0, '', '');
-- Criteria, thanks to Subv
DELETE FROM achievement_criteria_data WHERE criteria_id IN (144412, 15666);
INSERT INTO achievement_criteria_data (criteria_id,type,value1,value2) VALUES
(14412,12,2,0),
(15666,12,3,0);