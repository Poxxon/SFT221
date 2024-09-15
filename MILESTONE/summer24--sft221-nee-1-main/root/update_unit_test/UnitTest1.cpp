#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackBoxTests
{
    TEST_CLASS(CoreTests)
    {

    public:

        TEST_METHOD(CheckVehicleCapacity_WithinCapacity)
        {
            struct Truck vehicle = { 0, 2500, 0, 0, nullptr }; // 2500 is the max weight capacity
            struct DeliveryPackage pkg = { 200, 1.0, {0, 0} }; // 200 kg package
            Assert::AreEqual(1, checkVehicleCapacity(vehicle, pkg));
        }
        TEST_METHOD(CheckVehicleCapacity_AtCapacityLimit)
        {
            struct Truck vehicle = { 0, 2500, 0, 0, nullptr };
            struct DeliveryPackage pkg = { 2500, 1.0, {0, 0} }; // Exactly at capacity limit
            Assert::AreEqual(1, checkVehicleCapacity(vehicle, pkg));
        }

        TEST_METHOD(CheckVehicleCapacity_OverCapacity)
        {
            struct Truck vehicle = { 0, 2500, 0, 0, nullptr };
            struct DeliveryPackage pkg = { 2600, 1.0, {0, 0} }; // Over capacity
            Assert::AreEqual(1, checkVehicleCapacity(vehicle, pkg));
        }

        TEST_METHOD(CheckVehicleCapacity_EmptyTruckLightPackage)
        {
            struct Truck vehicle = { 0, 2500, 0, 0, nullptr };
            struct DeliveryPackage pkg = { 1, 1.0, {0, 0} }; // Minimal weight package
            Assert::AreEqual(1, checkVehicleCapacity(vehicle, pkg));
        }

        TEST_METHOD(IsBoxDimensionValid_ValidSmallSize)
        {
            Assert::AreEqual(1, isBoxDimensionValid(MIN_SIZE));
        }

        TEST_METHOD(IsBoxDimensionValid_ValidMediumSize)
        {
            Assert::AreEqual(1, isBoxDimensionValid(MID_SIZE));
        }

        TEST_METHOD(IsBoxDimensionValid_ValidLargeSize)
        {
            Assert::AreEqual(1, isBoxDimensionValid(MAX_SIZE));
        }

        TEST_METHOD(IsBoxDimensionValid_InvalidSize)
        {
            float invalidSize = 0.3f;
            Assert::AreEqual(0, isBoxDimensionValid(invalidSize));
        }
    };

    TEST_CLASS(MappingTests)
    {
    public:

        TEST_METHOD(Distance_SamePoint)
        {
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 0, 0 };
            Assert::AreEqual(0.0, distance(&p1, &p2));
        }

        TEST_METHOD(Distance_DifferentPoints)
        {
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 3, 4 }; // Known distance of 5.0 units
            Assert::AreEqual(5.0, distance(&p1, &p2));
        }

        TEST_METHOD(Distance_DiagonalDistance)
        {
            struct Point p1 = { 1, 1 };
            struct Point p2 = { 4, 5 }; // Diagonal distance
            Assert::AreEqual(5.0, distance(&p1, &p2));
        }

        TEST_METHOD(Distance_NegativeCoordinates)
        {
            struct Point p1 = { -3, -4 };
            struct Point p2 = { 0, 0 }; // Distance with negative coordinates
            Assert::AreEqual(5.0, distance(&p1, &p2));
        }

        TEST_METHOD(GetClosestPoint_PointOnRoute)
        {
            struct Route route = { {{0, 0}, {1, 1}, {2, 2}}, 3, 0 };
            struct Point pt = { 1, 1 };
            Assert::AreEqual(1, getClosestPoint(&route, pt));
        }

        TEST_METHOD(GetClosestPoint_PointNearRoute)
        {
            struct Route route = { {{0, 0}, {2, 2}, {4, 4}}, 3, 0 };
            struct Point pt = { 3, 3 }; // Closest to {2, 2}
            Assert::AreEqual(1, getClosestPoint(&route, pt));
        }

        TEST_METHOD(GetClosestPoint_PointFarFromRoute)
        {
            struct Route route = { {{0, 0}, {10, 10}, {20, 20}}, 3, 0 };
            struct Point pt = { 30, 30 }; // Farthest point, but closest to {20, 20}
            Assert::AreEqual(2, getClosestPoint(&route, pt));
        }
        TEST_METHOD(GetClosestPoint_EmptyRoute)
        {
            struct Route route = { {{0, 0}}, 0, 0 }; // No points in the route
            struct Point pt = { 5, 5 };
            Assert::AreEqual(-1, getClosestPoint(&route, pt)); // Expecting -1 for empty route
        }

    };
};