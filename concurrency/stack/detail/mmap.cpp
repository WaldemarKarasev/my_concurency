#include "mmap.hpp"

namespace concurrency::stack {

MmapStack::MmapStack(MmapAllocation allocation) 
    : allocation_(std::move(allocation))
{}

MmapStack MmapStack::AllocatePages(size_t count)
{
    auto allocation = MmapAllocation::AllocatePages(count + 1);

    // Guard page
    allocation.ProtectPages(/*offset=*/0, /*count=*/1);
    return MmapStack{std::move(allocation)};
}

MmapStack MmapStack::AllocateBytes(size_t at_least)
{
    const size_t page_size = MmapAllocation::PageSize();

    size_t pages = at_least / page_size;
    if (at_least % page_size != 0)
    {
        pages += 1;
    }

    return MmapStack::AllocatePages(pages);
}

void* MmapStack::LowerBound() const
{
    return allocation_.Start() + MmapAllocation::PageSize();
}

MutableMemView MmapStack::MutView()
{
    return allocation_.MutView();
}

MmapStack MmapStack::Acquire(MutableMemView view)
{
    return MmapStack(MmapAllocation::Acquire(view));
}

MutableMemView MmapStack::Release()
{
    return allocation_.Release();
}

} // namespace concurrency stack