add_executable (test_hayne test_hayne.cpp)
add_executable (test_kdtree test_kdtree.cpp)
add_executable (test_find_within_range test_find_within_range.cpp)

add_test(test_hayne test_hayne)
add_test(test_kdtree test_kdtree)
add_test(test_find_within_range test_find_within_range)
