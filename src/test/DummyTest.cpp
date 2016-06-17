#include <gmock/gmock.h>

#include <DummyClass.h>

class DummyTest: public testing::Test
{
public:
   class Thingie
   {
   public:
      virtual ~Thingie() = default;

      virtual void doStuff() = 0;
   };

   class MockedThing: public Thingie
   {
   public:
      MOCK_METHOD0(doStuff, void());
   };

protected:
   void SetUp() override;
};


void DummyTest::SetUp()
{

}

TEST_F(DummyTest, VerifyTestSystemWorks)
{
   DummyClass dummy(42);

   EXPECT_EQ(42, dummy.getValue());
}

TEST_F(DummyTest, VerifyMockingSystemWorks)
{
   MockedThing thing;

   EXPECT_CALL(thing, doStuff());

   thing.doStuff();
}
