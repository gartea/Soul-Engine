#include "CppUnitTest.h"
#include <boost/fiber/all.hpp>
#include <Source Files\Multithreading\Scheduler.h>
//#include "Source Files/Multithreading/Scheduler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void mult(int x, int y) {
	int z = x*y;
}

namespace Multithreadingtest
{		
	TEST_CLASS(unittest1)
	{
	public:
		
		TEST_METHOD(basic_fiber_spawning)
		{
			//tests intitializing, adding a simple task and terminating the scheduler
			Scheduler::Initialize();


			Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_HIGH, false, []() {
				std::cout << "hi" << std::endl;
			});

			Assert::IsTrue(Scheduler::Running());

			Scheduler::Block();

			Scheduler::Terminate();

			Assert::IsTrue(true);
		}
		TEST_METHOD(Multi_fiber_spawning)
		{
			//tests spawning 800 fibers of every combination of boolean/enums
			Scheduler::Initialize();

			for (UINT i = 0; i < 100; i++)
			{
				Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_HIGH, false, []() {
					mult(1,1);
				});
				Scheduler::AddTask(LAUNCH_CONTINUE, FIBER_HIGH, false, []() {
					mult(1, 1);
				});
				Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_LOW, false, []() {
					mult(1, 1);
				});
				Scheduler::AddTask(LAUNCH_CONTINUE, FIBER_LOW, false, []() {
					mult(1, 1);
				});
				Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_HIGH, true, []() {
					mult(1, 1);
				});
				Scheduler::AddTask(LAUNCH_CONTINUE, FIBER_HIGH, true, []() {
					mult(1, 1);
				});
				Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_LOW, true, []() {
					mult(1, 1);
				});
				Scheduler::AddTask(LAUNCH_CONTINUE, FIBER_LOW, true, []() {
					mult(1, 1);
				});
			}
			

			Assert::IsTrue(Scheduler::Running());

			Scheduler::Block();

			Scheduler::Terminate();

			Assert::IsTrue(true);
		}
		TEST_METHOD(blocker)
		{
			//Tests blocking of execution until all launch immediate tasks are done
			Scheduler::Initialize();

			//due to block each task runs sequentially so a is in order
			std::vector<int> a;
			for (size_t i = 0; i < 100; i++)
			{
				Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_HIGH, false, [&i, &a]() {
					a.push_back((int)(i));
				});
				Scheduler::Block();
			}


			Scheduler::Terminate();
			for (size_t i = 0; i < 100; i++)
			{
				Assert::AreEqual(int(i), a[i]);
			}


			Assert::IsTrue(true);
		}
		TEST_METHOD(fiber_properties_high_main)
		{
			//tests spawning a high priority thread that spawns on main
			Scheduler::Initialize();

			Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_HIGH, true, []() {
				mult(1, 1);
			});

			Scheduler::Terminate();

			Assert::IsTrue(true);
		}
		TEST_METHOD(fiber_properties_high_other)
		{
			//tests spawning a high priority thread running not on main
			Scheduler::Initialize();

			Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_HIGH, false, []() {
				mult(1, 1);
			});

			Scheduler::Terminate();

			Assert::IsTrue(true);
		}
		TEST_METHOD(fiber_properties_low_main)
		{
			//tests spawning a low priority thread that spawns on main
			Scheduler::Initialize();

			Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_LOW, true, []() {
				mult(1, 1);
			});

			Scheduler::Terminate();

			Assert::IsTrue(true);
		}
		TEST_METHOD(fiber_properties_low_other)
		{
			//tests spawning a low priority thread that spawns not on main
			Scheduler::Initialize();

			Scheduler::AddTask(LAUNCH_IMMEDIATE, FIBER_LOW, false, []() {
				mult(1, 1);
			});

			Scheduler::Terminate();

			Assert::IsTrue(true);
		}
	};
}