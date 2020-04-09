#include "Commander.hpp"
#include "Program.hpp"

int main() {
    build_commands();
    Commander::run(Program::self());
    return 0;
}
