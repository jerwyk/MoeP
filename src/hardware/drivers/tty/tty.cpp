#include <hardware/tty.h>

using namespace MoeP;
using namespace MoeP::hardware;

TtyDriver::TtyDriver(kernel::InterruptManager *manager)
{
    //well we dont really have a heap
    keyboard = &KeyboardDriver(manager);
    console = &ConsoleDriver();
}