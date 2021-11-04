//math_test.cpp
#include <gtest.h>
#include <math.h>
#include "Ptr.h"
#include "SPrt.h"


struct Point {
	int x;
	int y;
	
	Point(): x(0), y(0) {}
	Point(int x, int y): x(x), y(y) {}
};

std::ostream& operator<< (std::ostream &out, const Point &point)
{
	// Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
	out << "Point(" << point.x << ", " << point.y << ")";
 
	return out;
}

namespace  {
TEST(TestPrt, operator_star) {
	Ptr<int> intPtr(new int(2));
	EXPECT_EQ(*intPtr, 2);
	EXPECT_NE(*intPtr, 4);
}


TEST(TestPrt, operator_arrow) {
	Ptr<Point> pointOnePtr(new Point());
	EXPECT_EQ(pointOnePtr->x, 0);
	EXPECT_EQ(pointOnePtr->y, 0);
	EXPECT_NE(pointOnePtr->x, 1);
	EXPECT_NE(pointOnePtr->y, 1);
	
	Ptr<Point> pointTwoPtr(new Point(4, 6));
	EXPECT_EQ(pointTwoPtr->x, 4);
	EXPECT_EQ(pointTwoPtr->y, 6);
	EXPECT_NE(pointTwoPtr->x, 6);
	EXPECT_NE(pointTwoPtr->y, 4);
}

TEST(TestSPrt, incrementOne) {
	SPtr<int> intSPtrOne(new int(11));
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 1);
}

TEST(TestSPrt, incrementTwo) {
	SPtr<int> intSPtrOne(new int(11));
	SPtr<int> intSPtrTwo(new int(22));
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 1);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 1);
}

TEST(TestSPrt, incrementEqual) {
	SPtr<int> intSPtrOne(new int(11));
	SPtr<int> intSPtrTwo(intSPtrOne);
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 2);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 2);
	intSPtrOne = intSPtrTwo;
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 2);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 2);
}

TEST(TestSPrt, decrementPoint) {
	SPtr<Point> intSPtrOne(new Point(11, 11));
	SPtr<Point> intSPtrTwo(new Point(22, 22));
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 1);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 1);
	intSPtrOne = intSPtrTwo;
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 2);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 2);
	SPtr<Point> intSPtrThree(intSPtrTwo);
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 3);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 3);
	EXPECT_EQ(intSPtrThree.getReferenceCounter(), 3);
}

TEST(TestSPrt, PointsEqual) {
	SPtr<Point> intSPtrOne(new Point(11, 22));
	SPtr<Point> intSPtrTwo(intSPtrOne);
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 2);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 2);
	intSPtrOne = intSPtrTwo;
	EXPECT_EQ(intSPtrOne.getReferenceCounter(), 2);
	EXPECT_EQ(intSPtrTwo.getReferenceCounter(), 2);
}
}
