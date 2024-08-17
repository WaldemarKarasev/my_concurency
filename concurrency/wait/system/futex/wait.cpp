#include "wait.hpp"

#include <ctime>

#if LINUX || 1 // for now only for Linux

#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>



namespace concurrency::wait::futex::detail {

namespace  wrap {
// There is no glibc wrapper for 'futex' syscall

int futex(unsigned int* uaddr, int op, int val, const struct timespec* timeout,
          int* uaddr2, int val3) {
  return syscall(SYS_futex, uaddr, op, val, timeout, uaddr2, val3);
}

}
int SystemWaitTimed(uint32_t* addr, uint32_t old, uint32_t millis) {
  struct timespec timeout;
  timeout.tv_sec = millis / 1000;
  timeout.tv_nsec = (millis % 1000) * 1000'000;

  return wrap::futex(addr, FUTEX_WAIT_PRIVATE, old, &timeout, nullptr, 0);
}

int SystemWait(uint32_t* addr, uint32_t old) {
  return wrap::futex(addr, FUTEX_WAIT_PRIVATE, old, nullptr, nullptr, 0);
}

int SystemWake(uint32_t* addr, size_t count) {
  return wrap::futex(addr, FUTEX_WAKE_PRIVATE, (int)count, nullptr, nullptr, 0);
}

}
#endif