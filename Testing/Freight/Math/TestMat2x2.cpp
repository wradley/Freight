#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Matrix 2x2")
{
    FR_STAGE("Zero Constructor") {
        Mat2 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0 },
            { 0, 0 }
        }));
    }

    FR_STAGE("Array Constructor") {
        Real arr[2][2] = {
            { 1, 2 },
            { 3, 4 }
        };

        Mat2 a(arr);

        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 }
        }));
    }

    FR_STAGE("Initializer List") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 }
        }));
    }

    FR_STAGE("Smaller Initializer List 1") {
        Mat2 a{
            { 1 },
            { 3, 4 }
        };

        FR_REQUIRE(Eql(a, {
            { 1, 0 },
            { 3, 4 }
        }));
    }

    FR_STAGE("Smaller Initializer List 2") {
        Mat2 a{
            { 1, 2 }
        };

        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 0, 0 }
        }));
    }

    FR_STAGE("Larger Initializer List 1") {
        Mat2 a{
            { 1, 2, 3 },
            { 4, 5 }
        };

        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 4, 5 }
        }));
    }

    FR_STAGE("Larger Initializer List 2") {
        Mat2 a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 4, 5 }
        }));
    }

    FR_STAGE("Copy Constructor") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        Mat2 b(a);

        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("Assign Operator") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        Mat2 b = a;

        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("Copy Constructor for Different Size 1") {
        Matrix<double, 1, 1> a{
            { 1 }
        };

        Mat2 b(a);

        FR_REQUIRE(Eql(b, {
            { 1, 0 },
            { 0, 0 }
        }));
    }

    FR_STAGE("Copy Constructor for Different Size 2") {
        Matrix<double, 3, 1> a{
            { 1 },
            { 2 },
            { 3 }
        };

        Mat2 b(a);

        FR_REQUIRE(Eql(b, {
            { 1, 0 },
            { 2, 0 }
        }));
    }

    FR_STAGE("Copy Constructor for Different Size 3") {
        Matrix<double, 1, 3> a{
            { 1, 2, 3 }
        };

        Mat2 b(a);

        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 0, 0 }
        }));
    }

    FR_STAGE("Copy Constructor for Different Size 4") {
        Matrix<double, 3, 2> a{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        };

        Mat2 b(a);

        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 3, 4 }
        }));
    }

    FR_STAGE("Copy Constructor for Different Size 4") {
        Matrix<double, 1, 2> a{
            { 1, 2 }
        };

        Mat2 b(a);

        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 0, 0 }
        }));
    }

    FR_STAGE("Copy Constructor for Different Size 5") {
        Matrix<double, 3, 3> a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        Mat2 b(a);

        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 4, 5 }
        }));
    }

    FR_STAGE("Matrix Multiplication 1") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        Mat2 b{
            { 5, 6 },
            { 7, 8 }
        };

        FR_REQUIRE(Eql(a * b, {
            { 19, 22 },
            { 43, 50 }
        }));
    }

    FR_STAGE("Matrix Multiplication 2") {
        Mat2 a{
            { 1.1, 2.2 },
            { 3.3, 4.4 }
        };

        Mat2x3 b{
            { 5, 6, 7  },
            { 8, 9, 10 }
        };

        auto r = a * b;

        FR_REQUIRE(Eql(a * b, {
            { 23.1, 26.4, 29.7 },
            { 51.7, 59.4, 67.1 }
        }));
    }
};