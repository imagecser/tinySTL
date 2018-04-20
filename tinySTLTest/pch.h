//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"

#define CONTAINER_ITER_EQ(ref, target) { \
    auto first1 = std::begin(ref), end1 = std::end(ref); \
    auto first2 = std::begin(target), end2 = std::end(target); \
    unsigned int i = 0; \
    while(first1 != end1) { \
        if(first2 == end2) { \
            ADD_FAILURE() << #target " has a smaller length than " #ref; \
            break; \
        } \
        EXPECT_EQ(*first1, *first2) \
            << "Containers " #ref " & " #target " differ at index " << i; \
        ++first1; ++first2; ++i; \
    } \
    EXPECT_TRUE(first2 == end2) \
        << #ref " has a smaller length than " #target; \
}

