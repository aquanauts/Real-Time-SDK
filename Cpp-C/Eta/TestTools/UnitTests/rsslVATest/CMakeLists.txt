set(rsslVATestSrcFiles
	reactorUnitTests.cpp
	rdmDictionaryMsgTests.cpp
	rdmDirectoryMsgTests.cpp
	rdmLoginMsgTests.cpp
	rsslTestFramework.cpp
	rsslUnitTests.cpp
	rsslVATest.cpp
	rsslVATestUtil.cpp
	testFramework.cpp
	watchlistAggregationUnitTests.cpp
	watchlistDirectoryUnitTests.cpp
	watchlistMiscUnitTests.cpp
	watchlistPreferredHostUnitTests.cpp
	watchlistRecoveryUnitTests.cpp
	watchlistSymbolListUnitTests.cpp
	watchlistWarmStandbyUnitTests.cpp
	watchlistTestFramework.cpp
	
	#headers
	rsslTestFramework.h
	rsslVATestUtil.h
	testFramework.h
	watchlistTestFramework.h
)



add_executable( rsslVATest ${rsslVATestSrcFiles} )
target_link_libraries( rsslVATest 
							librsslVA 
							GTest::Main 
							${SYSTEM_LIBRARIES} 
						)
set_target_properties( rsslVATest 
							PROPERTIES 
								OUTPUT_NAME rsslVATest 
						)

target_include_directories(rsslVATest
							PUBLIC
								$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
								#Needed for testing of internal functionality
								$<BUILD_INTERFACE:${Eta_SOURCE_DIR}/Impl/Reactor/Watchlist>
								$<BUILD_INTERFACE:${Eta_SOURCE_DIR}/Impl/Reactor/Util>
								$<BUILD_INTERFACE:${Eta_SOURCE_DIR}/Impl/Util/Include>
							)


if( CMAKE_HOST_WIN32 )

	#This definition is required for using google test with VS2012.
	if (MSVC AND MSVC_VERSION EQUAL 1700)
		add_definitions(/D _VARIADIC_MAX=10)
	endif()
	target_compile_options( rsslVATest	 
								PRIVATE 
									${RCDEV_DEBUG_TYPE_FLAGS_NONSTATIC}
									${RCDEV_TYPE_CHECK_FLAG}
									${RTSDK_EXTRA_FLAGS}
									$<$<CONFIG:Release_MD>:${RCDEV_FLAGS_NONSTATIC_RELEASE}>
						)
	set_target_properties( rsslVATest 
							PROPERTIES 
								PROJECT_LABEL "rsslVATest" 
							)
else()
	target_compile_options( rsslVATest	 
								PRIVATE 
									${RTSDK_EXTRA_FLAGS}
						)
endif()

if ( CMAKE_HOST_UNIX )

    add_custom_command(
                    TARGET rsslVATest POST_BUILD

                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/enumtype.def
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/enumtype.def
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/RDMFieldDictionary
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RDMFieldDictionary
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/RDMFieldDictionary_large
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RDMFieldDictionary_large

                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    COMMENT "Copying enumtype.def, RDMFieldDictionary and RDMFieldDictionary_large for Eta VATest Unit Tests .... "
                    )

else()

    add_custom_command(
                    TARGET rsslVATest POST_BUILD

                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/enumtype.def
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE_MD}/enumtype.def
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/RDMFieldDictionary
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE_MD}/RDMFieldDictionary
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/RDMFieldDictionary_large
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE_MD}/RDMFieldDictionary_large
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/enumtype.def
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG_MDD}/enumtype.def
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/RDMFieldDictionary
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG_MDD}/RDMFieldDictionary
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../../../etc/RDMFieldDictionary_large
                            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG_MDD}/RDMFieldDictionary_large

                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    COMMENT "Copying enumtype.def, RDMFieldDictionary and RDMFieldDictionary_large for Eta VATest Unit Tests .... "
                    )

endif()