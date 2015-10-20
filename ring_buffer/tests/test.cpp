#include <gtest/gtest.h>

#include <stdint.h>
#include "../ring_buffer.h"

TEST (RingBuffer, defaultConstructor)
{
    RingBuffer<uint8_t, 10> my_buffer;
}


TEST (RingBuffer, overflow)
{
    RingBuffer<uint8_t, 3> my_buffer;

    ASSERT_EQ(my_buffer.getCount(), 0);
    my_buffer.push(0);
    ASSERT_EQ(my_buffer.getCount(), 1);
    my_buffer.push(1);
    ASSERT_EQ(my_buffer.getCount(), 2);
    my_buffer.push(2);
    ASSERT_EQ(my_buffer.getCount(), 3);

/// should bump out the first 0
    my_buffer.push(3);
    ASSERT_EQ(my_buffer.getCount(), 3);
    uint8_t popped_value;
    my_buffer.pop(popped_value);
    ASSERT_EQ(popped_value, 1);
}


TEST (RingBuffer, basicPop)
{
    uint8_t popped_value;
    uint8_t pushed_value = 3;
    RingBuffer<uint8_t, 10> my_buffer;

    my_buffer.push(pushed_value);
    my_buffer.pop(popped_value);

    ASSERT_EQ(popped_value, pushed_value);
}

TEST (RingBuffer, emptyPop)
{
    uint8_t popped_value;
    RingBuffer<uint8_t, 10> my_buffer;
    ASSERT_EQ(my_buffer.getCount(), 0);

// can't pop anything off if it's empty!
    ASSERT_EQ(my_buffer.pop(popped_value), false);
}


TEST (RingBuffer, basicPeek)
{
    uint8_t peeked_value;
    uint8_t pushed_value = 3;
    RingBuffer<uint8_t, 10> my_buffer;

    ASSERT_EQ(my_buffer.getCount(), 0);
    my_buffer.push(pushed_value);

    my_buffer.peek(peeked_value);

    ASSERT_EQ(my_buffer.getCount(), 1);
    ASSERT_EQ(peeked_value, pushed_value);
}


TEST (RingBuffer, emptyPeek)
{
    uint8_t peeked_value;
    RingBuffer<uint8_t, 10> my_buffer;
    ASSERT_EQ(my_buffer.getCount(), 0);

// can't pop anything off if it's empty!
    ASSERT_EQ(my_buffer.peek(peeked_value), false);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
