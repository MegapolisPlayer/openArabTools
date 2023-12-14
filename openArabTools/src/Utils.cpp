#include "Utils.hpp"

namespace OpenArabTools {
	namespace Utils {
		const char* Version() noexcept {
			return 
				"OpenArabTools version 0.1 build 131223a, (C) Copyright 2023-2024 Martin/MegapolisPlayer and contributors.\n"
				"Licensed under the Creative Commons CC-BY 4.0 license.\n"
				"Based on ArabTools 1.5.37 (19.03.2020), (C) Copyright 2014-2020 Ing. Daniel Kahoun. All rights reserved.\n";
		}

		bool Sleep(const U64 aMs) noexcept {
			std::this_thread::sleep_for(std::chrono::milliseconds(aMs));
			return true; //for compatibility
		}

		bool IsEmpty(const char* aString) noexcept {
			if (aString == nullptr) return true;
			return (strlen(aString) == 0);
		}
		bool IsEmpty(const std::string& aString) noexcept {
			return aString.empty();
		}

		const char* NonEmpty(const char* aString) noexcept {
			if (aString == nullptr) return nullptr;
			return ((strlen(aString) == 0) ? nullptr : aString);
		}
		const std::string* NonEmpty(const std::string* const aString) noexcept {
			if (aString == nullptr) return nullptr;
			return (aString->empty() ? nullptr : aString);
		}

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
			};

			static std::vector<AtomicWrapper<bool>> FunctionState; //bool true if is avaiable

			void RunnerFunc(const U08 aMyThreadId, const U64 aCount, RunConcurrentlyCallback aFunction) noexcept {
				for (U64 Id = 0; Id < aCount; Id++) {
					if (FunctionState[Id].mAtomic.load()) {
						FunctionState[Id].mAtomic.store(false);
						aFunction(aMyThreadId, Id);
					}
					else continue;
				}
			}
		}

		void RunConcurrently(const U64 aCount, const bool aWaitReturn, RunConcurrentlyCallback aFunction) noexcept {
			Internal::FunctionState.clear();
			for (U64 Id = 0; Id < aCount; Id++) {
				Internal::FunctionState.emplace_back(true);
			}

			std::thread TempThread;
			for (U32 Id = 0; Id < std::thread::hardware_concurrency() - 1; Id++) {
				TempThread = std::thread(Internal::RunnerFunc, Id, aCount, aFunction);
				TempThread.detach();
			}

			if (aWaitReturn) return;

			//TODO: wait for threads to finish
		}
	}
}