if(UNIX)
	set(EXTRA_LIBS pthread)
else()
	set(EXTRA_LIBS shlwapi.lib)
endif()

add_executable(dictionary_v3
	benchmark.cc
	dictionary.hh
  hashtable.hh
	string_view.hh
)

target_link_libraries(dictionary_v3
	benchmark
	${EXTRA_LIBS} papi
)
