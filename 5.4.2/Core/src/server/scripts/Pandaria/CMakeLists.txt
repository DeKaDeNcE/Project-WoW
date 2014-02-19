# Copyright (C) 2010-2014 RiseOfPandaria <http://www.riseofpandaria-forums.com/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Pandaria/GateSettingSun/boss_commander_rimok.cpp
  Pandaria/GateSettingSun/boss_raigonn.cpp
  Pandaria/GateSettingSun/boss_saboteur_kiptilak.cpp
  Pandaria/GateSettingSun/boss_striker_gadok.cpp
  Pandaria/GateSettingSun/gate_setting_sun.h
  Pandaria/GateSettingSun/instance_gate_setting_sun.cpp
  
  Pandaria/HeartofFear/boss_ambershaper_unsok.cpp
  Pandaria/HeartofFear/boss_blade_lord_tayak.cpp
  Pandaria/HeartofFear/boss_garalon.cpp
  Pandaria/HeartofFear/boss_grand_empress_shekzeer.cpp
  Pandaria/HeartofFear/boss_imperial_vizier_zorlok.cpp
  Pandaria/HeartofFear/boss_wind_lord_meljarak.cpp
  Pandaria/HeartofFear/heart_of_fear.h
  Pandaria/HeartofFear/instance_heart_of_fear.cpp
  
  Pandaria/MoguShanPalace/boss_gekkan.cpp
  Pandaria/MoguShanPalace/boss_xin_the_weaponmaster.cpp
  Pandaria/MoguShanPalace/instance_mogushan_palace.cpp
  Pandaria/MoguShanPalace/mogushan_palace.h
  Pandaria/MoguShanPalace/trial_of_king.cpp
  
  Pandaria/MogushanVault/boss_elegon.cpp
  Pandaria/MogushanVault/boss_feng.cpp
  Pandaria/MogushanVault/boss_garajal.cpp
  Pandaria/MogushanVault/boss_spirit_kings.cpp
  Pandaria/MogushanVault/boss_stone_guard.cpp
  Pandaria/MogushanVault/boss_will_of_emperor.cpp
  Pandaria/MogushanVault/instance_mogu_shan_vault.cpp
  Pandaria/MogushanVault/mogu_shan_vault.cpp
  Pandaria/MogushanVault/mogu_shan_vault.h
  
  Pandaria/ScarletHalls/boss_armsmaster_harlan.cpp
  Pandaria/ScarletHalls/boss_flameweaver_koegler.cpp
  Pandaria/ScarletHalls/boss_houndmaster_braun.cpp
  Pandaria/ScarletHalls/instance_scarlet_halls.cpp
  Pandaria/ScarletHalls/scarlet_halls.h

  Pandaria/ScarletMonastery/boss_brother_korloff.cpp
  Pandaria/ScarletMonastery/boss_high_inquisitor_whitemane.cpp
  Pandaria/ScarletMonastery/boss_thalnos_the_souldrender.cpp
  Pandaria/ScarletMonastery/instance_scarlet_monastery.cpp
  Pandaria/ScarletMonastery/scarlet_monastery.h

  Pandaria/Scholomance/boss_darkmaster_gandling.cpp
  Pandaria/Scholomance/boss_instructor_chillheart.cpp
  Pandaria/Scholomance/boss_jandice_barov.cpp
  Pandaria/Scholomance/boss_lilian_voss.cpp
  Pandaria/Scholomance/boss_rattlegore.cpp
  Pandaria/Scholomance/instance_scholomance.cpp
  Pandaria/Scholomance/scholomance.h

  Pandaria/ShadoPanMonastery/boss_gu_cloudstrike.cpp
  Pandaria/ShadoPanMonastery/boss_master_snowdrift.cpp
  Pandaria/ShadoPanMonastery/boss_sha_of_violence.cpp
  Pandaria/ShadoPanMonastery/boss_taran_zhu.cpp
  Pandaria/ShadoPanMonastery/instance_shadopan_monastery.cpp
  Pandaria/ShadoPanMonastery/shadopan_monastery.cpp
  Pandaria/ShadoPanMonastery/shadopan_monastery.h

  Pandaria/SiegeNiuzaoTemple/boss_jinbak.cpp
  Pandaria/SiegeNiuzaoTemple/instance_siege_of_the_niuzoa_temple.cpp
  Pandaria/SiegeNiuzaoTemple/siege_of_the_niuzoa_temple.cpp
  Pandaria/SiegeNiuzaoTemple/siege_of_the_niuzoa_temple.h

#  Pandaria/SiegeofOrgrimmar/ - EMPTY

  Pandaria/StormstoutBrewery/boss_ook_ook.cpp
  Pandaria/StormstoutBrewery/instance_stormstout_brewery.cpp
  Pandaria/StormstoutBrewery/stormstout_brewery.cpp
  Pandaria/StormstoutBrewery/stormstout_brewery.h

  Pandaria/TempleJadeSerpent/boss_liu_flameheart.cpp
  Pandaria/TempleJadeSerpent/boss_lorewalker_stonestep.cpp
  Pandaria/TempleJadeSerpent/boss_sha_of_doubt.cpp
  Pandaria/TempleJadeSerpent/boss_wise_mari.cpp
  Pandaria/TempleJadeSerpent/instance_temple_of_jade_serpent.cpp

  Pandaria/TerraceofEndlessSpring/boss_lei_shi.cpp
  Pandaria/TerraceofEndlessSpring/boss_protectors_of_the_endless.cpp
  Pandaria/TerraceofEndlessSpring/boss_sha_of_fear.cpp
  Pandaria/TerraceofEndlessSpring/boss_tsulong.cpp
  Pandaria/TerraceofEndlessSpring/instance_terrace_of_the_endless_spring.cpp
  Pandaria/TerraceofEndlessSpring/terrace_of_the_endless_spring.h

#  Pandaria/ThroneofThunder/ - EMPTY

  Pandaria/WanderingIsland/WanderingIsland_East.cpp
  Pandaria/WanderingIsland/WanderingIsland_North.cpp
  Pandaria/WanderingIsland/WanderingIsland_South.cpp
  Pandaria/WanderingIsland/WanderingIsland_West.cpp
  
  
  Pandaria/townlong_steppes.cpp
  Pandaria/dread_wastes.cpp
  Pandaria/valley_of_the_four_winds.cpp
  Pandaria/krasarang_wilds.cpp
  Pandaria/kun_lai_summit.cpp
  Pandaria/jade_forest.cpp
  Pandaria/vale_of_eternal_blossoms.cpp
  Pandaria/shrine_of_seven_stars.cpp
  Pandaria/shrine_of_two_moons.cpp
  Pandaria/veiled_stair.cpp
	
#  Pandaria/Island/zone_timeless_isle.h
#  Pandaria/Island/zone_isle_of_thunder.h
#  Pandaria/Island/zone_isle_of_giants.h
  Pandaria/Island/zone_isle_of_geants.cpp
  Pandaria/Island/zone_timeless_isle.cpp
  Pandaria/Island/zone_isle_of_thunder.cpp
  Pandaria/Island/zone_wandering_isle.cpp
  
  Pandaria/WorldBoss/worldboss_sha_of_anger.cpp
  Pandaria/WorldBoss/worldboss_galion.cpp
  Pandaria/WorldBoss/worldboss_chiji.cpp
  Pandaria/WorldBoss/worldboss_niuzao.cpp
  Pandaria/WorldBoss/worldboss_ordos.cpp
  Pandaria/WorldBoss/worldboss_xuen.cpp
  Pandaria/WorldBoss/worldboss_yulon.cpp
  Pandaria/WorldBoss/worldboss_oondasta.cpp
  Pandaria/WorldBoss/worldboss_nalak.cpp
)

message("  -> Prepared: Pandaria")
