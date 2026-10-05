//
// Created by Pablo Quiroga on 05/10/2026.
//

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>

// Macro para imprimir el resultado de un test
#define ASSERT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            printf("  ❌ FAIL: %s\n", message); \
            return 0; \
        } \
    } while (0)

// Macro para iniciar un test
#define RUN_TEST(test_func) \
    do { \
        printf("Running %s... ", #test_func); \
        if (test_func()) { \
            printf("✅ PASS\n"); \
        } else { \
            printf("❌ FAIL\n"); \
        } \
    } while (0)

#endif