#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define ___TEST_FILE_NAME___ "test.tmp"
#include "appointment_tests.hpp"
#include "calendar_tests.hpp"

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#include "Commander.hpp"
#include "Program.hpp"

int main() {
    doctest::Context().run();

    build_commands();
    Commander::run(Program::self());
    return 0;
}
