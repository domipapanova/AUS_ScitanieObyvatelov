#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size_);
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other) {
			Vector& otherVector = dynamic_cast<Vector&>(other); //dynamic_cast pretypovanie po hierarchii 
			size_ = otherVector.size_;
			memory_= realloc(memory_, size_); //realokacia pamati
			memcpy(memory_, otherVector.memory_, size_);

		}
		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		if (this == &other) {
			return true;
		}
		else {
			Vector* otherVector = dynamic_cast<Vector*>(&other);
			if (otherVector != nullptr) {
				return size_ == otherVector->size_ && memcmp(memory_, otherVector->memory_, size_) == 0;
			}
			else {
				return false;
			}
		}
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Invalid index"); //kontrola indexu
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		//srcStartIndex musi partit do <0,src.size_)
		//srcStartIndex + length musi do  <0,src.size_>
		//destStartIndex  musi partit do <0,des.size_)
		//destStartIndex + length musi do  <0,des.size_>
		//ak su identicke a zaroven je abs. hodnota rodzdielu destStartIndex a srcStartIndex < length
		//tak: memmove
		//inak: memcpy
		Utils::rangeCheckExcept(srcStartIndex, src.size_, "Invalid srcStartIndex!");
		Utils::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid srcStartIndex + length index!");
		Utils::rangeCheckExcept(destStartIndex, src.size_, "Invalid destStartIndex!");
		Utils::rangeCheckExcept(destStartIndex + length, src.size_ + 1, "Invalid destStartIndex + length index!");

		if (&src == &dest && abs(destStartIndex - srcStartIndex) < length) {
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Invalid index"); //kontrola indexu
		return reinterpret_cast<byte*>(memory_) + index;
	}
}