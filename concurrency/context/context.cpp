#include "context.hpp"


namespace concurrency::contex {

// Empty context, cannot be a target for SwitchTo
ExecutionContext::ExecutionContext()
{

}

// Prepare execution context for running trampoline->Run()
// on stack 'stack'
void ExecutionContext::Setup(concurrency::core::memory::MutableMemView stack, concurrency::ITrampoline* trampoline)
{
    user_trampoline_ = trampoline;
    machine_.Setup(stack, this);
    //sanitizer_.Setup(stack);
}

// Symmetric Control Transfer
// 1) Save current execution context to 'this'
// 2) Activate 'target' context
void ExecutionContext::SwitchTo(ExecutionContext& target)
{
    // exceptions.SwitchTo(target.exceptions_);

    // NB: __tsan_switch_to_fiber should be called immediately before switch to fiber
    // https://github.com/llvm/llvm-project/blob/712dfec1781db8aa92782b98cac5517db548b7f9/compiler-rt/include/sanitizer/tsan_interface.h#L150-L151
    //sanitizer_.BeforeSwitch(target.sanitizer_);

    //Switch stacks
    machine_.SwitchTo(target.machine_);

    //sanitizer.AfterSwitch();
}

[[noreturn]] void ExecutionContext::ExitTo(ExecutionContext& target)
{
    // exceptions_.SwitchTo(target.exceptions_);

    // NB: __tsan_switch_to_fiber should be called immediately before switch to fiber
    // sanitizer_.BeforeExit(target.sanitizer_);

    // Switch stacks
    machine_.SwitchTo(target.machine_);

    // Unreachable
    std::abort();
}


// ITrampoline
void ExecutionContext::Run() noexcept
{
    AfterStart();
    user_trampoline_->Run();
}

// Finalize first context seitch
void ExecutionContext::AfterStart()
{
    //sanitizer_.AfterStart();
}


} // namespace concurrency::context