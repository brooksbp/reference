#ifndef BASE_COMPILER_H
#define BASE_COMPILER_H

#if !defined(__GNUC__)
#error Please add support for your compiler in compiler.h
#endif

#define GCC_VERSION (__GNUC__ * 10000           \
                     + __GNUC_MINOR__ * 100     \
                     + __GNUC_PATCHLEVEL__)

#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)

#define barrier() __asm__ __volatile__("": : :"memory")
/*
 * This version is i.e. to prevent dead stores elimination on @ptr
 * where gcc and llvm may behave differently when otherwise using
 * normal barrier(): while gcc behavior gets along with a normal
 * barrier(), llvm needs an explicit input variable to be assumed
 * clobbered. The issue is as follows: while the inline asm might
 * access any memory it wants, the compiler could have fit all of
 * @ptr into memory registers instead, and since @ptr never escaped
 * from that, it proofed that the inline asm wasn't touching any of
 * it. This version works well with both compilers, i.e. we're telling
 * the compiler that the inline asm absolutely may see the contents
 * of @ptr. See also: https://llvm.org/bugs/show_bug.cgi?id=15495
 */
#define barrier_data(ptr) __asm__ __volatile__("": :"r"(ptr) :"memory")

#ifndef __always_inline
#define __always_inline inline __attribute__((always_inline))
#endif
#define noinline        __attribute__((noinline))

#define __deprecated    __attribute__((deprecated))
#define __packed        __attribute__((packed))
#define __weak          __attribute__((weak))
#define __alias(symbol) __attribute__((alias(#symbol)))

#define __pure               __attribute__((pure))
#define __aligned(x)         __attribute__((aligned(x)))
#define __printf(a, b)       __attribute__((format(printf, a, b)))
#define __scanf(a, b)        __attribute__((format(scanf, a, b)))
#define __attribute_const__  __attribute__((__const__))
#define __maybe_unused       __attribute__((unused))
#define __always_unused      __attribute__((unused))

#define __used          __attribute__((__used__))

#define __must_check    __attribute__((warn_unused_result))

#define __compiler_offsetof(a, b)  __builtin_offsetof(a, b)

/* Mark functions as cold. gcc will assume any path leading to a call
 * to them will be unlikely. This means a lot of manual unlikely()s
 * are unnecessary now.
 */
#define __cold          __attribute__((__cold__))

#define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#define __compiletime_warning(message) __attribute__((warning(message)))
#define __compiletime_error(message) __attribute__((error(message)))

#define unreachable() __builtin_unreachable()

#define __noclone       __attribute__((__noclone__))

#define __visible       __attribute__((externally_visible))

/*
 * Force the toolchain to keep a symbol even with LTO.
 *
 * Useful for C functions called only from assembly or through special sections.
 */
#define __keep __attribute__((used)) __attribute__((externally_visible))

#define asm_volatile_goto(x...) do { asm goto(x); asm (""); } while (0)

#define __no_sanitize_address __attribute__((no_sanitize_address))

/*
 * A trick to suppress uninitialized variable warning without generating any
 * code.
 */
#define uninitialized_var(x) x = x

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

#endif /* BASE_COMPILER_H */
