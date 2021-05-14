#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab1_Kuznetsov/Lab1_Kuznetsov.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		Map<string, int>* mapStringInt = new Map<string, int>();
		Map<int, string>* mapIntString = new Map<int, string>();
		Map<double, double>* mapDoubleDouble = new Map<double, double>();

		TEST_METHOD(TestInsertAndFind)
		{
			mapStringInt->insert("abc", 1);
			mapStringInt->insert("ade", 2);
			mapStringInt->insert("bbc", 3);

			mapIntString->insert(1, "a");
			mapIntString->insert(2, "abc");
			mapIntString->insert(3, "def");

			mapDoubleDouble->insert(3.52, 2.64);
			mapDoubleDouble->insert(3.53, 2.10934);
			mapDoubleDouble->insert(3.5333, 2.69402);

			Assert::AreEqual(1, mapStringInt->find("abc"));
			Assert::AreEqual((string)"def", mapIntString->find(3));
			Assert::AreEqual(2.69402, mapDoubleDouble->find(3.5333));
		}

		TEST_METHOD(TestRepeatInsert) {
			mapStringInt->insert("abc", 1);
			mapStringInt->insert("abc", 4);

			mapIntString->insert(1, "a");
			mapIntString->insert(1, "abc");

			mapDoubleDouble->insert(3, 2.66434);
			mapDoubleDouble->insert(3, 2.10934);

			Assert::AreEqual(4, mapStringInt->find("abc"));
			Assert::AreEqual((string)"abc", mapIntString->find(1));
			Assert::AreEqual(2.10934, mapDoubleDouble->find(3));
		}

		TEST_METHOD(TestRemove) {
			bool notFindMarker = false;

			mapStringInt->insert("abc", 1);
			mapStringInt->insert("ade", 2);
			mapStringInt->insert("bbc", 3);

			mapStringInt->remove("bbc");
			mapStringInt->remove("ade");

			try {
				mapStringInt->find("bbc");
			}
			catch (int) {
				notFindMarker = true;
			}

			Assert::IsTrue(notFindMarker);
			Assert::AreEqual(1, mapStringInt->find("abc"));

			mapStringInt->remove("abc");
			mapStringInt->insert("bse", 1);

			Assert::AreEqual(1, mapStringInt->find("bse"));
		}

		TEST_METHOD(TestClear) {
			bool notFindMarker = false;

			mapStringInt->insert("abc", 1);
			mapStringInt->insert("ade", 2);
			mapStringInt->insert("bbc", 3);

			mapStringInt->clear();

			try {
				mapStringInt->find("bbc");
			}
			catch (int) {
				notFindMarker = true;
			}

			Assert::IsTrue(notFindMarker);
			mapStringInt->insert("bse", 1);
			Assert::AreEqual(1, mapStringInt->find("bse"));
		}

		TEST_METHOD(TestGetKeys) {
			mapStringInt->insert("abc", 1);
			mapStringInt->insert("ade", 2);
			mapStringInt->insert("bbc", 3);
			mapStringInt->insert("bec", 4);
			mapStringInt->insert("bec", 5);

			auto k = mapStringInt->get_keys();
			Assert::AreEqual(4, (int)k.size());
			Assert::AreEqual((string)"abc", k[0]);
			Assert::AreEqual((string)"ade", k[1]);
			Assert::AreEqual((string)"bbc", k[2]);
			Assert::AreEqual((string)"bec", k[3]);
		}

		TEST_METHOD(TestGetValues) {
			mapStringInt->insert("abc", 1);
			mapStringInt->insert("ade", 2);
			mapStringInt->insert("bbc", 3);
			mapStringInt->insert("bec", 4);
			mapStringInt->insert("bec", 5);

			auto v = mapStringInt->get_values();
			Assert::AreEqual(4, (int)v.size());
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(2, v[1]);
			Assert::AreEqual(3, v[2]);
			Assert::AreEqual(5, v[3]);
		}
	};
}
