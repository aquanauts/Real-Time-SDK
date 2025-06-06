
set( SOURCE_FILES
    transportPerfConfig.c       transportThreads.c   TransportPerf.c
    ${EtaExamples_SOURCE_DIR}/PerfTools/Common/channelHandler.c
    ${EtaExamples_SOURCE_DIR}/PerfTools/Common/latencyRandomArray.c
    ${EtaExamples_SOURCE_DIR}/PerfTools/Common/statistics.c
  )

add_executable( TransportPerf_shared ${SOURCE_FILES} )
target_include_directories(TransportPerf_shared
							PUBLIC
								$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
								$<BUILD_INTERFACE:${EtaExamples_SOURCE_DIR}/PerfTools/Common>
							)
set_target_properties( TransportPerf_shared 
							PROPERTIES 
								OUTPUT_NAME TransportPerf 
							)
target_link_libraries( TransportPerf_shared 
							librsslVA_shared 
							LibXml2::LibXml2 
							${SYSTEM_LIBRARIES} 
							)

add_executable( TransportPerf ${SOURCE_FILES} )
target_include_directories(TransportPerf
							PUBLIC
								$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
								$<BUILD_INTERFACE:${EtaExamples_SOURCE_DIR}/PerfTools/Common>
							)
target_link_libraries( TransportPerf 
							librsslVA  
							LibXml2::LibXml2 
							${SYSTEM_LIBRARIES} 
							)

if ( CMAKE_HOST_UNIX )
    set_target_properties( TransportPerf 
                            PROPERTIES 
                                OUTPUT_NAME TransportPerf 
                                RUNTIME_OUTPUT_DIRECTORY 
                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
							)
	set_target_properties( TransportPerf_shared 
                            PROPERTIES 
                                RUNTIME_OUTPUT_DIRECTORY 
                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shared 
							)

else() # if ( CMAKE_HOST_WIN32 )
    set_target_properties(TransportPerf 
                            PROPERTIES 
                                PROJECT_LABEL "TransportPerf" 
                                RUNTIME_OUTPUT_DIRECTORY_RELEASE_MD 
                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE_MD}
                                RUNTIME_OUTPUT_DIRECTORY_DEBUG_MDD 
                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG_MDD}
								PDB_OUTPUT_DIRECTORY_RELEASE_MD 
									${CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE_MD}
								PDB_OUTPUT_DIRECTORY_DEBUG_MDD 
									${CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG_MDD}
							)
	target_compile_options( TransportPerf	 
								PRIVATE 
									${RCDEV_DEBUG_TYPE_FLAGS_NONSTATIC}
									${RCDEV_TYPE_CHECK_FLAG}
									$<$<CONFIG:Release_MD>:${RCDEV_FLAGS_NONSTATIC_RELEASE}>
						)
    set_target_properties( TransportPerf_shared 
                            PROPERTIES 
                                PROJECT_LABEL "TransportPerf_shared" 
                                RUNTIME_OUTPUT_DIRECTORY_RELEASE_MD 
                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE_MD}/Shared 
                                RUNTIME_OUTPUT_DIRECTORY_DEBUG_MDD 
                                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG_MDD}/Shared
								LIBRARY_OUTPUT_DIRECTORY_RELEASE_MD
                                    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE_MD}/Shared
                                LIBRARY_OUTPUT_DIRECTORY_DEBUG_MDD
                                    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG_MDD}/Shared
								PDB_OUTPUT_DIRECTORY_RELEASE_MD 
									${CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE_MD}/Shared 
								PDB_OUTPUT_DIRECTORY_DEBUG_MDD 
									${CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG_MDD}/Shared
								ARCHIVE_OUTPUT_DIRECTORY_RELEASE_MD
                                    ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE_MD}/Shared
                                ARCHIVE_OUTPUT_DIRECTORY_DEBUG_MDD
                                    ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG_MDD}/Shared
                          )
	target_compile_options( TransportPerf_shared	 
								PRIVATE 
									${RCDEV_DEBUG_TYPE_FLAGS_NONSTATIC}
									${RCDEV_TYPE_CHECK_FLAG}
									$<$<CONFIG:Release_MD>:${RCDEV_FLAGS_NONSTATIC_RELEASE}>
						)
    target_link_libraries( TransportPerf psapi )
    target_link_libraries( TransportPerf_shared psapi )
endif()


