if(UNIX)
	set(EXTRA_LIBS pthread)
else()
	set(EXTRA_LIBS shlwapi.lib)
endif()

add_executable(dictionary_v2
	benchmark.cc
	dictionary.hh
	string_view.hh
)

target_link_libraries(dictionary_v2
	benchmark
	${EXTRA_LIBS}
)
