if(UNIX)
	set(EXTRA_LIBS pthread)
else()
	set(EXTRA_LIBS shlwapi.lib)
endif()

add_executable(dictionary_v1
	benchmark.cc
	dictionary.hh
	string_view.hh
)

target_link_libraries(dictionary_v1
	benchmark
	${EXTRA_LIBS}
)
