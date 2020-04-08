#include "Commander.hpp"
#include "Program.hpp"

int main() {
    build_commands();
    Program p;
    Commander::run(p);
    return 0;
}
