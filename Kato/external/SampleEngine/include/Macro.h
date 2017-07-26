#ifndef MACRO_H
#define MACRO_H

#if defined (_DEBUG) && defined (ENABLE_KATO_DEBUG_TEST)

#define KATO_DEBUG_TEST(test_type, printfcall) \
#if defined (test_type)                        \
{printfcall;}                                  \
#else                                          \
{}                                             \
#endif                                         \

#else
#define KATO_DEBUG_TEST(test_type, printfcall) {}

#endif

#endif