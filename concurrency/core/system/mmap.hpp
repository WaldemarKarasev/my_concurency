#pragma once


#include <concurrency/core/memory/view.hpp>

namespace concurrency::core::system {

class MmapAllocation
{
public:

    using MutableMemView = concurrency::core::memory::MutableMemView;
    using ConstMemView   = concurrency::core::memory::ConstMemView;

public:
    MmapAllocation() {
        Reset();        
    }

    static size_t PageSize();

    // Allocate 'count' pages of zeroed memory
    static MmapAllocation AllocatePages(size_t count, void* hint = nullptr);
    static MmapAllocation Acquire(MutableMemView view);

    // Non-Copyable
    MmapAllocation(MmapAllocation&) = delete;
    MmapAllocation& operator=(MmapAllocation&) = delete;

    // Movable
    MmapAllocation(MmapAllocation&& other);
    MmapAllocation& operator=(MmapAllocation other);

    ~MmapAllocation() {
        Deallocate();
    }

    char* Start() const {
        return start_;
    }

    char* End() const {
        return start_ + size_;
    }

    size_t Size() const {
        return size_;
    }

    size_t PageCount() const {
        return Size() / PageSize();
    }

    ConstMemView View() const {
        return ConstMemView{start_, size_};
    }

    MutableMemView MutView() {
        return MutableMemView{start_, size_};
    }

    // Protect range of paged
    // Protected pages cannot be read, written or executed
    void ProtectPages(size_t start_index, size_t count);

    void Deallocate();

    MutableMemView Release();

private:

    MmapAllocation(char* start, size_t size) 
        : start_(start)
        , size_(size) {
    }

    static size_t PageSize();

    void Reset();

private:
    // Aligned to page boundary
    char* start_;
    size_t size_;
};

} // namespace concurrency::core::system