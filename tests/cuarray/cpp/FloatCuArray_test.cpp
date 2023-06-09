
#include <gtest/gtest.h>

#include "FloatCuArrayFixture.h"
#include "cuarray.h"


TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_m
) {
    EXPECT_EQ(cuArrayNoData->m(), 20);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_n
) {
    EXPECT_EQ(cuArrayNoData->n(), 100);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_bytes
) {
    EXPECT_EQ(cuArrayNoData->bytes(), 2000 * sizeof(float));
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_size
) {
    EXPECT_EQ(cuArrayNoData->size(), 2000);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_allocatedHost
) {
    EXPECT_EQ(cuArrayNoData->allocatedHost(), 1);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_allocatedDevice
) {
    EXPECT_EQ(cuArrayNoData->allocatedDevice(), 0);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_host
) {
    for (int i = 0; i < 2000; i++) {
        EXPECT_EQ(cuArrayNoData->host()[i], 0);
    }
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoData_allocateDevice
) {
    cuArrayNoData->allocateDevice();
    EXPECT_EQ(cuArrayNoData->allocatedDevice(), 1);
    cuArrayNoData->deallocateDevice();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoDataTest_toDeviceNegative
) {
    cuArrayNoData->toDevice();
    EXPECT_EQ(cuArrayNoData->allocatedDevice(), 0);
    cuArrayNoData->deallocateDevice();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoDataTest_toDevicePositive
) {
    cuArrayNoData->allocateDevice();
    cuArrayNoData->toDevice();
    EXPECT_EQ(cuArrayNoData->allocatedDevice(), 1);
    cuArrayNoData->deallocateDevice();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoDataTest_toHostNegative
) {
    cuArrayNoData->toHost();
    EXPECT_EQ(cuArrayNoData->allocatedHost(), 0);
    cuArrayNoData->deallocateHost();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayNoDataTest_toHostPositive
) {
    cuArrayNoData->allocateHost();
    cuArrayNoData->toHost();
    EXPECT_EQ(cuArrayNoData->allocatedHost(), 1);
    cuArrayNoData->deallocateHost();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_m
) {
    EXPECT_EQ(cuArrayWithData->m(), 20);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_n
) {
    EXPECT_EQ(cuArrayWithData->n(), 100);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_bytes
) {
    EXPECT_EQ(cuArrayWithData->bytes(), 2000 * sizeof(float));
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_size
) {
    EXPECT_EQ(cuArrayWithData->size(), 2000);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_allocatedHost
) {
    EXPECT_EQ(cuArrayWithData->allocatedHost(), 1);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_allocatedDevice
) {
    EXPECT_EQ(cuArrayWithData->allocatedDevice(), 0);
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_host
) {
    for (int i = 0; i < 2000; i++) {
        EXPECT_EQ(cuArrayWithData->host()[i], data[i]);
    }
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_get
) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 100; j++) {
            EXPECT_EQ(cuArrayWithData->get(i, j), data[i * 100 + j]);
        }
    }
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithData_allocateDevice
) {
    cuArrayWithData->allocateDevice();
    EXPECT_EQ(cuArrayWithData->allocatedDevice(), 1);
    cuArrayWithData->deallocateDevice();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithDataTest_toDeviceNegative
) {
    cuArrayWithData->toDevice();
    EXPECT_EQ(cuArrayWithData->allocatedDevice(), 0);
    cuArrayWithData->deallocateDevice();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithDataTest_toDevicePositive
) {
    cuArrayWithData->allocateDevice();
    cuArrayWithData->toDevice();
    EXPECT_EQ(cuArrayWithData->allocatedDevice(), 1);
    cuArrayWithData->deallocateDevice();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithDataTest_toHostNegative
) {
    cuArrayWithData->toHost();
    EXPECT_EQ(cuArrayWithData->allocatedHost(), 0);
    cuArrayWithData->deallocateHost();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArrayWithDataTest_toHostPositive
) {
    cuArrayWithData->allocateHost();
    cuArrayWithData->toHost();
    EXPECT_EQ(cuArrayWithData->allocatedHost(), 1);
    cuArrayWithData->deallocateHost();
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArray_fromCuArrayShallowCopy
) {
    auto cuArrayShallowCopy = new CuArray<float>;
    cuArrayShallowCopy->fromCuArrayShallowCopy(
            cuArrayWithData,
            19,
            19, 1, 100
    );
    EXPECT_EQ(cuArrayShallowCopy->m(), 1);
    EXPECT_EQ(cuArrayShallowCopy->n(), 100);
    EXPECT_EQ(cuArrayShallowCopy->bytes(), 100 * sizeof(float));
    EXPECT_EQ(cuArrayShallowCopy->size(), 100);
    EXPECT_EQ(cuArrayShallowCopy->allocatedHost(), 1);
    EXPECT_EQ(cuArrayShallowCopy->allocatedDevice(), 0);
    EXPECT_EQ(
            cuArrayShallowCopy->owner(), 0
    );
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(
                cuArrayShallowCopy->get(0, i),
                cuArrayWithData->get(19, i)
        );
    }
    delete cuArrayShallowCopy;
    for (int i = 0; i < 100; i++) {
        EXPECT_NO_FATAL_FAILURE(
                cuArrayWithData->get(19, i)
        );
    }
}

TEST_F(
        FloatCuArrayFixture,
        FloatCuArray_fromCuArrayDeepCopy
) {
    auto cuArrayDeepCopy = new CuArray<float>;
    cuArrayDeepCopy->fromCuArrayDeepCopy(
            cuArrayWithData,
            19,
            19, 1, 100
    );
    EXPECT_EQ(cuArrayDeepCopy->m(), 1);
    EXPECT_EQ(cuArrayDeepCopy->n(), 100);
    EXPECT_EQ(cuArrayDeepCopy->bytes(), 100 * sizeof(float));
    EXPECT_EQ(cuArrayDeepCopy->size(), 100);
    EXPECT_EQ(cuArrayDeepCopy->allocatedHost(), 1);
    EXPECT_EQ(cuArrayDeepCopy->allocatedDevice(), 0);
    EXPECT_EQ(
            cuArrayDeepCopy->owner(), 1
    );
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(
                cuArrayDeepCopy->get(0, i),
                cuArrayWithData->get(19, i)
        );
    }
    delete cuArrayDeepCopy;
    for (int i = 0; i < 100; i++) {
        EXPECT_NO_FATAL_FAILURE(
                cuArrayWithData->get(19, i)
        );
    }
}

int main(
        int argc,
        char **argv
) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
