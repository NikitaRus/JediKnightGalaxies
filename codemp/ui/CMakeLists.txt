cmake_minimum_required(VERSION 2.8.8)

# Make sure the user is not executing this script directly
if(NOT InOpenJK)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InOpenJK)

set(MPUIIncludeDirectories "${MPDir}" "${MPDir}/libraries" "${MPDir}/game" "${MPDir}/libraries/libexpat/include" ${BoostDirectory})
if(WIN32)
    set(MPUILibraries "${MPDir}/libraries/libexpat/lib/libexpatMT.lib")
else(WIN32)
    set(MPUILibraries "${MPDir}/libraries/libexpat/lib/libexpatMT")
endif(WIN32)

if(WIN32)
	set(MPUILibraries "${MPUILibraries}" "odbc32" "odbccp32" "winmm")
endif(WIN32)
set(MPUIDefines ${MPSharedDefines} "UI_EXPORTS" "MISSIONPACK" "_USRDLL" "UI")

set(MPUIGameFiles
    "${MPDir}/game/animtable.cpp"
	"${MPDir}/game/bg_ammo.cpp"
	"${MPDir}/game/bg_constants.cpp"
	"${MPDir}/game/bg_lib.cpp"
	"${MPDir}/game/bg_misc.cpp"
	"${MPDir}/game/bg_vehicleLoad.cpp"
	"${MPDir}/game/bg_weapons.cpp"
	"${MPDir}/game/bg_weapons_load.cpp"
	"${MPDir}/game/anims.h"
	"${MPDir}/game/bg_local.h"
	"${MPDir}/game/bg_public.h"
	"${MPDir}/game/bg_strap.h"
	"${MPDir}/game/bg_weapons.h"
	"${MPDir}/game/surfaceflags.h"
	)
source_group("game" FILES ${MPUIGameFiles})
set(MPUIFiles ${MPUIFiles} ${MPUIGameFiles})

set(MPJSONFiles "${MPDir}/libraries/json/cJSON.c" "${MPDir}/libraries/json/cJSON.h")
source_group("json" FILES ${MPJSONFiles})
set(MPUIFiles ${MPUIFiles} ${MPJSONFiles})

set(MPUICommonFiles
	"${MPDir}/qcommon/q_math.cpp"
	"${MPDir}/qcommon/q_shared.cpp"
	"${MPDir}/qcommon/disablewarnings.h"
	"${MPDir}/qcommon/game_version.h"
	"${MPDir}/qcommon/q_shared.h"
	"${MPDir}/qcommon/qfiles.h"
	"${MPDir}/qcommon/tags.h"
	)
source_group("common" FILES ${MPUICommonFiles})
set(MPUIFiles ${MPUIFiles} ${MPUICommonFiles})

set(MPUIUIFiles
	"${MPDir}/ui/ui_atoms.cpp"
	"${MPDir}/ui/ui_crossover.cpp"
	"${MPDir}/ui/ui_force.cpp"
	"${MPDir}/ui/ui_gameinfo.cpp"
	"${MPDir}/ui/ui_jkgscript.cpp"
	"${MPDir}/ui/ui_main.cpp"
	"${MPDir}/ui/ui_saber.cpp"
	"${MPDir}/ui/ui_shared.cpp"
    "${MPDir}/ui/ui_strap.cpp"
	"${MPDir}/ui/ui_syscalls.cpp"
	"${MPDir}/ui/keycodes.h"
	"${MPDir}/ui/menudef.h"
	"${MPDir}/ui/ui_force.h"
	"${MPDir}/ui/ui_local.h"
	"${MPDir}/ui/ui_public.h"
	"${MPDir}/ui/ui_shared.h"
	)
source_group("ui" FILES ${MPUIUIFiles})
set(MPUIFiles ${MPUIFiles} ${MPUIUIFiles})

set(MPUIUIModuleFiles
    "${MPDir}/ui/jkg_conversations.cpp"
    "${MPDir}/ui/jkg_gangwars_ui.cpp"
    "${MPDir}/ui/jkg_inventory.cpp"
    "${MPDir}/ui/jkg_loot.cpp"
    "${MPDir}/ui/jkg_partymanager.cpp"
    "${MPDir}/ui/jkg_pazaak.cpp"
    "${MPDir}/ui/jkg_shop.cpp"
    "${MPDir}/ui/jkg_slice.cpp"
    )
source_group("modules" FILES ${MPUIUIModuleFiles})
set(MPUIFiles ${MPUIFiles} ${MPUIUIModuleFiles})

set(MPUIRendererFiles
	"${MPDir}/rd-common/tr_types.h"
	)
source_group("rd-common" FILES ${MPUIRendererFiles})
set(MPUIFiles ${MPUIFiles} ${MPUIRendererFiles})

add_library(${MPUI} SHARED ${MPUIFiles})

if(NOT WIN32)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${MPUI} PROPERTIES PREFIX "")
endif(NOT WIN32)

if(WIN32)
	install(TARGETS ${MPUI} RUNTIME DESTINATION "JKGalaxies")
else(WIN32)
	install(TARGETS ${MPUI} LIBRARY DESTINATION "JKGalaxies")
endif(WIN32)
set_target_properties(${MPUI} PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "${MPUIDefines};${ReleaseDefines}")
set_target_properties(${MPUI} PROPERTIES COMPILE_DEFINITIONS_MINSIZEREL "${MPUIDefines};${ReleaseDefines}")
set_target_properties(${MPUI} PROPERTIES COMPILE_DEFINITIONS_RELEASE "${MPUIDefines};${ReleaseDefines}")
set_target_properties(${MPUI} PROPERTIES COMPILE_DEFINITIONS_DEBUG "${MPUIDefines};${DebugDefines}")
set_target_properties(${MPUI} PROPERTIES INCLUDE_DIRECTORIES "${MPUIIncludeDirectories}")
set_target_properties(${MPUI} PROPERTIES PROJECT_LABEL "MP UI Library")
# no libraries used
if(MPUILibraries)
	target_link_libraries(${MPUI} ${MPUILibraries})
endif(MPUILibraries)
