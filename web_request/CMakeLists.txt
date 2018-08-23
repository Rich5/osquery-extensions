project(web_request)

function(main)

  find_package(CURL REQUIRED)
  list(APPEND PROJECT_LIBRARIES
    ${CURL_LIBRARIES}
  )

  set(PROJECT_SOURCEFILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/web_request.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/web_request.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/client.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp"
  )


  add_osquery_extension_ex("WebRequestTable" "table" "web_request"
    SOURCES ${PROJECT_SOURCEFILES}
    INCLUDEDIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" ${CURL_INCLUDE_DIRS}
    MAININCLUDES "web_request.h"
    LIBRARIES ${PROJECT_LIBRARIES}
  )
endfunction()

main()
