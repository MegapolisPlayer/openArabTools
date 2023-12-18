#include "Utils.hpp"

namespace OpenArabTools {
	//Manager
	Manager::Manager() noexcept {
		//GLFW validation
		if (glfwInit() == GLFW_FALSE) {
			std::cout << "OpenArabTools Error: GLFW window library initialization failed.\n";
			return;
		}
		//GLEW validation by create fake 1x1 window
		GLFWwindow* FakeWindow = glfwCreateWindow(1, 1, "temp", NULL, NULL);
		glfwMakeContextCurrent(FakeWindow);
		if (glewInit()) {
			std::cout << "OpenArabTools Error: GLEW OpenGL loader library initialization failed.\n";
			return;
		}
		glfwDestroyWindow(FakeWindow);
	}
	Manager::~Manager() noexcept {
		glfwTerminate();
	}
	namespace Utils {
		//General

		//increment build for each update, major or minor

		const char* Version() noexcept {
			return 
				"OpenArabTools version 0.1.0 build 0, (C) Copyright 2023-2024 Martin/MegapolisPlayer and contributors.\n"
				"Licensed under the Creative Commons CC-BY 4.0 license.\n"
				"Based on ArabTools 1.5.37 (19.03.2020), (C) Copyright 2014-2020 Ing. Daniel Kahoun. All rights reserved.\n";
		}

		constexpr U64 BuildID() noexcept {
			return 0;
			//0.1.0 in development -> builds 0-
			//0.1.0 release        -> build  
		}

		bool Sleep(const U64 aMs) noexcept {
			std::this_thread::sleep_for(std::chrono::milliseconds(aMs));
			return true; //for compatibility
		}

		//String utils

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

		void RunConcurrently(const U64 aCount, const bool aWaitReturn, RunConcurrentlyCallback aFunction) noexcept {
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
}