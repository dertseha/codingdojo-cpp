#include "DummyClass.h"

DummyClass::DummyClass(int value)
	:	value(value)
{

}

DummyClass::~DummyClass()
{
	
}

int DummyClass::getValue() const
{
	return value;
}
