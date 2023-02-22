#include "runtimer.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(RunTimerTest, ShouldStartTimer)
{
    RunTimer rt;
    rt.start();
    ASSERT_TRUE(rt.isRunning());    
}

