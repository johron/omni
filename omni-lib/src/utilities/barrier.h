#pragma once
#include <cstddef>
#include <atomic>
#include <mutex>
#include <set>

namespace util {
	class barrier {
	public:
		barrier(std::ptrdiff_t num_threads) 
			: m_required(num_threads) { }
		barrier(const barrier& other) = delete;
		barrier(barrier&& other) = delete;

		void arrive_and_wait() {
			std::unique_lock<std::mutex> lock(m_mutex);
			m_participants.insert(std::this_thread::get_id());
			if (m_participants.size() == m_required) {
				m_participants.clear();
				m_condition.notify_all();
			} else {
				m_condition.wait(lock);
			}
		}

		void arrive_and_drop() {
			m_participants.erase(std::this_thread::get_id());
		}

		size_t use_count() const noexcept {
			return m_participants.size();
		}

		size_t threshold() const noexcept {
			return m_required;
		}

	private:
		std::set<std::thread::id> m_participants;
		std::atomic_ptrdiff_t m_required;
		std::condition_variable m_condition;
		std::mutex m_mutex;
	};
}
