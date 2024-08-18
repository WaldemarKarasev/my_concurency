#include "mmap.hpp"

namespace concurrency::core::system {



MmapAllocation::MmapAllocation(MmapAllocation&& other) {

}

MmapAllocation& MmapAllocation::operator=(MmapAllocation&& other) {

}

void MmapAllocation::Deallocate() {

}

MmapAllocation::MutableMemView MmapAllocation::Release() {
    auto view = MutView();
    Reset();
    return view;
}

void MmapAllocation::Reset() {
    start_ = nullptr;
    size_  = 0;
}

} // namespace concurrency::core::system