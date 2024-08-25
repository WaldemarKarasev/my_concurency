#pragma once

#include <cstdint>

#include <concurrency/core/memory/view.hpp>
#include <concurrency/core/system/mmap.hpp>

namespace concurrency::stack {

using MutableMemView = concurrency::core::memory::MutableMemView;
using MmapAllocation = concurrency::core::system::MmapAllocation;

// MmapStack = mmap allocation with guard page
class MmapStack {

public:
	MmapStack() = delete;

	static MmapStack AllocateBytes(size_t at_least);

	// Allocated memory will be released to the operating system
	~MmapStack() = default;

	MmapStack(MmapStack&&) = default;
	MmapStack& operator=(MmapStack&&) = default;

	void* LowerBound() const;

	// Including guard page
	size_t AllocationSize() const 
	{
		return allocation_.Size();
	}

	MutableMemView MutView();

	// Release / acquire ownership for the underlying memory region
	[[nodiscard("Memory leak")]] MutableMemView Release();
	
	static MmapStack Acquire(MutableMemView view);

private:
	MmapStack(MmapAllocation allocation);

	static MmapStack AllocatePages(size_t count);

private:
	MmapAllocation allocation_;
};


} // namespace concurrency::stack