set(OS_RELEASE_DISTRO_REGEX "{s/.*\(.*\).*/\\1/;}")
set(DISTRO_RELEASE_REGEX "{s/.*=\(.*\)$/\\1/;q;}")
set(LSB_RELEASE_REGEX "s/.*:\(.*\)$/\\1/")
set(TRIM_VARIABLE_REGEX "{s/^[ \"\t\r]*//;s/[ \"\t\r\\r(\\l)(\\m) ]*$//;q;}")
set(REMOVE_NOT_MATCHED_OS "/^NAME[ ]*=[ ]*/!d")
set(REMOVE_NOT_MATCHED_LSB "/^Distributor[ ]*ID:[ ]*/!d")


find_program(CAT cat /bin /usr/bin /usr/local/bin )
find_program(SED sed /bin /usr/bin /usr/local/bin )
    
exec_program(${CAT} ARGS /etc/os-release OUTPUT_VARIABLE OS_RELEASE_TEXT)
exec_program(${SED} ARGS -e ${REMOVE_NOT_MATCHED_OS} -e ${OS_RELEASE_DISTRO_REGEX} ${OS_RELEASE_TEXT} OUTPUT_VARIABLE OS_RELEASE_DISTRO)  

find_program(LSB_RELEASE lsb_release /bin /usr/bin /usr/local/bin )
            
if(LSB_RELEASE)
    exec_program(${LSB_RELEASE} ARGS -a OUTPUT_VARIABLE LSB_RELEASE_TEXT)
    exec_program(${SED} ARGS -e ${REMOVE_NOT_MATCHED_LSB} -n ${LSB_RELEASE_REGEX} -e ${TRIM_VARIABLE_REGEX} ${LSB_RELEASE_TEXT} OUTPUT_VARIABLE LSB_RELEASE_DISTRO) 
endif()
