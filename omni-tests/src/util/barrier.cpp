#include "gtest/gtest.h"
#include "omni-lib/src/utilities/barrier.h"
#include <string>

namespace {
	void barrier_arrive_and_wait(util::barrier& barrier, bool& flag) {
		barrier.arrive_and_wait();
		flag = true;
	}

	void barrier_arrive_and_drop(util::barrier& barrier, bool& flag) {
		barrier.arrive_and_drop();
		flag = false;
	}
}

TEST(barrier, use_count) {
	util::barrier barrier(1);
	EXPECT_EQ(barrier.use_count(), 0);
}

TEST(barrier, threshold) {
	util::barrier barrier(2);
	EXPECT_EQ(barrier.threshold(), 2);
}

TEST(barrier, arrive_and_wait) {
	util::barrier barrier(3);
	bool flags[3] = { false, false, false };
	std::thread thread_0([&flags, &barrier]() { ::barrier_arrive_and_wait(barrier, flags[0]); });
	std::thread thread_1([&flags, &barrier]() { ::barrier_arrive_and_wait(barrier, flags[1]); });
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	EXPECT_FALSE(flags[0] && flags[1] && flags[2]);
	EXPECT_EQ(barrier.use_count(), 2);
	std::thread thread_2([&flags, &barrier]() { ::barrier_arrive_and_wait(barrier, flags[2]); });
	thread_0.join();
	thread_1.join();
	thread_2.join();
	EXPECT_TRUE(flags[0] && flags[1] && flags[2]);
}

TEST(barrier, arrive_and_drop) {
	util::barrier barrier(3);
	bool flags[4] = { false, false, false, false };
	std::thread thread_0([&flags, &barrier]() { ::barrier_arrive_and_wait(barrier, flags[0]); });
	std::thread thread_1([&flags, &barrier]() { ::barrier_arrive_and_wait(barrier, flags[1]); });
	std::thread thread_2([&flags, &barrier]() { ::barrier_arrive_and_drop(barrier, flags[2]); });
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	EXPECT_FALSE(flags[0] && flags[1] && flags[2] && flags[3]);
	EXPECT_EQ(barrier.use_count(), 2);
	std::thread thread_3([&flags, &barrier]() { ::barrier_arrive_and_wait(barrier, flags[3]); });
	thread_0.join();
	thread_1.join();
	thread_2.join();
	thread_3.join();
	EXPECT_TRUE(flags[0] && flags[1] && flags[3]);
	EXPECT_FALSE(flags[2]);
}