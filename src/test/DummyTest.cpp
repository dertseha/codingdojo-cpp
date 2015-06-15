#include <gtest/gtest.h>

#include <DummyClass.h>

class DummyTest: public testing::Test
{
public:

protected:
    virtual void SetUp();
};


void DummyTest::SetUp()
{

}

TEST_F(DummyTest, VerifyTestSystemWorks)
{
	DummyClass dummy(42);

	EXPECT_EQ(42, dummy.getValue());
}
