#pragma once

// #include <concurrency/context/context.hpp>
#include <concurrency/context/trampoline.hpp>
#include <concurrency/core/memory/view.hpp>

// Switch between MachineContex-s
extern "C" void SwitchMachineContext(void* from_rsp, void* to_rsp);

namespace concurrency::contex::machine {

struct MachineContext
{
    void* rsp_;

    void Setup(concurrency::core::memory::MutableMemView stack, concurrency::ITrampoline* trampoline);

    void SwitchTo(MachineContext& target)
    {
        SwitchMachineContext(&rsp_, &target.rsp_);
    }

    void* TryStackPointer() const
    {
        return rsp_;
    }
};


} // namespace concurrency::context::machine