#include <gtest/gtest.h>
#include "color.hpp"

using namespace RT;

class ColorTest : public ::testing::Test {
protected:
    void SetUp() override {
        a = Color({0.11, 0.22, 0.33});
        b = Color({0.5, 0.6, 0.7});
    }

    Color a;
    Color b;
};

TEST_F(ColorTest, Getters) {
    EXPECT_FLOAT_EQ(a.red(), 0.11);
    EXPECT_FLOAT_EQ(a.green(), 0.22);
    EXPECT_FLOAT_EQ(a.blue(), 0.33);
}

TEST_F(ColorTest, Comparison) {
    Color aa({0.11, 0.22, 0.33});
    Color bb({0.5, 0.6, 0.7});
    
    EXPECT_EQ(aa, a);
    EXPECT_EQ(bb, b);

    EXPECT_NE(a, b);
    EXPECT_NE(aa, bb);
}

// TEST_F(ColorTest, Addition) {
//     Color c({0.61, 0.82, 1.03});
//     EXPECT_EQ(a + b, c);
// }
