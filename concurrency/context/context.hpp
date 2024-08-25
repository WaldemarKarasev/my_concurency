#pragma once


#include <concurrency/stack/stack.hpp>
#include <concurrency/context/trampoline.hpp>
// #if X86
#include <concurrency/context/machine/x86_64/context.hpp>
// #endif




namespace concurrency::contex {

class ExecutionContext : private concurrency::ITrampoline 
{
public:
    // Empty context, cannot be a target for SwitchTo
    ExecutionContext();

    // Non-copyable
    ExecutionContext(const ExecutionContext&) = delete;
    ExecutionContext& operator=(const ExecutionContext&) = delete;

    // Non movable
    ExecutionContext(ExecutionContext&&) = delete;
    ExecutionContext& operator=(ExecutionContext&&) = delete;

    // Prepare execution context for running trampoline->Run()
    // on stack 'stack'
    void Setup(concurrency::core::memory::MutableMemView stack, concurrency::ITrampoline* trampoline);

    // Symmetric Control Transfer
    // 1) Save current execution context to 'this'
    // 2) Activate 'target' context
    void SwitchTo(ExecutionContext& target);

    [[noreturn]] void ExitTo(ExecutionContext& target);

    // For overflow checking
    // Best effort, nullptr means stack pointer value is not available (e.g. ucontext)
    // Calling TryStackPointer on non-suspended ExecutionContext results in UB
    void* TryStackPointer() const 
    {
        return machine_.TryStackPointer();
    }

private:
    // ITrampoline
    void Run() noexcept override;

    // Finalize first context seitch
    void AfterStart();

private:
    ITrampoline* user_trampoline_;

    concurrency::contex::machine::MachineContext machine_;
    // SanitizeContext sanitizer_;
    // ExceptionContext exceptions_; 

};

} // namespace concurrency::context