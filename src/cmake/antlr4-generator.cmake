# Helper macro to resolve the ANTLR4 generator tool (Java + antlr-4.x-complete.jar).
#
# Parameters:
# ANTLR4_VERSION          - ANTLR4 version string, e.g. 4.13.2
# OUT_ENABLED_VAR         - Output variable set to ON/OFF for generator availability
# OUT_JAVA_EXECUTABLE_VAR - Output variable containing Java executable path
# OUT_JAR_PATH_VAR        - Output variable containing ANTLR4 JAR path
macro(yaip_configure_antlr4_generator ANTLR4_VERSION OUT_ENABLED_VAR OUT_JAVA_EXECUTABLE_VAR OUT_JAR_PATH_VAR)
    set(ANTLR4_JAR "" CACHE FILEPATH "Path to antlr-4.x-complete.jar used for parser generation")

    set(_YAIP_ANTLR_GENERATION_ENABLED ON)

    find_package(Java COMPONENTS Runtime QUIET)

    if(Java_Runtime_FOUND)
        if(NOT ANTLR4_JAR)
            set(ANTLR4_JAR ${CMAKE_BINARY_DIR}/antlr-${ANTLR4_VERSION}-complete.jar)
        endif()

        if(NOT EXISTS ${ANTLR4_JAR})
            file(DOWNLOAD
                https://www.antlr.org/download/antlr-${ANTLR4_VERSION}-complete.jar
                ${ANTLR4_JAR}
                STATUS _ANTLR_DOWNLOAD_STATUS
                SHOW_PROGRESS
                TLS_VERIFY ON
            )

            list(GET _ANTLR_DOWNLOAD_STATUS 0 _ANTLR_DOWNLOAD_CODE)

            if(NOT _ANTLR_DOWNLOAD_CODE EQUAL 0)
                message(WARNING "Failed to download ANTLR tool JAR (${_ANTLR_DOWNLOAD_STATUS}). Falling back to checked-in generated parser sources.")
                set(_YAIP_ANTLR_GENERATION_ENABLED OFF)
            endif()
        endif()
    else()
        message(WARNING "ANTLR code generation requires a Java runtime. Falling back to checked-in generated parser sources.")
        set(_YAIP_ANTLR_GENERATION_ENABLED OFF)
    endif()

    if(_YAIP_ANTLR_GENERATION_ENABLED)
        set(${OUT_JAVA_EXECUTABLE_VAR} ${Java_JAVA_EXECUTABLE})
        set(${OUT_JAR_PATH_VAR} ${ANTLR4_JAR})
    endif()

    set(${OUT_ENABLED_VAR} ${_YAIP_ANTLR_GENERATION_ENABLED})
endmacro()
