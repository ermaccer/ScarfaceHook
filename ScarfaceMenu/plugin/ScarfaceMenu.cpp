#include "ScarfaceMenu.h"
#include "../imgui/imgui.h"
#include "../IniReader.h"
#include "../scarface/Scarface.h"
#include "../utils/MemoryMgr.h"
#include "../eNotifManager.h"
#include "../hooks.h"
#include <iostream>
#include <Windows.h>
#include "../SettingsMgr.h"
#include "../helper/eKeyboardMan.h"
#include "../eDirectX9Hook.h"

std::vector<TeleporterPlace> vTeleports;

bool& gTonyIsInvincible = *(bool*)(0x825CC2);

const char* szVehicles[] =
{
	"AlbatrossTemplate",
	"AmbassadorTemplate",
	"AmbulanceTemplate",
	"AmphibPlaneTemplate",
	"AntiqueRacerTemplate",
	"ArmoredCarTemplate",
	"ArmyHeliTemplate",
	"AttackBoatTemplate",
	"AttackGunBoatTemplate",
	"AttackHeliTemplate",
	"BacinariTemplate",
	"BanditStTemplate",
	"BeaverFloatPlaneTemplate",
	"BodogStampedeTemplate",
	"BulldozerTemplate",
	"BusTemplate",
	"BusV2Template",
	"BusV3Template",
	"BusV4Template",
	"caballoTemplate",
	"cabrioletTemplate",
	"CigaretteBoatTemplate",
	"CigaretteGunBoatTemplate",
	"CoastGuardBoatTemplate",
	"ColombianAttackBoatTemplate",
	"ColumbianCigaretteBoatTemplate",
	"ColumbianMojaveTemplate",
	"ColumbianShagVanTemplate",
	"ContainerTruckTemplate",
	"corfuTemplate",
	"CubeVanTemplate",
	"DEA_vanTemplate",
	"DeaBoatTemplate",
	"DeaTwinEaglePlaneTemplate",
	"delivery_vanTemplate",
	"DiazCaballoTemplate",
	"DiazCigaretteBoatTemplate",
	"DiazLightningTemplate",
	"DiazShagVanTemplate",
	"dump_truckTemplate",
	"EpsilonTemplate",
	"exotic_pumaTemplate",
	"ExoticBanditSTTemplate",
	"ExoticMacaroTemplate",
	"ExoticMontereySharkTemplate",
	"ExoticPickleForkBoatTemplate",
	"ExoticTwinEaglePlaneTemplate",
	"FanBoatTemplate",
	"FelliniTemplate",
	"FlatbedTemplate",
	"fuelTruckTemplate",
	"garbage_truckTemplate",
	"GasparCigaretteBoatTemplate",
	"GasparGsWohlabendTemplate",
	"GasparSantaMonicaTemplate",
	"GasparShagVanTemplate",
	"GenericAttackBoatTemplate",
	"Gpv_offroadTemplate",
	"GsWohlabendTemplate",
	"HippyVanPotheadTemplate",
	"HippyVanTemplate",
	"HueyCgHeliTemplate",
	"Idump_truckTemplate",
	"IFlatbedTemplate",
	"IfuelTruckTemplate",
	"IGpv_offroadTemplate",
	"IHippyVanPotheadTemplate",
	"IJupiterTemplate",
	"IMojaveTemplate",
	"IQMConvertibleTemplate",
	"ISedanTemplate",
	"IslandBoatTemplate",
	"IStationWagonTemplate",
	"ITruckGunTemplate",
	"ITruckTemplate",
	"JetBoatTemplate",
	"JupiterTemplate",
	"konigN29Template",
	"lakotaTemplate",
	"LargeSailboatRigTemplate",
	"LargeSailboatUnRigTemplate",
	"LeDoreanTemplate",
	"lightningTemplate",
	"LimoTemplate",
	"macaroTemplate",
	"mercutioTemplate",
	"MojaveTemplate",
	"MontereySharkTemplate",
	"MountedArmyHeliTemplate",
	"MulletTemplate",
	"NachoCigaretteBoatTemplate",
	"NachoMacaroTemplate",
	"NachoShagVanTemplate",
	"NavyHydroBoatTemplate",
	"Orient380Template",
	"pantherTemplate",
	"PickleForkBoatTemplate",
	"PoliceBoatTemplate",
	"PoliceCarTemplate",
	"PoliceHeliTemplate",
	"PowerBoatTemplate",
	"PTBoatTemplate",
	"pumaTemplate",
	"QMConvertibleTemplate",
	"QMCreampuffTemplate",
	"RacingBoatTemplate",
	"RattlerTemplate",
	"RhinoGunTemplate",
	"RhinoTemplate",
	"SantaMonicaConvTemplate",
	"SantaMonicaTemplate",
	"SedanTemplate",
	"ShagVanTemplate",
	"SportFishingBoatTemplate",
	"StationWagonTemplate",
	"swat_vanTemplate",
	"TArmoredCarTemplate",
	"TBacinariTemplate",
	"TcaballoTemplate",
	"Tdump_truckTemplate",
	"TFelliniTemplate",
	"TGpv_offroadTemplate",
	"TGsWohlabendTemplate",
	"TkonigN29Template",
	"TlakotaTemplate",
	"TlightningTemplate",
	"TLimoTemplate",
	"TMojaveTemplate",
	"TonyCaballoTemplate",
	"TonyCigaretteBoatTemplate",
	"TonyGsWohlabendTemplate",
	"TonyLightningTemplate",
	"TonyMacaroTemplate",
	"TonyMojaveTemplate",
	"TonySantaMonicaTemplate",
	"TonyShagVanTemplate",
	"TOrient380Template",
	"TpantherTemplate",
	"TPoliceCarTemplate",
	"TrickCraftBoatTemplate",
	"TruckGunTemplate",
	"TruckTemplate",
	"WhiskeyGhostTemplate",
	"YachtBoatTemplate",
};

const char* szWeapons[] = {
	"WeaponTemplateMetalPipe",
	"WeaponTemplateMachete",
	"WeaponTemplateChainsaw",
	"WeaponTemplateSuper38",
	"WeaponTemplateColt45",
	"WeaponTemplateColt45Upgrade",
	"WeaponTemplateDesertEagle",
	"WeaponTemplateUzi",
	"WeaponTemplateUziUpgrade",
	"WeaponTemplateUziUpgrade2",
	"WeaponTemplateUziUpgrade3",
	"WeaponTemplateMAC10",
	"WeaponTemplateMAC10Upgrade",
	"WeaponTemplateMAC10Upgrade2",
	"WeaponTemplateMAC10Upgrade3",
	"WeaponTemplateShotgun",
	"WeaponTemplateAK47",
	"WeaponTemplateAK47Upgrade",
	"WeaponTemplateAK47Upgrade2",
	"WeaponTemplateM16",
	"WeaponTemplateM16Upgrade",
	"WeaponTemplateM16Mortar",
	"WeaponTemplateM79",
	"WeaponTemplateSniper",
	"WeaponTemplateBazooka",
	"WeaponTemplateMissileLauncher",
	"WeaponTemplateM240",
};


const char* szCharacters[] = {
	"MCP_ArmyTony",
	"MCP_Assassin",
	"MCP_BlackSuitTony",
	"MCP_BluePinSuitShadesTony",
	"MCP_BluePinSuitTony",
	"MCP_BlueSuitTony",
	"MCP_Driver",
	"MCP_Enforcer",
	"MCP_GraySuitShadesTony",
	"MCP_GraySuitTony",
	"MCP_HawaiianShadesTony",
	"MCP_HawaiianTony",
	"MCP_SandyShadesTony",
	"MCP_SandyTony",
	"MCP_WhiteSuitShadesTony",
	"MCP_WhiteSuitTony",
};

const char* szCutscenes[] = {
	"MNIS_A23_0_Intro_to_Tranq",
	"MNIS_A51a_0_Intro_to_Texanoil",
	"MNIS_A51a_2_Helicopter_Arrives",
	"MNIS_A51a_3_Boats_Arrive",
	"MNIS_A51b_0_Talking_to_Dock_Boss",
	"MNIS_A51b_1_Target_on_Navy_Boat",
	"MNIS_A56_0_Goon_Takes_Off",
	"MNIS_A56_1_Goon_Beaches_Boat",
	"MNIS_A56_2_Tony_Delivers_the_Goods",
	"MNIS_A59_0_Enemies_Drive_Up",
	"MNIS_A59_0_The_Cripple",
	"MNIS_A59_1_Second_Wave",
	"MNIS_A64_0_Daughter_Killed",
	"MNIS_A64_0_Daughter_Rescued",
	"MNIS_A64_0_Daughter_Roughed_Up",
	"MNIS_A64_0_Establish_Hotel",
	"MNIS_A80_0_Baggage_Check_Shemale",
	"MNIS_AMB_Angel_Dust_Owned",
	"MNIS_AMB_Babylon_Owned",
	"MNIS_AMB_Cabana_Owned",
	"MNIS_AMB_Chi_Peso_Owned",
	"MNIS_AMB_Cocos_Owned",
	"MNIS_AMB_Fidel_Owned",
	"MNIS_AMB_Hot_Coffee",
	"MNIS_AMB_Macau_Owned",
	"MNIS_AMB_Oakley_Drivein_Owned",
	"MNIS_AMB_Ogrady_Owned",
	"MNIS_AMB_Pedros_Owned",
	"MNIS_AMB_Peninsula_Owned",
	"MNIS_AMB_Shark_Eats_Busi_Man02",
	"MNIS_AMB_Shark_Eats_S_Henchman03",
	"MNIS_AMB_Sniper_Takes_Out_Tony",
	"MNIS_AMB_Stein_Owned",
	"MNIS_AMB_Sunray_Owned",
	"MNIS_AMB_Swansong_Owned",
	"MNIS_AMB_Tony_Beaten_by_Cops",
	"MNIS_AMB_Tony_Beaten_by_Gang",
	"MNIS_AMB_Tony_Beaten_by_Hoes",
	"MNIS_AMB_Tony_Dies_by_Shark",
	"MNIS_AMB_Tony_Needs_a_Drink",
	"MNIS_AMB_Ugin_Owned",
	"MNIS_AMB_Whippet_Owned",
	"MNIS_MA1A_0_Pedros_Intro",
	"MNIS_MA1A_0_Pedros_Success",
	"MNIS_MA1A_Pedros_Intro_Cam",
	"MNIS_MA2A_0_Cabana_Intro",
	"MNIS_MA2A_0_Cabana_Success",
	"MNIS_MA2A_Cabana_Intro_Cam",
	"MNIS_MA3A_0_Oakley_Intro",
	"MNIS_MA3A_0_Oakley_Success",
	"MNIS_MA3A_Oakley_Intro_Cam",
	"MNIS_MB1A_0_Ogrady_Intro",
	"MNIS_MB1A_0_Ogrady_Success",
	"MNIS_MB1A_Ogrady_Intro_Cam",
	"MNIS_MB2A_0_Fidel_Intro",
	"MNIS_MB2A_0_Fidel_Success",
	"MNIS_MB2A_0_Tapes_Aquired",
	"MNIS_MB2A_Fidel_Intro_Cam",
	"MNIS_MB3A_0_Ugin_Intro",
	"MNIS_MB3A_0_Ugin_Success",
	"MNIS_MB3A_Ugin_Intro_Cam",
	"MNIS_MB4A_0_Babylon_Intro",
	"MNIS_MB4A_0_Babylon_Success",
	"MNIS_MB4A_0_Empty_the_Club",
	"MNIS_MB4A_Babylon_Intro_Cam",
	"MNIS_MC1A_0_Angel_Dust_Intro",
	"MNIS_MC1A_0_Angel_Dust_Success",
	"MNIS_MC1A_0_Lead_Cops_Away",
	"MNIS_MC1A_0_Tony_Escapes_Cops",
	"MNIS_MC1A_Angel_Dust_Intro_Cam",
	"MNIS_MC2A_0_Whippet_Intro",
	"MNIS_MC2A_0_Whippet_Success",
	"MNIS_MC2A_Whippet_Intro_Cam",
	"MNIS_MC3A_0_Cop_Escapes",
	"MNIS_MC3A_0_Enemies_in_Back",
	"MNIS_MC3A_0_Peninsula_Intro",
	"MNIS_MC3A_0_Peninsula_Success",
	"MNIS_MC3A_Peninsula_Intro_Cam",
	"MNIS_MC4A_0_Robbers_Getting_Away",
	"MNIS_MC4A_0_Stein_Intro",
	"MNIS_MC4A_0_Stein_Success",
	"MNIS_MC4A_Stein_Intro_Cam",
	"MNIS_MC5A_0_Cocos_Failure",
	"MNIS_MC5A_0_Cocos_Intro",
	"MNIS_MC5A_0_Cocos_Success",
	"MNIS_MC5A_Cocos_Intro_Cam",
	"MNIS_MD1A_0_Macau_Intro",
	"MNIS_MD1A_0_Macau_Success",
	"MNIS_MD1A_Macau_Intro_Cam",
	"MNIS_MD2A_0_Chi_Peso_Intro",
	"MNIS_MD2A_0_Chi_Peso_Success",
	"MNIS_MD2A_Chi_Peso_Intro_Cam",
	"MNIS_MD3A_0_Swansong_Intro",
	"MNIS_MD3A_0_Swansong_Success",
	"MNIS_MD3A_Swansong_Intro_Cam",
	"MNIS_MD4A_0_Sunray_Intro",
	"MNIS_MD4A_0_Sunray_Success",
	"MNIS_MD4A_Sunray_Intro_Cam",
	"MNIS_S01_0_Skull_Kills_Tony_Balcony",
	"MNIS_S01_0_Tony_in_Chair",
	"MNIS_S01_1_Hm_Saves_the_Day",
	"MNIS_S01_1_Hm_Saves_the_Day_Alt",
	"MNIS_S01_2_Bazooka_Joe",
	"MNIS_S01_2_Car_Delivered",
	"MNIS_S01_3_Car_Drives_Out_of_Garage",
	"MNIS_S01_3_Tiger_Attack",
	"MNIS_S01_4_Cops_Are_Here",
	"MNIS_S01_4_Cops_Coming",
	"MNIS_S01_4_Tony_Beaten_by_Cops",
	"MNIS_S04_0_Establish_Hotel",
	"MNIS_S04_0_Establish_Penthouse",
	"MNIS_S04_1_Tony_Kills_Ricardo",
	"MNIS_S07_0_Boats_Arrive",
	"MNIS_S07_0_Cops_Arrive",
	"MNIS_S09_2_Snipers_Setup",
	"MNIS_S09_3_Nacho_Bleeds",
	"MNIS_S09_3_Nacho_Gets_Away",
	"MNIS_S10_0_Rubber_Ducky_Intro",
	"MNIS_S10_1_All_Hands_on_Deck",
	"MNIS_S10_2_The_Captain",
	"MNIS_S10_3_Enemies_on_the_Docks",
	"MNIS_S10_3_Mothership_Docks",
	"MNIS_S11_0_Truck1",
	"MNIS_S11_1_Truck2",
	"MNIS_S11_2_Truck3",
	"MNIS_S11_3_Truck4",
	"MNIS_S11_4_Mini_Boss_Escapes",
	"MNIS_S13_0_Assassins_Revealed",
	"MNIS_S13_0_Meal_Interrupted",
	"MNIS_S14_0_Diaz_Surprise",
	"MNIS_S14_0_Intro_Diaz_Motors",
	"MNIS_S14_1_Edgar_Gets_Away",
	"MNIS_S18_0_Mansion_Flyby",
	"MNIS_S18_1_Enemies_in_Position",
	"MNIS_S18_1_Sheffields_Death",
	"MNIS_S18_1_Sheffields_Death_HTH",
	"MNIS_S18_1_Sheffields_Death_Pistol",
	"MNIS_S18_1_Sheffields_Death_Rifle",
	"MNIS_S18_3_Gaspars_Death",
	"MNIS_S18_4_Rage_Kill_Sosa",
	"MNIS_SHA_0_Havana_Intro",
	"MNIS_SHB_0_Marina_Intro",
	"MNIS_SHC_0_Rail_Yard_Intro",
	"MNIS_SHD_0_Shoreline_Intro",
	"MNIS_TUT_Intro_Cam",
	"NIS_0D0A_credits",
	"NIS_0D0A_skull_fucked",
	"NIS_01_secretary",
	"NIS_02_bouncer",
	"NIS_03_sheffield",
	"NIS_04_coco",
	"NIS_05_vice",
	"NIS_06_felix",
	"NIS_07_cocos_coke",
	"NIS_08_storehouse",
	"NIS_09b_banking",
	"NIS_10D0A_office_politics",
	"NIS_10_jerry",
	"NIS_110_cops_intervene",
	"NIS_111_swampshack",
	"NIS_118_paying_off_the_vice",
	"NIS_119_Storehouse_Setup",
	"NIS_11_exotics_catalog",
	"NIS_124_frontal_assualt",
	"NIS_128_sheffields_betrayal",
	"NIS_128b_sheffields_betrayal",
	"NIS_140_chop_shop_suey",
	"NIS_159_plantation_purchase",
	"NIS_164_sheffield_boss_setup",
	"NIS_166_gaspar_boss_setup",
	"NIS_167_sosa_boss_setup",
	"NIS_170_Sosas_dead",
	"NIS_171_Tub_Talk",
	"NIS_17_meeting_venus",
	"NIS_18_int_casino_est",
	"NIS_18b_casino_fatale",
	"NIS_19_nachos_death",
	"NIS_21_refugees",
	"NIS_23_chop_shop",
	"NIS_24_delivering_the_goods",
	"NIS_26_dropping_off",
	"NIS_27_contract_killer",
	"NIS_29_jimmy_boca",
	"NIS_32_hotel_lobby",
	"NIS_33_ricardo",
	"NIS_34_bolivian_summit",
	"NIS_36_sandman",
	"PAL_MNIS_S04_1_Tony_Kills_Ricardo",
	"PAL_MNIS_S14_0_Intro_Diaz_Motors",
	"MNIS_S01_0_Tony_in_Chair",
};

const char* szMissions[] = {
	"A11",
	"A22",
	"A23",
	"A23x",
	"A51",
	"A51b",
	"A53",
	"A53a",
	"A53aReward",
	"A56",
	"A59",
	"A59a",
	"A64",
	"A80",
	"FF_0",
	"FF_0B",
	"FF_1",
	"FF_1B",
	"FF_2",
	"FF_2B",
	"FF_3",
	"FF_3B",
	"FF_4",
	"FF_4B",
	"MP01",
	"MP02",
	"MP03",
	"MP04",
	"M_A1A",
	"M_A1B",
	"M_A2A",
	"M_A2B",
	"M_A3A",
	"M_A3B",
	"M_B1A",
	"M_B1B",
	"M_B2A",
	"M_B2B",
	"M_B3A",
	"M_B3B",
	"M_B4A",
	"M_B4B",
	"M_C1A",
	"M_C1B",
	"M_C2A",
	"M_C2B",
	"M_C3A",
	"M_C3B",
	"M_C4A",
	"M_C4B",
	"M_C5A",
	"M_C5B",
	"M_D1A",
	"M_D1B",
	"M_D2A",
	"M_D2B",
	"M_D3A",
	"M_D3B",
	"M_D4A",
	"M_D4B",
	"M_EndOfStory",
	"M_SHA",
	"M_SHB",
	"M_SHC",
	"M_SHD",
	"S01a",
	"S01c",
	"S02",
	"S03",
	"S04",
	"S05",
	"S06",
	"S07a",
	"S08",
	"S08e",
	"S09",
	"S10",
	"S11",
	"S12",
	"S13",
	"S14",
	"S18",
	"S18a",
	"T01",
};

const char* szPeds[] = {
	"CharTemp_AA_Female01",
	"CharTemp_AA_Female02",
	"CharTemp_AA_Male01",
	"CharTemp_AA_Male01a",
	"CharTemp_AA_Male01b",
	"CharTemp_AA_Male02",
	"CharTemp_AA_Male02a",
	"CharTemp_Amb_Driver01",
	"CharTemp_Amb_Driver02",
	"CharTemp_Assn_Butcher",
	"CharTemp_Assn_Can",
	"CharTemp_Assn_Judge",
	"CharTemp_Assn_Law",
	"CharTemp_Assn_Pro",
	"CharTemp_B_Bimbo01",
	"CharTemp_B_Bimbo02",
	"CharTemp_B_Bimbo03",
	"CharTemp_B_Bimbo04",
	"CharTemp_Bart_Female",
	"CharTemp_BC_Bouncer",
	"CharTemp_BC_Chef",
	"CharTemp_BC_Comedian",
	"CharTemp_BC_Female01",
	"CharTemp_BC_Female02",
	"CharTemp_BC_Female03",
	"CharTemp_BC_Female04",
	"CharTemp_BC_Kcrew01",
	"CharTemp_BC_Kcrew02",
	"CharTemp_BC_Male01",
	"CharTemp_BC_Male02",
	"CharTemp_BC_Male03",
	"CharTemp_BC_Waiter",
	"CharTemp_BC_Waitress",
	"CharTemp_Boca",
	"CharTemp_Boss",
	"CharTemp_BS_Haitian02",
	"CharTemp_BS_Haitian03",
	"CharTemp_BS_Haitian04",
	"CharTemp_Bullet_Proof",
	"CharTemp_Bus_Driver01",
	"CharTemp_Busi_Man01",
	"CharTemp_Busi_Man01a",
	"CharTemp_Busi_Man02",
	"CharTemp_Busi_Man02a",
	"CharTemp_Busi_Woman01",
	"CharTemp_Busi_Woman02",
	"CharTemp_Cabana",
	"CharTemp_CGuard01",
	"CharTemp_CGuard02",
	"CharTemp_Chicken",
	"CharTemp_Clerk01",
	"CharTemp_Clerk02",
	"CharTemp_Clerk_Cabana",
	"CharTemp_Clerk_ChiPeso",
	"CharTemp_Clerk_Pedros",
	"CharTemp_Clerk_Stein",
	"CharTemp_Clerk_Swansong",
	"CharTemp_Clown",
	"CharTemp_Coco",
	"CharTemp_Columbia01",
	"CharTemp_Columbia02",
	"CharTemp_Columbia03",
	"CharTemp_Columbia04",
	"CharTemp_Columbia05",
	"CharTemp_Contract",
	"CharTemp_Cornelius",
	"CharTemp_CT_Female01",
	"CharTemp_CT_Female02",
	"CharTemp_CT_Male01",
	"CharTemp_CT_Male02",
	"CharTemp_D_Henchman01",
	"CharTemp_D_Henchman02",
	"CharTemp_D_Henchman03",
	"CharTemp_D_Henchman04",
	"CharTemp_D_Henchman05",
	"CharTemp_D_Henchman06",
	"CharTemp_D_Henchman07",
	"CharTemp_D_Henchman08",
	"CharTemp_Daughter",
	"CharTemp_DC_AA",
	"CharTemp_DC_Hispanic",
	"CharTemp_DC_White",
	"CharTemp_Dea_Undercover",
	"CharTemp_Dea_Uniform01",
	"CharTemp_Dea_Uniform02",
	"CharTemp_DG_AA",
	"CharTemp_DG_Hispanic",
	"CharTemp_DG_White",
	"CharTemp_Diaz",
	"CharTemp_Dock_Boss",
	"CharTemp_Drunk01",
	"CharTemp_Drunk02",
	"CharTemp_Dying_Henchman",
	"CharTemp_Edgar_Diaz",
	"CharTemp_Eunich",
	"CharTemp_Fat_Boss",
	"CharTemp_Felix",
	"CharTemp_FF01",
	"CharTemp_FF01_undies",
	"CharTemp_FF02",
	"CharTemp_FF02_undies",
	"CharTemp_FF03",
	"CharTemp_FF03_undies",
	"CharTemp_FF04",
	"CharTemp_FF04_undies",
	"CharTemp_FF05",
	"CharTemp_FF05_undies",
	"CharTemp_FF06",
	"CharTemp_FF06_undies",
	"CharTemp_FM_Angel",
	"CharTemp_FM_Babylon",
	"CharTemp_FM_Cabana",
	"CharTemp_FM_ChiPeso",
	"CharTemp_FM_Coco",
	"CharTemp_FM_Fidel",
	"CharTemp_FM_Macao",
	"CharTemp_FM_Oakley",
	"CharTemp_FM_Ogrady",
	"CharTemp_FM_Pedros",
	"CharTemp_FM_Peninsula",
	"CharTemp_FM_Stein",
	"CharTemp_FM_Sunray",
	"CharTemp_FM_Swansong",
	"CharTemp_FM_Ugin",
	"CharTemp_FM_Whippet",
	"CharTemp_G_Henchman01",
	"CharTemp_G_Henchman02",
	"CharTemp_G_Henchman03",
	"CharTemp_G_Henchman04",
	"CharTemp_G_Henchman05",
	"CharTemp_G_Henchman06",
	"CharTemp_G_Henchman07",
	"CharTemp_G_Henchman08",
	"CharTemp_Gaspar",
	"CharTemp_Gen_Bankteller",
	"CharTemp_Gina",
	"CharTemp_Gunvendor",
	"CharTemp_HeShe",
	"CharTemp_Hick01",
	"CharTemp_Hick02",
	"CharTemp_Hippy",
	"CharTemp_His_Female01",
	"CharTemp_His_Female02",
	"CharTemp_His_Female03",
	"CharTemp_His_Male01",
	"CharTemp_His_Male02",
	"CharTemp_His_Male02A",
	"CharTemp_His_Male02B",
	"CharTemp_His_Male03",
	"CharTemp_Hoe01",
	"CharTemp_Hoe01_Butch",
	"CharTemp_Hoe02",
	"CharTemp_Hoe02_Butch",
	"CharTemp_Hoe03",
	"CharTemp_Hotelclerk",
	"CharTemp_Island_Cop01",
	"CharTemp_Island_Cop02",
	"CharTemp_Island_Gang01",
	"CharTemp_Island_Gang01a",
	"CharTemp_Island_Gang01b",
	"CharTemp_Island_Gang02",
	"CharTemp_Island_Gang02a",
	"CharTemp_Island_Gang02b",
	"CharTemp_Island_Gang03",
	"CharTemp_Island_Gang03a",
	"CharTemp_Island_Gas",
	"CharTemp_Jam_Female01",
	"CharTemp_Jam_Female02",
	"CharTemp_Jam_Male01",
	"CharTemp_Jam_Male02",
	"CharTemp_Jerry",
	"CharTemp_LL01",
	"CharTemp_LL02",
	"CharTemp_LL03",
	"CharTemp_Logan",
	"CharTemp_Longshore01",
	"CharTemp_Longshore01A",
	"CharTemp_Longshore01B",
	"CharTemp_Longshore01C",
	"CharTemp_Longshore02",
	"CharTemp_Longshore02A",
	"CharTemp_Longshore02B",
	"CharTemp_LT_Diaz",
	"CharTemp_LT_Nacho",
	"CharTemp_M_Henchman01",
	"CharTemp_M_Henchman02",
	"CharTemp_M_Henchman03",
	"CharTemp_M_Henchman04",
	"CharTemp_M_Henchman05",
	"CharTemp_Main_Bankteller",
	"CharTemp_Mama",
	"CharTemp_Maribelle",
	"CharTemp_Mechanic",
	"CharTemp_Miami_Cop01",
	"CharTemp_Miami_Cop02",
	"CharTemp_Miami_Cop03",
	"CharTemp_Miami_Cop04",
	"CharTemp_Miami_Cop05",
	"CharTemp_Miami_Cop06",
	"CharTemp_Miami_Gas",
	"CharTemp_Muscle",
	"CharTemp_MuscleA",
	"CharTemp_MuscleB",
	"CharTemp_MuscleC",
	"CharTemp_MuscleD",
	"CharTemp_N_Henchman01",
	"CharTemp_N_Henchman02",
	"CharTemp_N_Henchman03",
	"CharTemp_N_Henchman04",
	"CharTemp_N_Henchman05",
	"CharTemp_N_Henchman06",
	"CharTemp_N_Henchman07",
	"CharTemp_N_Henchman08",
	"CharTemp_Nacho",
	"CharTemp_NIS_Boat_Captain",
	"CharTemp_NPC_Bar",
	"CharTemp_NPC_BlackSuitTony",
	"CharTemp_NPC_BlackSuitTonyShades",
	"CharTemp_NPC_BlueSuitTony",
	"CharTemp_NPC_BlueSuitTonyShades",
	"CharTemp_NPC_Bookie",
	"CharTemp_NPC_Dis_Man",
	"CharTemp_NPC_Dis_Woman",
	"CharTemp_NPC_Fisherman",
	"CharTemp_NPC_GraySuitTony",
	"CharTemp_NPC_GraySuitTonyShades",
	"CharTemp_NPC_HawaiianTony",
	"CharTemp_NPC_HawaiianTonyShades",
	"CharTemp_NPC_Inbred",
	"CharTemp_NPC_Market",
	"CharTemp_NPC_Mother",
	"CharTemp_NPC_Reporter",
	"CharTemp_NPC_SandyTony",
	"CharTemp_NPC_SandyTonyShades",
	"CharTemp_NPC_Smuggler",
	"CharTemp_NPC_Sorority",
	"CharTemp_NPC_Waitress",
	"CharTemp_NPC_WhiteSuitTony",
	"CharTemp_NPC_WhiteSuitTonyShades",
	"CharTemp_Ocean_Gas",
	"CharTemp_Old_Female",
	"CharTemp_Old_His_Female",
	"CharTemp_Old_His_Male",
	"CharTemp_Old_His_Male01",
	"CharTemp_Old_Male",
	"CharTemp_Old_Male01",
	"CharTemp_Pablo",
	"CharTemp_Pimp",
	"CharTemp_Pimp02",
	"CharTemp_Pirate01",
	"CharTemp_Pirate02",
	"CharTemp_Politician",
	"CharTemp_Prep",
	"CharTemp_Refugee01",
	"CharTemp_Refugee02",
	"CharTemp_Ricardo",
	"CharTemp_S_B_Guard01",
	"CharTemp_S_B_Guard02",
	"CharTemp_S_Henchman01",
	"CharTemp_S_Henchman02",
	"CharTemp_S_Henchman03",
	"CharTemp_S_Henchman04",
	"CharTemp_S_Henchman05",
	"CharTemp_S_Henchman06",
	"CharTemp_S_Henchman07",
	"CharTemp_S_Henchman08",
	"CharTemp_Sandman",
	"CharTemp_SD01",
	"CharTemp_SD01A",
	"CharTemp_SD02",
	"CharTemp_SD02A",
	"CharTemp_SD03",
	"CharTemp_SD04",
	"CharTemp_Shao",
	"CharTemp_Shark",
	"CharTemp_Sheffield",
	"CharTemp_Sheffield_Babe",
	"CharTemp_Skull",
	"CharTemp_Sosa",
	"CharTemp_SS01",
	"CharTemp_SS02",
	"CharTemp_SS03",
	"CharTemp_SS04",
	"CharTemp_Swat01",
	"CharTemp_Swat02",
	"CharTemp_T_Henchman01",
	"CharTemp_T_Henchman02",
	"CharTemp_T_Henchman03",
	"CharTemp_T_Henchman04",
	"CharTemp_T_Henchman05",
	"CharTemp_Tiger",
	"CharTemp_Trailer01",
	"CharTemp_Trailer02",
	"CharTemp_Venus",
	"CharTemp_Vera",
	"CharTemp_Vice_Black",
	"CharTemp_Vice_White",
	"CharTemp_Young_Female01",
	"CharTemp_Young_Female02",
	"CharTemp_Young_Female03",
	"CharTemp_Young_Male01",
	"CharTemp_Young_Male02",
	"CharTemp_Young_Male03",
	"CharTemp_Yup_Female01",
	"CharTemp_Yup_Female02",
	"CharTemp_Yup_Male01",
	"CharTemp_Yup_Male02",
};


const char* szAnimations[] = {
	"A80_Death",
	"Arcade_State",
	"BAT",
	"Bartender_State",
	"BeggingForLife",
	"Boat_Sitting_Generic",
	"Boat_Steer_Generic",
	"Boat_Target_Generic",
	"Browse_High_State",
	"Browse_Low_State",
	"CHAINSAW",
	"CHICKEN_ATTACK",
	"CHICKEN_DODGE",
	"CHICKEN_IDLE",
	"Cancel_Ambient_Loop",
	"CarHit_Hard",
	"CarHit_Hard_Death",
	"CarHit_Low",
	"CarHit_Mid",
	"CarHit_Mid_Death",
	"Car_Exit_Door_0",
	"Car_Exit_Door_1",
	"Car_Exit_NoDoor_0",
	"Car_Exit_NoDoor_1",
	"Car_Exit_Thrown_Driver",
	"Car_Exit_Thrown_Driver_Dead",
	"Car_GU_Target",
	"Car_Pass_Door_0_to_Door_1",
	"Car_Pass_Door_1_to_Door_0",
	"CardDealer_State",
	"CheckMachineHigh_State",
	"CheckMachineLow_State",
	"Cheering_State",
	"CigMachine_State",
	"CounterBrowsing_State",
	"CowerState",
	"CrouchCover",
	"DAMAGE",
	"DANCE",
	"DEATH",
	"Dancing_State",
	"DealerIdles",
	"DeathLandingHigh",
	"DeathLandingHighDebug",
	"DefaultDeathPose",
	"Dishes_State",
	"DiveFromVehicle",
	"Dive_L",
	"Dive_N",
	"Dive_R",
	"Dodge_L",
	"Dodge_R",
	"DriveThrough_State",
	"Drumming_State",
	"EXPLOSIONDAMAGE",
	"EXPLOSIONDEATH",
	"EnteringWallCover",
	"ExecutionBack",
	"ExecutionFront",
	"ExitCover",
	"ExitingWallCover",
	"FIRING_MOUNTED_GUN",
	"Frying_State",
	"Gang_Idles",
	"GetIn_Door_0_Busy",
	"GetIn_Door_0_NoDoor",
	"GetIn_Door_0_empty",
	"GetIn_Door_1_Drive",
	"GetIn_Door_1_Drive_NoPass",
	"GetIn_Door_1_NoDoor",
	"GetIn_Door_1_NoDoor_NoPass",
	"GetIn_Door_1_NoDrive_Door",
	"GetIn_Door_1_NoDrive_NoDoor",
	"GetOut_Boat_Dive",
	"GetUpBack",
	"GetUpFront",
	"Ghetto_State",
	"Grab",
	"GrenadeDeath",
	"Grilling_State",
	"GroinKick",
	"Grooming_State",
	"H_DS",
	"Heli_Exit",
	"Heli_Fire",
	"Heli_GunDown",
	"Heli_GunUp",
	"Heli_Pilot_Idle",
	"Idle",
	"Idle_Alert",
	"Intimidate_Fail_State",
	"Intimidate_Success_State",
	"Jukebox_State",
	"KitchenPrep_State",
	"LandingMedium",
	"LeanLeftCover",
	"LeanLeft_State",
	"LeanRail_State",
	"LeanRightCover",
	"LeanRight_State",
	"MELEEDAMAGE",
	"Mailbox_State",
	"Mercy",
	"Motion_Toward",
	"NearMiss",
	"NearMissBack",
	"NewspaperBox_State",
	"Ordering_State",
	"PHONEHANGUP",
	"PHONELISTEN",
	"PHONEPICKUP",
	"PROXIMITYWEAPONATTACK",
	"PUNCH",
	"PassFire",
	"PassSit",
	"Patrol_Alert_State",
	"Patrol_Relaxed_State",
	"Patrol_Searching_State",
	"Peeing_State",
	"Player_State",
	"PopMachine_State",
	"Prone_KneeR_Slave",
	"Push",
	"Push_Block",
	"RecordStore_State",
	"ReputationGain",
	"ReturnToSeatedState",
	"Roll_L",
	"Roll_R",
	"SHARK_ATTACK",
	"Seated_Cower",
	"Sit_Bar_State",
	"Sit_Conversation_State",
	"Sit_Dancing_State",
	"Sit_Drinking_State",
	"Sit_Eating_State",
	"Sit_Idle_State",
	"Sit_Lounge_State",
	"Sit_On_Bench",
	"Sit_Ordering_State",
	"Sit_Piano_State",
	"Sit_Sleep_State",
	"Sit_Smoking_State",
	"Sit_Work_Cigar_State",
	"Sit_Work_Jewlery_State",
	"Sit_Work_Office_State",
	"SlotMachine_State",
	"Smoking_State",
	"Spectating_State",
	"Standing_State",
	"StartShooting",
	"Steer_Forward",
	"Steer_Reverse",
	"Stool_Drinking_State",
	"Stool_Ordering",
	"Stool_Sitting_State",
	"StopShooting",
	"TM_Vehicle_Car_Seat_Pass",
	"TM_Vehicle_Car_Target_Back",
	"TM_Vehicle_Car_Target_Pass",
	"TONY_DEATH",
	"TWITCHDAMAGE",
	"Taunt",
	"Telephone_State",
	"Teller_State",
	"ThrowDriverOut",
	"ThrowDriverOutNoDoor",
	"TrashBin_State",
	"Truck_Exit_Door_0",
	"Truck_Exit_Door_1",
	"Truck_Exit_NoDoor_0",
	"Truck_Exit_Thrown_Driver",
	"Vehicle_Bail_Dive_Car_Door_0",
	"Vehicle_Bail_Dive_Car_Door_1",
	"Vehicle_Bail_Dive_Truck_Door_0",
	"Vehicle_Bail_Dive_Truck_Door_1",
	"Vehicle_Bail_Roll_Car_Door_0",
	"Vehicle_Bail_Roll_Car_Door_1",
	"Vehicle_Bail_Roll_Truck_Door_0",
	"Vehicle_Bail_Roll_Truck_Door_1",
	"WEAPONBUTTDAMAGE",
	"WaitingTables_State",
	"WallCover_Into_E",
	"WallCover_Into_W",
	"WallCover_Out_E",
	"WallCover_Out_W",
	"WashingHands_State",
	"attract",
	"clerk_State",
	"exitVanState",
	"listeningEndState",
	"listeningState",
	"propose",
	"purchase_State",
	"react_bad",
	"react_good",
	"react_great",
	"respond_negative",
	"respond_positive",
	"streetDealerAttractState",
	"streetDealerDismissState",
	"streetDealerIdleState",
	"stumbleState",
	"talkingEndState",
	"talkingState",
	"taunt",
};


struct debugMenuPair {
	char* name;
	char* func;
};


debugMenuPair szDebugEntries[] = {
	{"Artist Safe Roam","ArtistSafeRoam();"},
	{"Test 100 Game Complete","GameCompleteCheat();"},
	{"Toggle Dynamic Difficulty","DDA_Toggle();"},
	{"Display Current DDA Level","DDA_Display();"},
	{"Toggle Debug info","HUD_ToggleDebug();"},
	{"1000 balls","ChangeBalls(1000);"},
	{"50000 balls (Femme Unlocking)","ChangeBalls(50000);"},
	{"Get Massive Ammo","AllWeapons();MaxAmmo();"},
	{"10,000,000 dirty cash","DBChangeDirtyCash(10000000);"},
	{"1000g drugs","DBChangeProduct(1000);"},
	{"Make Supplier Ready","Set_SatphoneMissionCounter(10);"},
	{"Show PMG Templates","REPRO_ShowPMGTemplateData();"},
	{"Display Last PMG Template","REPRO_DisplayData();"},
	{"Restart Last PMG","REPRO_RestartLastPMG();"},
	{"Test Miami Addresses","AC_CheckAddresses(\"MIAMI\");"},
	{"Test Island Addresses","AC_CheckAddresses(\"ISLAND\");"},
	{"Show Current Address ID","AC_DisplayCurrentAddressInfo();"},
	{"SetCopHeat 0","SetCopHeat(0);"},
	{"SetCopHeat 2500","SetCopHeat(2500);"},
	{"SetCopHeat 4500","SetCopHeat(4500);"},
	{"SetCopHeat 6500","SetCopHeat(6500);"},
	{"SetCopHeat 8500","SetCopHeat(8500);"},
	{"SetCopHeat 10000","SetCopHeat(10000);"},
	{"SetGangHeat 0","SetGangHeat(0);"},
	{"SetGangHeat 2500","SetGangHeat(2500);"},
	{"SetGangHeat 4500","SetGangHeat(4500);"},
	{"SetGangHeat 6500","SetGangHeat(6500);"},
	{"SetGangHeat 8500","SetGangHeat(8500);"},
	{"SetGangHeat 10000","SetGangHeat(10000);"},
	{"Toggle Lock to Vsync","ToggleLockToVsync();"},
	{"Toggle Half Speed","ToggleSlowMotion();"},
	{"Toggle Cop Game","CopGame_Toggle();"},
	{"Toggle Rain","ToggleRaining();"},
	{"Toggle Lightning","ToggleLightning();"},
	{"Sound Disable Random","SoundDisableRandom();"},
	{"Call Any NIS","anyNISSelectFromMenu();"},
	{"[PHONE_INVINCIBLE]","TogglePlayerInvincible();"},
	{"[PHONE_MONEY_NOW]","d_cash();"},
	{"[FORCE_INCOME]","force_collectionMission();"},
	{"[PHONE_MISSIONFAIL]","mission_fail();"},
	{"[PHONE_MISSIONFINISH]","mission_finish();"},
	{"Advance Stage","mission_advanceStage();"},
	{"Toggle HUD","HUD_ToggleHUD();"},
	{"Test font","TestFont();"},
	{"Quit Game","GameShutdown();"},
	{"Matrix Mode (Spawn All Weapons)","MatrixMode();"},
	{"Display Last Supplier Fail Reason.","DisplaySupplierFailReason();"},
	{"Save Game To Profile 1","SGS_ActivateQueue(2,0);"},
	{"Save Game To Profile 2","SGS_ActivateQueue(2,1);"},
	{"Save Game To Profile 3","SGS_ActivateQueue(2,2);"},
	{"Save Game To Profile 4","SGS_ActivateQueue(2,3);"},
};

ScarfaceMenu* TheMenu = new ScarfaceMenu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

}

void ScarfaceMenu::Init()
{
	sprintf(character, szCharacters[0]);
	sprintf(vehicle, szVehicles[0]);
	sprintf(weapon, szWeapons[0]);
	sprintf(characterWeapon, szWeapons[0]);
	sprintf(cutscene, szCutscenes[0]);
	sprintf(dbgItem, szDebugEntries[0].name);
	sprintf(mission, szMissions[0]);
	sprintf(characterSpawn, szPeds[0]);
	sprintf(animName, szAnimations[128]);

	m_fSpeed = 1.0f;

	LoadLocationFile();

	if (vTeleports.size() > 0)
		sprintf(teleportName, vTeleports[0].name);
}

void ScarfaceMenu::Draw()
{
	if (!m_bIsActive)
		return;

	ImGui::Begin("ScarfaceHook by ermaccer",&m_bIsActive, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	static char console[4096] = {};

	if (GetMainCharacter())
	{
		ImGui::BeginTabBar("##tabs");


		if (ImGui::BeginTabItem("Player"))
		{
			DrawPlayerTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Spawner"))
		{
			DrawSpawnerTab();
			ImGui::EndTabItem();
		}
		if (vTeleports.size() > 0)
		{
			if (ImGui::BeginTabItem("Teleporter"))
			{
				DrawTeleporterTab();
				ImGui::EndTabItem();
			}
		}
		if (ImGui::BeginTabItem("Speed"))
		{
			DrawSpeedTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera"))
		{
			DrawCameraTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("World"))
		{
			DrawWorldTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			DrawMiscTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Script"))
		{
			ImGui::TextWrapped("Notepad");
			ImGui::InputTextMultiline("", console, sizeof(console), { -FLT_MIN, 150 });
			ImGui::TextWrapped("Bytes free: %d", sizeof(console) - strlen(console));

			if (ImGui::Button("Run", { -FLT_MIN, 0 }))
				runScript(console);


			ImGui::EndTabItem();
		}
		if (GetModuleHandle("Scarface.DebugMenu.asi"))
		{
			if (ImGui::BeginTabItem("Debug"))
			{
				DrawDebugTab();
				ImGui::EndTabItem();
			}
		}

		ImGui::EndTabBar();
	}
	else
		ImGui::TextWrapped("Not ready!");
	

	ImGui::End();

	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();
}

void ScarfaceMenu::DrawPlayerTab()
{	
	ImGui::TextWrapped("Skin");
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##skin", character))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
		{
			bool is_selected = (character == szCharacters[n]);
			if (ImGui::Selectable(szCharacters[n], is_selected))
			{
				sprintf(character, szCharacters[n]);
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Player skin set to %s", character);
				setPlayerSkin(character);
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
	ImGui::Separator();

	ImGui::TextWrapped("Weapons");
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##wlist", weapon))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szWeapons); n++)
		{
			bool is_selected = (weapon == szWeapons[n]);
			if (ImGui::Selectable(szWeapons[n], is_selected))
				sprintf(weapon, szWeapons[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
	if (ImGui::Button("Give Weapon", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Weapon %s given!", weapon);
		giveWeaponToPlayer(weapon);

	}
	ImGui::Separator();
	if (ImGui::_Checkbox("Infinite Ammo", &m_bInfiniteAmmo))
	{
		if (CharacterObject* plr = GetMainCharacter())
				plr->InfiniteAmmo(m_bInfiniteAmmo);
	}
	ImGui::_Checkbox("Invincibility", &m_bForceInvincibility);
	ImGui::SameLine();
	ShowHelpMarker("Player needs to die from fall damage to have the full effect.");
	ImGui::_Checkbox("Disable Fall Damage", &m_bDisableFallDamage);
	ImGui::Separator();
	Vector plrPos = *(Vector*)(0x7C68DC);
	ImGui::Text("Position");
#ifdef CLIP_POS
	if (ImGui::Button("Copy"))
	{
		char pos[128] = {};
		sprintf(pos, "%f %f %f", plrPos.X, plrPos.Y, plrPos.Z);
		const size_t len = strlen(pos);
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), pos, len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
		MessageBeep(MB_ICONINFORMATION);
	}
#endif
	ImGui::InputFloat3("X | Y | Z", &plrPos.X);


	ImGui::_Checkbox("Airbreak", &m_bAirbreak);
	ImGui::SameLine();
	ShowHelpMarker("Allows to move player with hotkeys.\nYou can configure keys in .ini file or in the Settings menu.\nAutomatically enforces no fall damage and invincibility.");

	if (m_bAirbreak)
		ImGui::InputFloat("Airbreak Speed", &m_fAirbreakSpeed);

	ImGui::Separator();
	if (ImGui::CollapsingHeader("Data"))
	{
		{
			static int balls = 0;
			ImGui::TextWrapped("Balls");
			ImGui::InputInt("##balls", &balls);
			ImGui::SameLine();
			if (ImGui::Button("Give Balls"))
			{
				char buff[128];
				sprintf(buff, "ChangeBalls(%d);", balls);
				runScript(buff);
			}
		}
		{
			static int money = 0;
			static bool dirty = true;
			ImGui::TextWrapped("Money");
			ImGui::InputInt("##money", &money);
			ImGui::SameLine();
			ImGui::_Checkbox("Dirty", &dirty);
			ImGui::SameLine();
			if (dirty)
			{
				if (ImGui::Button("Give Dirty Money"))
				{
					char buff[128];
					sprintf(buff, "DBChangeDirtyCash(%d);", money);
					runScript(buff);
				}
			}
			else
			{
				if (ImGui::Button("Give Money"))
				{
					char buff[128];
					sprintf(buff, "DBChangeCleanCash(%d);", money);
					runScript(buff);
				}
			}

		}
		{
			static int drugs = 0;
			ImGui::TextWrapped("Drugs");
			ImGui::InputInt("##drug", &drugs);
			ImGui::SameLine();
			if (ImGui::Button("Give Drugs"))
			{
				char buff[128];
				sprintf(buff, "DBChangeProduct(%d);", drugs);
				runScript(buff);
			}
		}
		{
			static int gang = 0;
			ImGui::TextWrapped("Gang Heat");
			ImGui::InputInt("##gang", &gang);
			ImGui::SameLine();
			if (ImGui::Button("Give Gang Heat"))
			{
				char buff[128];
				sprintf(buff, "DBChangeGangHeat(%d);", gang);
				runScript(buff);
			}
		}
		{
			static int cop = 0;
			ImGui::TextWrapped("Cop Heat");
			ImGui::InputInt("##cop", &cop);
			ImGui::SameLine();
			if (ImGui::Button("Give Cop Heat"))
			{
				char buff[128];
				sprintf(buff, "DBChangeCopHeat(%d);", cop);
				runScript(buff);
			}
		}

	}
	if (ImGui::CollapsingHeader("Animation"))
	{
		static bool animManual = false;

		ImGui::Text("Animation Name");
		ImGui::SameLine();
		char animTip[260] = {};
		sprintf(animTip, "Press (%s) to play last selected animation.\n\nSome animations can make player stuck permanently and restore player state might not help, in case that happens, only \"fix\" is to reload profile, you can also try to spam \"Teleport Player To Camera\" to reset state.",
			eKeyboardMan::KeyToString(SettingsMgr->iPlayLastAnimKey));
		ShowHelpMarker(animTip);
		if (animManual)
		{
			ImGui::PushItemWidth(-FLT_MIN);
			ImGui::InputText("##animName", animName, sizeof(animName));
			ImGui::PopItemWidth();
		}
		else
		{
			ImGui::PushItemWidth(-FLT_MIN);
			if (ImGui::BeginCombo("##animList", animName))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szAnimations); n++)
				{
					bool is_selected = (animName == szAnimations[n]);
					if (ImGui::Selectable(szAnimations[n], is_selected))
						sprintf(animName, szAnimations[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
		}
		ImGui::_Checkbox("Enter Manually", &animManual);

		if (ImGui::Button("Play", { -FLT_MIN, 0 }))
			GetMainCharacter()->PlayAnimation(animName);
		if (ImGui::Button("Restore Player State", { -FLT_MIN, 0 }))
		{
			GetMainCharacter()->ResetAnimation();
			GetMainCharacter()->SetPhysicalMode("Cancel_Ambient_Loop");
		}

	}
	
}

void ScarfaceMenu::DrawSpawnerTab()
{
	ImGui::_Checkbox("High Priority", &m_bHighPrioritySpawning);
	ImGui::SameLine();
	ShowHelpMarker("Loads data with a higher priority, may help loading if an object doesn't want to spawn. Do not abuse, untick after spawning an object.");
	ImGui::_Checkbox("Create At Custom Position", &m_bSpawnerCustomPosition);
	if (m_bSpawnerCustomPosition)
	{
		ImGui::TextWrapped("Spawn Position");
		ImGui::InputFloat3("X | Y | Z", &customSpawnPos.X);
	}
	ImGui::Separator();

	ImGui::TextWrapped("Vehicle");
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##vehlist", vehicle))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szVehicles); n++)
		{
			bool is_selected = (vehicle == szVehicles[n]);
			if (ImGui::Selectable(szVehicles[n], is_selected))
				sprintf(vehicle, szVehicles[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
	if (ImGui::Button("Create", { -FLT_MIN, 0 }))
	{
		Vector pos = GetMainCharacter()->GetLocation();
		Vector forward = GetMainCharacter()->GetMatrix().GetForward();

		pos += forward * 3.0f;
		if (m_bSpawnerCustomPosition)
			SpawnCar(vehicle, &customSpawnPos);
		else
			SpawnCar(vehicle, &pos);
	}
	ImGui::Separator();

	ImGui::TextWrapped("Character");
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##chrlist", characterSpawn))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szPeds); n++)
		{
			bool is_selected = (characterSpawn == szPeds[n]);
			if (ImGui::Selectable(szPeds[n], is_selected))
				sprintf(characterSpawn, szPeds[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
	/*
	ImGui::_Checkbox("Weapon", &m_bCharacterUseWeapon);
	ImGui::SameLine();
	if (ImGui::BeginCombo("##wclist", weapon))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szWeapons); n++)
		{
			bool is_selected = (characterWeapon == szWeapons[n]);
			if (ImGui::Selectable(szWeapons[n], is_selected))
				sprintf(characterWeapon, szWeapons[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	*/

	if (ImGui::Button("Create Character", { -FLT_MIN, 0 }))
	{
		Vector pos = GetMainCharacter()->GetLocation();
		Vector forward = GetMainCharacter()->GetMatrix().GetForward();

		pos += forward * 3.0f;
		if (m_bSpawnerCustomPosition)
			SpawnCharacter(characterSpawn, &customSpawnPos);
		else
			SpawnCharacter(characterSpawn, &pos);
	}
	ImGui::Separator();
}

void ScarfaceMenu::DrawCameraTab()
{
	ImGui::_Checkbox("Set Camera Position", &m_bCustomCameraPos);
	ImGui::InputFloat3("X | Y | Z", &camPos.X);
	ImGui::_Checkbox("Set FOV", &m_bCustomCameraFOV);
	ImGui::InputFloat("FOV", &camFov);
	ImGui::Separator();
	ImGui::_Checkbox("Free Camera", &m_bFreeCam);
	ImGui::SameLine(); ShowHelpMarker("Allows to move camera with hotkeys.\nYou can configure keys in .ini file or in the Settings menu.");

	if (m_bFreeCam)
	{
		if (!m_bCustomCameraPos || !m_bCustomCameraFOV)
			ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check rest of the Set Camera options!");

		ImGui::InputFloat("Free Camera Speed", &m_fFreeCamSpeed);
	}



	ImGui::Separator();
	ImGui::TextWrapped("First Person");
	ImGui::_Checkbox("Enable##fp", &fps.enabled);
	if (fps.enabled)
	{
		ImGui::SliderFloat("Height Adjustement", &fps.YAdjust, -1.0f, 1.0f);
		ImGui::SliderFloat("Distance", &fps.ZAdjust, -0.065, 0.500f);
		ImGui::SliderFloat("Offset", &fps.XAdjust, -0.100, 0.100f);

		if (ImGui::Button("Save", { -FLT_MIN, 0 }))
		{
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Settings saved!");
			eDirectX9Hook::ms_bShouldReloadFonts = true;
			SettingsMgr->SaveSettings();
		}
	}
	ImGui::Separator();
	if (ImGui::Button("Teleport Player To Camera", { -FLT_MIN, 0 }))
	{
		setPlayerPosition(TheCamera->GetLocation());
	}
}

void ScarfaceMenu::DrawWorldTab()
{
	static int time[2];

	ImGui::TextWrapped("Time (Hour | Minute)");
	ImGui::PushItemWidth(-FLT_MIN);
	ImGui::InputInt2("", time);
	ImGui::PopItemWidth();
	if (ImGui::Button("Set Time", { -FLT_MIN, 0 }))
	{
		TODObject::TOD->SetTime(time[0], time[1]);
	}
	ImGui::Separator();
	if (ImGui::Button("Disable Rain", { -FLT_MIN, 0 }))
		TODObject::TOD->EnableRain(false);
	if (ImGui::Button("Enable Rain", { -FLT_MIN, 0 }))
		TODObject::TOD->EnableRain(true);
	ImGui::Separator();
}

void ScarfaceMenu::DrawSpeedTab()
{
	ImGui::TextWrapped("Gamespeed");
	ImGui::PushItemWidth(-FLT_MIN);
	ImGui::SliderFloat("",&m_fSpeed,0.0,5.0f);
	ImGui::PopItemWidth();
	if (ImGui::Button("Set Speed", { -FLT_MIN, 0 }))
	{
		runScript("PopTimeScale();");
		char buff[128];
		sprintf(buff, "PushTimeScale(%f);", m_fSpeed);
		runScript(buff);
	}
	if (ImGui::Button("Restore", { -FLT_MIN, 0 }))
	{
		runScript("PopTimeScale();");
		m_fSpeed = 1.0f;
	}
	ImGui::Separator();
}

void ScarfaceMenu::DrawTeleporterTab()
{
	static int nCurOption = 0;

	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##tplist", teleportName))
	{
		for (int n = 0; n < vTeleports.size(); n++)
		{
			bool is_selected = (teleportName == vTeleports[n].name);
			if (ImGui::Selectable(vTeleports[n].name, is_selected))
			{
				sprintf(teleportName, vTeleports[n].name);
				nCurOption = n;
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();


	if (ImGui::Button("Teleport", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Teleported to %s", teleportName);
		TonyTeleport(vTeleports[nCurOption].pos);
	}

	if (ImGui::CollapsingHeader("Add Location"))
	{
		static Vector newPos = {};

		ImGui::InputFloat3("Position", &newPos.X);
		if (ImGui::Button("Get Player Position"))
		{
			if (GetMainCharacter())
				newPos = GetMainCharacter()->GetLocation();
		}

		static char newName[260] = {};
		ImGui::InputText("Name", newName, sizeof(newName));

		if (strlen(newName) > 0)
		{
			if (ImGui::Button("Add", { -FLT_MIN, 0 }))
			{
				TeleporterPlace place;
				place.pos = newPos;
				sprintf(place.name, newName);
				vTeleports.push_back(place);
				char str[128] = {};
				sprintf(str, "Place%d", vTeleports.size()-1);

				locIni->WriteBoolean(str, "is_set", true);
				locIni->WriteString(str, "name", place.name);
				locIni->WriteFloat(str, "x", place.pos.X);
				locIni->WriteFloat(str, "y", place.pos.Y);
				locIni->WriteFloat(str, "z", place.pos.Z);
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Added & saved %s", place.name);

				newPos = {};
				newName[0] = 0x00;
			}
		}
	}
}

void ScarfaceMenu::DrawMiscTab()
{

	if (ImGui::Button("Hide HUD"))
		runScript("HUD_Hide();");
	ImGui::SameLine();
	if (ImGui::Button("Show HUD"))
		runScript("HUD_Show();");

	ImGui::Separator();
	ImGui::TextWrapped("Cutscene");
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::BeginCombo("##cslist", cutscene))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szCutscenes); n++)
		{
			bool is_selected = (cutscene == szCutscenes[n]);
			if (ImGui::Selectable(szCutscenes[n], is_selected))
				sprintf(cutscene, szCutscenes[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();

	if (ImGui::Button("Play", { -FLT_MIN, 0 }))
	{
		playCutscene(cutscene);
	}

	ImGui::Separator();

	ImGui::Separator();
	ImGui::TextWrapped("Mission");
	static bool custName = false;
	ImGui::_Checkbox("Custom Name", &custName);
	if (!custName)
	{
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::BeginCombo("##mlist", mission))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szMissions); n++)
			{
				bool is_selected = (mission == szMissions[n]);
				if (ImGui::Selectable(szMissions[n], is_selected))
					sprintf(mission, szMissions[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}
	else
	{
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("", mission, sizeof(mission));
		ImGui::PopItemWidth();
	}

	if (ImGui::Button("Play##mission", { -FLT_MIN, 0 }))
	{
		playMission(mission);
	}

	ImGui::Separator();

	ImGui::TextWrapped("Fun (WIP)");

	if (ImGui::Button("Explode All Characters", { -FLT_MIN, 0 }))
		ExplodeAllPeds();
	if (ImGui::Button("Make Everyone Dance", { -FLT_MIN, 0 }))
		MakeAllPedsDance();

#ifdef _DEBUG
	static char text[256] = {};
	ImGui::InputText("Text", text, sizeof(text));
	static int hash = 0;
	hash = _hash(text);
	ImGui::Text("0x%X", hash);
	ImGui::Text("%p chr", GetMainCharacter());
#endif // _DEBUG


}

void ScarfaceMenu::DrawDebugTab()
{
	if (!GetModuleHandle("Scarface.DebugMenu.asi"))
	{
		ImGui::TextWrapped("Debug Menu unlock asi is required to call original debug functions.");
		return;
	}
	ImGui::TextWrapped("Original debug menu options.");
	ImGui::Separator();
	ImGui::PushItemWidth(-FLT_MIN);
	static int nCurOption = 0;
	if (ImGui::BeginCombo("##dbglist", dbgItem))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szDebugEntries); n++)
		{
			bool is_selected = (dbgItem == szDebugEntries[n].name);
			if (ImGui::Selectable(szDebugEntries[n].name, is_selected))
				{ 
					sprintf(dbgItem, szDebugEntries[n].name);
					nCurOption = n;
				}
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();

	if (ImGui::Button("Run", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Debug function %s executed", szDebugEntries[nCurOption].func);
		runScript(szDebugEntries[nCurOption].func);
	}
}

void ScarfaceMenu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"Keys"
	};

	enum eSettings {
		MENU,
		KEYS,
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to scfhook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat("", &SettingsMgr->fMenuScale);
		ImGui::PopItemWidth();
		break;
	case KEYS:
		if (m_bPressingKey)
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");
		if (ImGui::Button("Reset Keys", { -FLT_MIN, 0 }))
		{
			SettingsMgr->ResetKeys();
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Keys reset! Remember to save.");
		}
		ImGui::Separator();
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iHookMenuOpenKey, "Open/Close Menu", "menu");
		KeyBind(&SettingsMgr->iHookSlowMoKey, "Toggle Gamespeed", "slomo");
		ImGui::Separator();
		ImGui::LabelText("", "Camera/Airbreak");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyForward, "Forward", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyBack, "Back", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyLeft, "Left", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRight, "Right", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyUp, "Up", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyDown, "Down", "z_minus");
		ImGui::Separator();

		ImGui::LabelText("", "Features");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iToggleFirstPersonKey, "First Person Mode", "fp_toggle");
		KeyBind(&SettingsMgr->iPlayLastAnimKey, "Play Last Animation", "last_anim");
		ImGui::Separator();

		if (m_bPressingKey)
		{
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				*m_pCurrentVarToChange = result;
				m_bPressingKey = false;
			}

		}
		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved!");
		eDirectX9Hook::ms_bShouldReloadFonts = true;
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

void ScarfaceMenu::DrawKeyBind(char* name, int* var)
{
	ImGui::SameLine();

	static char butName[256] = {};
	sprintf(butName, "%s##key%s", eKeyboardMan::KeyToString(*var), name);
	if (ImGui::Button(butName))
	{
		m_bPressingKey = true;
		m_pCurrentVarToChange = var;
	}
}

void ScarfaceMenu::KeyBind(int* var, char* bindName, char* name)
{
	ImGui::LabelText("", bindName);
	DrawKeyBind(name, var);
}

void ScarfaceMenu::Process()
{
	//// player only
	if (!SettingsMgr->bUseAlternateMethodToDisableInput)
	{
		if (m_bAirbreak)
			hooks::DisableInput();
		else
			hooks::EnableInput();
	}
	else
	{
		if (m_bIsActive)
		{
			hooks::DisableInput();
			hooks::DisableMouse();
		}
		else if (m_bAirbreak || m_bFreeCam)
		{
			hooks::DisableInput();
			hooks::EnableMouse();
		}
		else
		{
			hooks::EnableInput();
			hooks::EnableMouse();
		}
	}


	if (!m_bIsActive)
	{
		if (GetAsyncKeyState(SettingsMgr->iToggleFirstPersonKey) & 0x1)
			fps.enabled ^= 1;
	}

	gTonyIsInvincible = m_bForceInvincibility;


	if (CharacterObject* plr = GetMainCharacter())
	{
		if (m_bInfiniteAmmo)
			plr->InfiniteAmmo(m_bInfiniteAmmo);

		if (m_bForceInvincibility)
			plr->SetHealth(1000.0f);
	}


	if (m_bFreeCam)
	{
		Matrix matrix = TheCamera->GetMatrix();

		Vector fwd = matrix.GetForward();
		Vector strafe = matrix.GetRight();
		Vector up = matrix.GetUp();

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyForward))
			camPos += fwd * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * 1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyBack))
			camPos += fwd * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * -1;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyLeft))
			camPos += strafe * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * -1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRight))
			camPos += strafe * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * 1;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyUp))
			camPos += up * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * 1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyDown))
			camPos += up * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * -1;
	}


	if (m_bAirbreak)
	{
		m_bDisableFallDamage = true;
		m_bForceInvincibility = true;

		Matrix matrix = TheCamera->GetMatrix();

		Vector fwd = matrix.GetForward();
		Vector strafe = matrix.GetRight();
		Vector up = matrix.GetUp();

		Vector pos = GetMainCharacter()->GetLocation();

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyForward))
			pos += fwd * TheMenu->m_fAirbreakSpeed * GetDeltaTime() * 1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyBack))
			pos += fwd * TheMenu->m_fAirbreakSpeed * GetDeltaTime() * -1;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyLeft))
			pos += strafe * TheMenu->m_fAirbreakSpeed * GetDeltaTime() * -1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRight))
			pos += strafe * TheMenu->m_fAirbreakSpeed * GetDeltaTime() * 1;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyUp))
			pos += up * TheMenu->m_fAirbreakSpeed * GetDeltaTime() * 1;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyDown))
			pos += up * TheMenu->m_fAirbreakSpeed * GetDeltaTime() * -1;

		setPlayerPosition(pos);
	}

	if (m_bDisableFallDamage)
	{
		Memory::VP::Patch<int>(0x579183 + 3, 1000);
		Memory::VP::Patch<int>(0x579264 + 3, 1000);
	}
	else
	{
		Memory::VP::Patch<int>(0x579183 + 3, 0);
		Memory::VP::Patch<int>(0x579264 + 3, 0);
	}

	Notifications->Update();
}

void ScarfaceMenu::LoadLocationFile()
{
	static CIniReader locations("scfhook_locations.ini");
	locIni = &locations;

	for (int i = 0; i < MAX_TELEPORTS; i++)
	{
		char str[128] = {};
		sprintf(str, "Place%d", i);

		bool is_set = locations.ReadBoolean(str, "is_set", false);
		if (is_set)
		{
			TeleporterPlace place;
			Vector tpPos = {};
			tpPos.X = locations.ReadFloat(str, "x", 0.0f);
			tpPos.Y = locations.ReadFloat(str, "y", 0.0f);
			tpPos.Z = locations.ReadFloat(str, "z", 0.0f);

			place.pos = tpPos;
			sprintf(place.name, "%s", locations.ReadString(str, "name", str));
			vTeleports.push_back(place);
		}
	}

}

bool ImGui::_Checkbox(const char* label, bool* v)
{
	bool result = ImGui::Checkbox(label, v);
	if (result) Frontend_PlaySound("toggle");
	return result;
}

float GetDeltaTime()
{
	float delta = 1.0f / 60.0f;

	if (eDirectX9Hook::ms_bInit)
		delta = 1.0f / ImGui::GetIO().Framerate;

	return delta;
}

void ExplodeAllPeds()
{
	GameSet<CharacterObject>* characters = CVManager::GetInstance()->GetCharacters();

	for (int i = 0; i < characters->Count(); i++)
	{
		CharacterObject* p = characters->Get(i);
		if (p == GetMainCharacter())
			continue;
		ExplosionTemplate* explosion = FindExplosion("ExplosionTemplateEcopropLarge");
		if (explosion)
		{
			Vector pos = p->GetLocation();
			EffectsObject::GetInstance()->PlayPedExplosion(&pos);
			pos.Y += 1.5f;
			explosion->Explode(&pos);

		}

	}
}

void MakeAllPedsDance()
{
	GameSet<CharacterObject>* characters = CVManager::GetInstance()->GetCharacters();

	for (int i = 0; i < characters->Count(); i++)
	{
		CharacterObject* p = characters->Get(i);
		if (p == GetMainCharacter())
			continue;

		if (p)
		{
			p->ResetAnimation();
			p->PlayAnimation("Dancing_State", 0);
			p->SetPhysicalMode("Dancing_State");
		}

	}
}
