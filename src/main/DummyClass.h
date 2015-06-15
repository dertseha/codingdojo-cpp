#ifndef H_DUMMY_CLASS
#define H_DUMMY_CLASS

class DummyClass
{
public:
	DummyClass(int value);
	~DummyClass();

	int getValue() const;

private:
	int value;
};

#endif
