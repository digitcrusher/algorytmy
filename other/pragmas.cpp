/*
 * The Ultimate Pragmas - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */

/*
 * This is a collection of GCC pragmas that may be useful for squeezing more
 * out of your code/compiler in competitive programming especially Codeforces.
 *
 * To see what optimizations are being made by the compiler pass the -fopt-info
 * flag to your compiler or -fopt-info-all to see also the ones not made by the
 * compiler.
 *
 * To generate a debuggable executable, pass these options to the compiler:
 *   -Og -ggdb3
 *
 * To get useful run-time diagnostics, pass these options:
 *   -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow
 *   -g -fsignaling-nans -fnon-call-exceptions
 *   -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
 * Passing the other -fstack… options listed in GCC's docs is redundant.
 *
 * Solutions on Codeforces are compiled with (https://codeforces.com/blog/entry/75004):
 *   g++ -static -DONLINE_JUDGE -Wl,--stack=268435456 -O2 -std=c++17 solution.cpp
 */

/* Useful compile-time diagnostics */
#pragma GCC diagnostic warning "-Wall"
#pragma GCC diagnostic warning "-Wextra"

/* Other */
#pragma GCC diagnostic warning "-Wformat=2"
#pragma GCC diagnostic warning "-Wnull-dereference"
#pragma GCC diagnostic warning "-Wduplicated-branches"
#pragma GCC diagnostic warning "-Wduplicated-cond"
#pragma GCC diagnostic warning "-Wfloat-equal"
#pragma GCC diagnostic warning "-Wshadow"
#pragma GCC diagnostic warning "-Wconversion"
#pragma GCC diagnostic warning "-Wlogical-op"
#pragma GCC diagnostic warning "-Wvector-operation-performance"
#pragma GCC diagnostic warning "-Wdisabled-optimization"
#pragma GCC diagnostic warning "-Wunsafe-loop-optimizations"
// Detects promotion to doubles which are costly on 32-bit machines
#pragma GCC diagnostic warning "-Wdouble-promotion"

/*
 * Codeforces' CPU is Intel(R) Core(TM) i5-3470
 * (https://codeforces.com/blog/entry/57248,
 *  https://codeforces.com/blog/entry/8457)
 */
#pragma GCC target "arch=ivybridge", "tune=ivybridge"

// Looks for an explicitly set optimization level excluding -O0 such as -Og
#if defined(ONLINE_JUDGE) || !defined(__OPTIMIZE__)

/* Basic */
#pragma GCC optimize "Ofast" // Not standard-compliant, alternative: O3
#pragma GCC optimize "inline" // Inlines all functions declared inline
#pragma GCC optimize "unroll-loops"
#pragma GCC optimize "ipa-pta"
#pragma GCC optimize "no-rtti" // Disables dynamic_cast and typeid
#pragma GCC optimize "no-exceptions"
#pragma GCC optimize "nothrow-opt"

/* Other */
#pragma GCC target "inline-all-stringops"
#pragma GCC optimize "strict-enums" // Disables casting arbitrary integers to enums
#pragma GCC optimize "stdarg-opt"
#pragma GCC optimize "tracer"

/* Memory */
#pragma GCC optimize "Os" // Replaces Ofast
#pragma GCC optimize "conserve-stack" // May make the program slower.
#pragma GCC target "no-align-stringops"

/* Aggressive */
#pragma GCC optimize "reg-struct-return"

/* Aggressive memory */
#pragma GCC optimize "pack-struct" // May slow down your program
#pragma GCC optimize "short-enums"
#pragma GCC optimize "no-threadsafe-statics" // Makes your code smaller

/* Maybe */
#pragma GCC optimize "modulo-sched"
#pragma GCC optimize "modulo-sched-allow-regmoves"
#pragma GCC optimize "gcse-sm"
#pragma GCC optimize "gcse-las"
#pragma GCC optimize "sched2-use-superblocks"
#pragma GCC optimize "reschedule-modulo-scheduled-loops"
#pragma GCC optimize "selective-scheduling"
#pragma GCC optimize "selective-scheduling2"
#pragma GCC optimize "sel-sched-pipelining"
#pragma GCC optimize "sel-sched-pipelining-outer-loops"
#pragma GCC optimize "unroll-all-loops" // The docs say this usually slows down your program

#endif

/*
 * Some interesting things I found out when making this:
 * - "native" CPU type doesn't work in #pragma GCC target
 *   (https://stackoverflow.com/questions/45908243/how-to-specify-march-native-using-pragmas-or-otherwise-in-gcc)
 *
 * - #pragma GCC option used in other people's pragmas doesn't actually exist
 *   and in 2008 #pragma GCC option was actually renamed to #pragma GCC target.
 *   So you can specify only optimization and submodel options in pragmas.
 *
 * - GCC accepts any sequence of characters after #pragma GCC
 *
 * - Wrong warning message:
 *   soln_template.cpp:132:20: warning: ‘#pragma GCC option’ is not a string [-Wpragmas]
 *     132 | #pragma GCC target avx
 *         |                    ^~~
 *
 * - -finline is not documented on https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options,
 *   but it is a recognized GCC optimization option.
 *
 * - Some options including -fmerge-all-constants don't have the "Optimization"
 *   flag in gcc/common.opt even though they are listed on the Optimization
 *   Options page in GCC's documentation.
 *
 * - -funsafe-loop-optimizations does nothing and is preserved only for
 *   backwards compatibility.
 *
 * - -fdevirtualize-speculatively, -funswitch-loops and -fsplit-loops don't have
 *   a notice in their descriptions in the docs that they are enabled by default
 *   with -O options.
 *
 * - -Wfatal-errors and -Wno-pedantic don't work in pragmas.
 *
 * - -ftrapv is kind of useless for detecting over-/underflows because it only
 *   sends a POSIX signal to the program and nothing else.
 *
 * - #pragma GCC diagnostic warning accepts only one option
 *
 * Notes:
 *   I omitted some of the options which would be of no use on Codeforces'
 *   hardware. There were also some other options that just didn't work in
 *   pragmas.
 */
