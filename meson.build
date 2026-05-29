project('toast', 'cpp', default_options: ['cpp_std=c++23'])
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
TOAST_TESTS = ['test/toast.cc']
TOAST_INCLUDES = include_directories('src')
toast_test = executable(
    'unit_tests',
    sources: [TOAST_TESTS],
    include_directories: [TOAST_INCLUDES],
    dependencies: [gmock_dep, gtest_dep],
)
test('unit_tests', toast_test)
