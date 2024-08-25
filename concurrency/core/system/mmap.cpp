#include "mmap.hpp"


#include <concurrency/utility.hpp>

#include "page_size.hpp"

// #include <cerrno>
// #include <cstring>

// #include <unistd.h>

#include <sys/mman.h>

namespace concurrency::core::system {


#define CHECK_RESULT(ret, error) //????

///////////////////////////////////////////////////////////////

static size_t PagesToBytes(size_t count)
{
    return count * concurrency::core::system::PageSize();
}

size_t MmapAllocation::PageSize() 
{
    return concurrency::core::system::PageSize();
}

MmapAllocation MmapAllocation::AllocatePages(size_t count, void* hint)
{
    size_t size = PagesToBytes(count);

    void* start = mmap(/*addr=*/hint, /*length=*/size,
                       /*prot=*/PROT_READ | PROT_WRITE,
                       /*flags=*/MAP_PRIVATE | MAP_ANONYMOUS,
                       /*fd=*/-1, /*offset=*/0);
    if (start == MAP_FAILED)
    {
        std::abort();
    }

    return MmapAllocation((char*)start, size);
    
}

MmapAllocation MmapAllocation::Acquire(memory::MutableMemView view)
{
    // TODO: check size and alignment
    return MmapAllocation{view.Data(), view.Size()};
}

void MmapAllocation::ProtectPages(size_t start_index, size_t count)
{
    int ret = mprotect(/*addr=*/(void*)(start_ + PagesToBytes(start_index)),
                     /*len=*/PagesToBytes(count),
                     /*prot=*/PROT_NONE);
    if (ret == -1)
    {
        std::cout << "Cannot protect pages [" << start_index << ", " << start_index + count << ")" << std::endl;
    }
}

MmapAllocation::MmapAllocation(MmapAllocation&& other)
{
    start_ = other.start_;
    size_ = other.size_;
    other.Reset();
}

MmapAllocation& MmapAllocation::operator=(MmapAllocation&& other)
{
    Deallocate();
    start_ = other.start_;
    size_ = other.size_;
    other.Reset();
    return *this;
}

void MmapAllocation::Deallocate()
{
    if (start_ == nullptr)
    { 
        return;
    }

    int ret = munmap((void*)start_, size_);
    if (ret == -1)
    {
        std::cout << "Cannot unmap pages" << std::endl;
    }
}

memory::MutableMemView MmapAllocation::Release()
{
    auto view = MutView();
    Reset();
    return view;
}

void MmapAllocation::Reset()
{
    start_ = nullptr;
    size_ = 0;
}

} // namespace concurrency::core::system