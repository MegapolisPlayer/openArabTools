#include "Utils.hpp"

namespace OpenArabTools {
	namespace Utils {
		//General

		bool sleep(const U64 aMs) noexcept {
			//this is more precise and extenable than sleep_for

			std::chrono::system_clock::time_point Start = std::chrono::system_clock::now();
			std::chrono::system_clock::time_point End = Start + std::chrono::milliseconds(aMs);

			while (std::chrono::system_clock::now() < End) {
				std::this_thread::sleep_for(1ms);
			}
			return true; //for compatibility
		}

		//String utils

		bool isEmpty(const char* aString) noexcept {
			if (aString == nullptr) return true;
			return (strlen(aString) == 0);
		}

		bool isEmpty(const std::string& aString) noexcept {
			return aString.empty();
		}

		const char* const nonEmpty(const char* aString) noexcept {
			if (aString == nullptr) return nullptr;
			return ((strlen(aString) == 0) ? nullptr : aString);
		}
		const std::string* nonEmpty(const std::string* const aString) noexcept {
			if (aString == nullptr) return nullptr;
			return (aString->empty() ? nullptr : aString);
		}

		//RunConcurrently

		namespace Internal {
			template<typename tType>
			struct AtomicWrapper {
				std::atomic<tType> mAtomic;

				AtomicWrapper() {
					mAtomic.store({});
				}
				AtomicWrapper(const tType& aValue) {
					mAtomic.store(aValue);
				}
				AtomicWrapper(const AtomicWrapper& aOther) {
					mAtomic.store(aOther.mAtomic.load());
				}
				AtomicWrapper& operator=(const AtomicWrapper& aOther) {
					mAtomic.store(aOther.mAtomic.load());
					return *this;
				}
				~AtomicWrapper() {}; //std::atomic has a destructor
			};

			static U08 ThreadAmount = std::thread::hardware_concurrency() - 1;
			static std::mutex Mutex; //so that only 1 thread can access
			static std::vector<AtomicWrapper<bool>> FunctionState; //bool true if is avaiable
			static std::atomic<U08> ThreadAmountFinished = ThreadAmount;

			void RunnerFunc(const U08 aMyThreadId, const U64 aCount, RunConcurrentlyCallback aFunction) noexcept {
				for (U64 Id = 0; Id < aCount; Id++) {
					std::unique_lock<std::mutex> LG(Mutex);
					if (FunctionState[Id].mAtomic.load()) {
						FunctionState[Id].mAtomic.store(false);
						LG.unlock();
						aFunction(aMyThreadId, Id);
					}
					else {
						LG.unlock();
						continue;
					};
				}
				ThreadAmountFinished++;
			}
		}

		void runConcurrently(const U64 aCount, const bool aWaitReturn, RunConcurrentlyCallback aFunction) noexcept {
			if (aFunction == nullptr) {
				Error::warning("Invalid parameter in runConcurrently: aFunction is nullptr");
			}
			if (aCount == 0) return; //nothing to do, this can happen
			if (Internal::ThreadAmount != Internal::ThreadAmountFinished) return; //if runConcurrently is running

			Internal::FunctionState.clear();
			Internal::ThreadAmountFinished = 0;
			for (U64 Id = 0; Id < aCount; Id++) {
				Internal::FunctionState.emplace_back(true);
			}

			std::thread TempThread;
			for (U08 Id = 0; Id < Internal::ThreadAmount; Id++) {
				TempThread = std::thread(Internal::RunnerFunc, Id, aCount, aFunction);
				TempThread.detach();
			}

			if (!aWaitReturn) return;

			//wait
			while (Internal::ThreadAmount != Internal::ThreadAmountFinished);
		}
	}

	ScopedTimer::ScopedTimer(const char* aName) noexcept {
		this->mName = aName;
		this->mStart = std::chrono::system_clock::now();
	}
	ScopedTimer::~ScopedTimer() noexcept {
		U64 Us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - this->mStart).count();
		U64 Ms = Us / 1000;
		std::cout << "Timer \"" << this->mName << "\": " << Ms << "ms, " << Us << "us, " << 1000000/Us << "FPS\n";
	}
}