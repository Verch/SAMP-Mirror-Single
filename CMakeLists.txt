cmake_minimum_required(VERSION 2.6)

set(cmake_archive_output_directory ${CMAKE_HOME_DIRECTORY}/bin)
set(cmake_library_output_directory ${CMAKE_HOME_DIRECTORY}/bin)
set(cmake_runtime_output_directory ${CMAKE_HOME_DIRECTORY}/bin)

project(MirrorSync3)

file( GLOB SOURCE_CODE
	 	source/main.cpp
	source/udpserver.cpp
	source/udpserver.h
	source/compute.cpp
	source/compute.h
	source/dataAnswer.cpp
	source/dataAnswer.h
	source/DataBase.cpp
	source/DataBase.h
	source/GameLogic.cpp
	source/GameLogic.h
	source/GameObject_List.cpp
	source/GameObject_List.h
	source/Logic.cpp
	source/Logic.h
	source/MyUtiles.cpp
	source/MyUtiles.h
	source/PackageRules.cpp
	source/PlayerManager.cpp
	source/PlayerManager.h
	source/VehicleManager.cpp
	source/VehicleManager.h
	source/sender.cpp
	source/sender.h
	source/EventManager.cpp
	source/EventManager.h
	source/PackageType.h

	source/BaseType.cpp
	source/BaseType.h	
	)
source_group("" FILES ${SOURCE_CODE})

option(Boost_USE_STATIC_LIBS    "Set to ON to force the use of the static libraries."                                                  ON)
option(Boost_USE_MULTITHREADED  "Set to OFF to use the non-multithreaded libraries                                         ('mt' tag)" ON)  
option(Boost_USE_STATIC_RUNTIME "Set to ON or OFF to specify whether to use libraries linked statically to the C++ runtime ('s' tag) " ON)
option(Boost_USE_DEBUG_RUNTIME  "Set to ON or OFF to specify whether to use libraries linked to the MS debug C++ runtime   ('g' tag) " ON)
 
find_package(Boost COMPONENTS system filesystem program_options date_time regex thread chrono REQUIRED)

if(Boost_FOUND)

	if(MSVC)
		if (COMMAND cmake_policy)
		CMAKE_POLICY(SET CMP0003 NEW)
		endif(COMMAND cmake_policy)

		set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   /MTd /Zi /Ob0 /Od /EHsc /RTC1 /D_DEBUG")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /O2 /Ob2") 

		add_definitions(-D _CRT_SECURE_NO_WARNINGS)
		add_definitions(/sdl /EHsc /Od /RTC1 /GS)
	endif()

    if(UNIX)
        add_definitions("-std=c++11")
        add_definitions("-O3")

        add_definitions("-static")
        add_definitions("-static-libgcc")
        add_definitions("-static-libstdc++")
    endif()
	
	include_directories(${Boost_INCLUDE_DIR})
	add_executable(MirrorSync3 ${SOURCE_CODE})
	target_link_libraries(MirrorSync3 ${Boost_LIBRARIES})
endif()