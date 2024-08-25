#include "context.hpp"


extern "C" void* SetupMachineContext(void* stack, void* trampoline, void* arg);


namespace concurrency::contex::machine {

// https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/
void MachineContextTrampoline(void*, void*, void*, void*, void*, void*, void* arg7)
{
    concurrency::ITrampoline* t = (concurrency::ITrampoline*)arg7;
    t->Run();
}

void MachineContext::Setup(concurrency::core::memory::MutableMemView stack, concurrency::ITrampoline* trampoline)
{
    rsp_ = SetupMachineContext((void*)stack.End(), (void*)MachineContextTrampoline, trampoline);
}

} // namepsace concurrency::contex::machine