//-----------------------------------------------------------------------------
//Copyright (c) 2014 Peter Lama
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef GENERIC_DATA_ARRAY_H
#define GENERIC_DATA_ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename T, size_t N>
class MeshElement
{
public:
	MeshElement() { }
	MeshElement(const T* data)
	{
		for (size_t i = 0; i < N; ++i) {
			m_data[i] = *(data++);
		}
	}

	T* data() { return &m_data; }

	void fill(T value)
	{
		for (size_t i = 0; i < N; ++i) {
			m_data[i] = value;
		}
	}

	size_t length() { return N; }

	T& at(size_t index) 
	{
		if (index >= N) {
			throw std::out_of_range("MeshElement: index out of range");
		}
		return m_data[index];
	}
	T& operator[](size_t index) { return m_data[index]; }

private:
	T m_data[N];
};

template<typename T, size_t N = 3>
class GenericDataArray
{
public:
	typedef typename std::vector<MeshElement<T, N> >::iterator iterator;
	typedef typename std::vector<MeshElement<T, N> >::const_iterator const_iterator;
	typedef typename std::vector<MeshElement<T, N> >::value_type value_type;
  
	GenericDataArray() { }
	GenericDataArray(size_t length) : m_data(length) { }
	~GenericDataArray() { }
    
	void reserve(size_t count) { m_data.reserve(count); }

	bool empty() { return m_data.empty(); }
	size_t length() const { return m_data.size(); }
	unsigned int elementLength() const { return N; }
	unsigned int byteSize() const { return length() * sizeof(value_type); }

    iterator begin() const { return m_data.begin(); }
	iterator end() const { return m_data.end(); }
    
	value_type& at(size_t index) { return m_data.at(index) }
	T& at(size_t index, size_t elementIndex) { return m_data.at(index).at(elementIndex); }
	value_type& operator[](size_t index) { return m_data[index]; }

	const T* rawData() { return &m_data[0][0]; }
	void setRawData(const T* data) { std::copy(data, data + (length() * N), m_data); }
    
private:
    GenericDataArray(const GenericDataArray& other);

    std::vector<MeshElement<T, N> > m_data;
};

#endif // GENERIC_DATA_ARRAY_H
