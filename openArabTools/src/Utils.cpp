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

			static U08 sThreadAmount = std::thread::hardware_concurrency() - 1;
			static std::mutex sMutex; //so that only 1 thread can access
			static std::vector<AtomicWrapper<bool>> sFunctionState; //bool true if is avaiable
			static std::atomic<U08> sThreadAmountFinished = sThreadAmount;

			void RunnerFunc(const U08 aMyThreadId, const U64 aCount, RunConcurrentlyCallback aFunction) noexcept {
				for (U64 Id = 0; Id < aCount; Id++) {
					std::unique_lock<std::mutex> LG(sMutex);
					if (sFunctionState[Id].mAtomic.load()) {
						sFunctionState[Id].mAtomic.store(false);
						LG.unlock();
						aFunction(aMyThreadId, Id);
					}
					else {
						LG.unlock();
						continue;
					};
				}
				sThreadAmountFinished++;
			}
		}

		void runConcurrently(const U64 aCount, const bool aWaitReturn, RunConcurrentlyCallback aFunction) noexcept {
			if (aFunction == nullptr) {
				Error::warning("Invalid parameter in runConcurrently: aFunction is nullptr");
			}
			if (aCount == 0) return; //nothing to do, this can happen
			if (Internal::sThreadAmount != Internal::sThreadAmountFinished) return; //if runConcurrently is running

			Internal::sFunctionState.clear();
			Internal::sThreadAmountFinished = 0;
			for (U64 Id = 0; Id < aCount; Id++) {
				Internal::sFunctionState.emplace_back(true);
			}

			std::thread TempThread;
			for (U08 Id = 0; Id < Internal::sThreadAmount; Id++) {
				TempThread = std::thread(Internal::RunnerFunc, Id, aCount, aFunction);
				TempThread.detach();
			}

			if (!aWaitReturn) return;

			//wait
			while (Internal::sThreadAmount != Internal::sThreadAmountFinished);
		}
	}

	ScopedTimer::ScopedTimer(const char* aName) noexcept {
		this->mName = aName;
		this->mStart = std::chrono::system_clock::now();
	}
	ScopedTimer::~ScopedTimer() noexcept {
		U64 Us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - this->mStart).count();
		if (Us == 0) {
			std::cerr << "Timer \"" << this->mName << "\": 0us, >1000000 FPS\n";
			return;
		}
		U64 Ms = Us / 1000;
		std::cerr << "Timer \"" << this->mName << "\": " << Ms << "ms, " << Us << "us, " << 1000000/Us << "FPS\n";
	}
}