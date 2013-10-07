cmake_minimum_required(VERSION 2.8.8)

# Make sure the user is not executing this script directly
if(NOT InOpenJK)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InOpenJK)

set(MPGameIncludeDirectories "${MPDir}" "${MPDir}/libraries" "${MPDir}/libraries/libcurl/include" "${MPDir}/libraries/Detour/include" "${MPDir}/libraries/Recast/include")
set(MPGameLibraries "libeay32")
if(WIN32)
	set(MPGameLibraries ${MPGameLibraries} "winmm" "ws2_32" "dbghelp" "psapi")
endif(WIN32)
set(MPGameDefines ${MPSharedDefines} "QAGAME" "MISSIONPACK" "_PHASE1" "CURL_STATICLIB" )
set(MPGameGameFiles
	"${MPDir}/game/ai_dominance.cpp"
	"${MPDir}/game/ai_dominance_astar.cpp"
	"${MPDir}/game/ai_dominance_bot.cpp"
	"${MPDir}/game/ai_dominance_evasion.cpp"
	"${MPDir}/game/ai_main.cpp"
	"${MPDir}/game/ai_util.cpp"
	"${MPDir}/game/ai_wpnav.cpp"
	"${MPDir}/game/bg_ammo.cpp"
	"${MPDir}/game/bg_constants.cpp"
	"${MPDir}/game/bg_g2_utils.cpp"
	"${MPDir}/game/bg_items.cpp"
	"${MPDir}/game/bg_misc.cpp"
	"${MPDir}/game/bg_panimate.cpp"
	"${MPDir}/game/bg_pmove.cpp"
	"${MPDir}/game/bg_saber.cpp"
	"${MPDir}/game/bg_saberLoad.cpp"
	"${MPDir}/game/bg_slidemove.cpp"
	"${MPDir}/game/bg_vehicleLoad.cpp"
	"${MPDir}/game/bg_vmove.cpp"
	"${MPDir}/game/bg_weapons.cpp"
	"${MPDir}/game/bg_weapons_load.cpp"
	"${MPDir}/game/g_active.cpp"
	"${MPDir}/game/g_bot.cpp"
	"${MPDir}/game/g_client.cpp"
	"${MPDir}/game/g_cmds.cpp"
	"${MPDir}/game/g_combat.cpp"
	"${MPDir}/game/g_exphysics.cpp"
	"${MPDir}/game/g_ICARUScb.cpp"
	"${MPDir}/game/g_items.cpp"
	"${MPDir}/game/g_log.cpp"
	"${MPDir}/game/g_main.cpp"
	"${MPDir}/game/g_mem.cpp"
	"${MPDir}/game/g_misc.cpp"
	"${MPDir}/game/g_missile.cpp"
	"${MPDir}/game/g_mover.cpp"
	"${MPDir}/game/g_nav.cpp"
	"${MPDir}/game/g_navnew.cpp"
	"${MPDir}/game/g_object.cpp"
	"${MPDir}/game/g_session.cpp"
	"${MPDir}/game/g_spawn.cpp"
	"${MPDir}/game/g_strap.cpp"
	"${MPDir}/game/g_svcmds.cpp"
	"${MPDir}/game/g_syscalls.cpp"
	"${MPDir}/game/g_target.cpp"
	"${MPDir}/game/g_team.cpp"
	"${MPDir}/game/g_timer.cpp"
	"${MPDir}/game/g_trigger.cpp"
	"${MPDir}/game/g_turret.cpp"
	"${MPDir}/game/g_turret_G2.cpp"
	"${MPDir}/game/g_utils.cpp"
	"${MPDir}/game/g_vehicles.cpp"
	"${MPDir}/game/g_vehicleTurret.cpp"
	"${MPDir}/game/g_weapon.cpp"
	"${MPDir}/game/NPC.cpp"
	"${MPDir}/game/NPC_AI_Atst.cpp"
	"${MPDir}/game/NPC_AI_Default.cpp"
	"${MPDir}/game/NPC_AI_Droid.cpp"
	"${MPDir}/game/NPC_AI_GalakMech.cpp"
	"${MPDir}/game/NPC_AI_Grenadier.cpp"
	"${MPDir}/game/NPC_AI_Howler.cpp"
	"${MPDir}/game/NPC_AI_Humanoid.cpp"
	"${MPDir}/game/NPC_AI_ImperialProbe.cpp"
	"${MPDir}/game/NPC_AI_Interrogator.cpp"
	"${MPDir}/game/NPC_AI_Mark1.cpp"
	"${MPDir}/game/NPC_AI_Mark2.cpp"
	"${MPDir}/game/NPC_AI_MineMonster.cpp"
	"${MPDir}/game/NPC_AI_Rancor.cpp"
	"${MPDir}/game/NPC_AI_Remote.cpp"
	"${MPDir}/game/NPC_AI_Seeker.cpp"
	"${MPDir}/game/NPC_AI_Sentry.cpp"
	"${MPDir}/game/NPC_AI_Sniper.cpp"
	"${MPDir}/game/NPC_AI_Stormtrooper.cpp"
	"${MPDir}/game/NPC_AI_Utils.cpp"
	"${MPDir}/game/NPC_AI_Wampa.cpp"
	"${MPDir}/game/NPC_Animal.cpp"
	"${MPDir}/game/NPC_behavior.cpp"
	"${MPDir}/game/NPC_combat.cpp"
	"${MPDir}/game/NPC_Conversations.cpp"
	"${MPDir}/game/NPC_CoverPoints.cpp"
	"${MPDir}/game/NPC_Fighter.cpp"
	"${MPDir}/game/NPC_goal.cpp"
	"${MPDir}/game/NPC_misc.cpp"
	"${MPDir}/game/NPC_move.cpp"
	"${MPDir}/game/NPC_reactions.cpp"
	"${MPDir}/game/NPC_senses.cpp"
	"${MPDir}/game/NPC_sounds.cpp"
	"${MPDir}/game/NPC_spawn.cpp"
	"${MPDir}/game/NPC_Speeder.cpp"
	"${MPDir}/game/NPC_stats.cpp"
	"${MPDir}/game/NPC_utils.cpp"
	"${MPDir}/game/NPC_Walker.cpp"
	"${MPDir}/game/NPC_Waypointing.cpp"
	"${MPDir}/game/jkg_admin.cpp"
	"${MPDir}/game/jkg_bans.cpp"
	"${MPDir}/game/jkg_chatcmds.cpp"
	"${MPDir}/game/jkg_crafting.cpp"
	"${MPDir}/game/jkg_custombounds.cpp"
	"${MPDir}/game/jkg_damagetypes.cpp"
	"${MPDir}/game/jkg_dynarrays.cpp"
	"${MPDir}/game/jkg_equip.cpp"
	"${MPDir}/game/jkg_item_sub.cpp"
	"${MPDir}/game/jkg_items.cpp"
	"${MPDir}/game/jkg_items_easy.cpp"
	"${MPDir}/game/jkg_keypairs.cpp"
	"${MPDir}/game/jkg_playerisolation.cpp"
	"${MPDir}/game/jkg_rconbans.cpp"
	"${MPDir}/game/jkg_team.cpp"
	"${MPDir}/game/jkg_threading.cpp"
	"${MPDir}/game/jkg_threadingsq.cpp"
	"${MPDir}/game/jkg_utilityfunc.cpp"
	"${MPDir}/game/tri_coll_test.cpp"
	"${MPDir}/game/w_force.cpp"
	"${MPDir}/game/w_melee.cpp"
	"${MPDir}/game/w_saber.cpp"
	"${MPDir}/game/ai.h"
	"${MPDir}/game/ai_main.h"
	"${MPDir}/game/anims.h"
	"${MPDir}/game/aux_exports.h"
	"${MPDir}/game/b_local.h"
	"${MPDir}/game/b_public.h"
	"${MPDir}/game/bg_ammo.h"
	"${MPDir}/game/bg_items.h"
	"${MPDir}/game/bg_lib.h"
	"${MPDir}/game/bg_local.h"
	"${MPDir}/game/bg_public.h"
	"${MPDir}/game/bg_strap.h"
	"${MPDir}/game/bg_vehicles.h"
	"${MPDir}/game/bg_weapons.h"
	"${MPDir}/game/chars.h"
	"${MPDir}/game/g_ICARUScb.h"
	"${MPDir}/game/g_local.h"
	"${MPDir}/game/g_nav.h"
	"${MPDir}/game/g_public.h"
	"${MPDir}/game/g_team.h"
	"${MPDir}/game/g_xcvar.h"
	"${MPDir}/game/inv.h"
	"${MPDir}/game/jkg_admin.h"
	"${MPDir}/game/jkg_asmdefines.h"
	"${MPDir}/game/jkg_bans.h"
	"${MPDir}/game/jkg_chatcmds.h"
	"${MPDir}/game/jkg_crafting.h"
	"${MPDir}/game/jkg_damagetypes.h"
	"${MPDir}/game/jkg_dynarrays.h"
	"${MPDir}/game/jkg_easy_items.h"
	"${MPDir}/game/jkg_gangwars.h"
	"${MPDir}/game/jkg_items.h"
	"${MPDir}/game/jkg_keypairs.h"
	"${MPDir}/game/jkg_libcurl.h"
	"${MPDir}/game/jkg_navmesh_creator.h"
	"${MPDir}/game/jkg_threading.h"
	"${MPDir}/game/jkg_threadingsq.h"
	"${MPDir}/game/jkg_utilityfunc.h"
	"${MPDir}/game/match.h"
	"${MPDir}/game/npc_headers.h"
	"${MPDir}/game/say.h"
	"${MPDir}/game/surfaceflags.h"
	"${MPDir}/game/teams.h"
	"${MPDir}/game/w_saber.h"
	)
source_group("game" FILES ${MPGameGameFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameGameFiles})

set(MPGameGluaFiles
	"${MPDir}/GLua/glua_bitstream.cpp"
	"${MPDir}/GLua/glua_bitwise.cpp"
	"${MPDir}/GLua/glua_cryptography.cpp"
	"${MPDir}/GLua/glua_cvar.cpp"
	"${MPDir}/GLua/glua_encoding.cpp"
	"${MPDir}/GLua/glua_engine.cpp"
	"${MPDir}/GLua/glua_entity.cpp"
	"${MPDir}/GLua/glua_files.cpp"
	"${MPDir}/GLua/glua_json.cpp"
	"${MPDir}/GLua/glua_main.cpp"
	"${MPDir}/GLua/glua_npc.cpp"
	"${MPDir}/GLua/glua_player.cpp"
	"${MPDir}/GLua/glua_prng.cpp"
	"${MPDir}/GLua/glua_sys.cpp"
	"${MPDir}/GLua/glua_vector.cpp"
	"${MPDir}/GLua/glua.h"
	)
source_group("glua" FILES ${MPGameGluaFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameGluaFiles})

set(MPGameCommonFiles
	"${MPDir}/qcommon/q_math.cpp"
	"${MPDir}/qcommon/q_shared.cpp"
	"${MPDir}/qcommon/disablewarnings.h"
	"${MPDir}/qcommon/q_shared.h"
	"${MPDir}/qcommon/tags.h"
	)
source_group("common" FILES ${MPGameCommonFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameCommonFiles})

set(MPGameCgameFiles
	"${MPDir}/cgame/animtable.h"
	"${MPDir}/cgame/cg_local.h"
	"${MPDir}/cgame/cg_public.h"
	)
source_group("cgame" FILES ${MPGameCgameFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameCgameFiles})

set(MPGameRendererFiles
	"${MPDir}/rd-common/tr_types.h"
	)
source_group("rd-common" FILES ${MPGameRendererFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameRendererFiles})

set(MPGameBotlibFiles
	"${MPDir}/botlib/be_aas.h"
	"${MPDir}/botlib/be_ai_char.h"
	"${MPDir}/botlib/be_ai_chat.h"
	"${MPDir}/botlib/be_ai_gen.h"
	"${MPDir}/botlib/be_ai_goal.h"
	"${MPDir}/botlib/be_ai_move.h"
	"${MPDir}/botlib/be_ai_weap.h"
	"${MPDir}/botlib/be_ea.h"
	"${MPDir}/botlib/botlib.h"
	)
source_group("botlib" FILES ${MPGameBotlibFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameBotlibFiles})

set(MPGameG2Files
	"${MPDir}/ghoul2/G2.h"
	)
source_group("ghoul2" FILES ${MPGameG2Files})
set(MPGameFiles ${MPGameFiles} ${MPGameG2Files})

set(MPGameIcarusFiles
	"${MPDir}/icarus/interpreter.h"
	"${MPDir}/icarus/Q3_Interface.h"
	)
source_group("icarus" FILES ${MPGameIcarusFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameIcarusFiles})

set(MPGameUiFiles
	"${MPDir}/ui/menudef.h"
	)
source_group("ui" FILES ${MPGameUiFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameUiFiles})

add_library(${MPGame} SHARED ${MPGameFiles})

if(NOT WIN32)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${MPGame} PROPERTIES PREFIX "")
endif(NOT WIN32)

if(WIN32)
	install(TARGETS ${MPGame} RUNTIME DESTINATION "OpenJK")
else(WIN32)
	install(TARGETS ${MPGame} LIBRARY DESTINATION "OpenJK")
endif(WIN32)
set_target_properties(${MPGame} PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "${MPGameDefines};${ReleaseDefines}")
set_target_properties(${MPGame} PROPERTIES COMPILE_DEFINITIONS_MINSIZEREL "${MPGameDefines};${ReleaseDefines}")
set_target_properties(${MPGame} PROPERTIES COMPILE_DEFINITIONS_RELEASE "${MPGameDefines};${ReleaseDefines}")
set_target_properties(${MPGame} PROPERTIES COMPILE_DEFINITIONS_DEBUG "${MPGameDefines};${DebugDefines}")
set_target_properties(${MPGame} PROPERTIES INCLUDE_DIRECTORIES "${MPGameIncludeDirectories}")
set_target_properties(${MPGame} PROPERTIES PROJECT_LABEL "MP Game Library")
# no libraries used
if(MPGameLibraries)
	target_link_libraries(${MPGame} ${MPGameLibraries})
endif(MPGameLibraries)
