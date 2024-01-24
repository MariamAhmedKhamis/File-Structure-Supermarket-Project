#include"varlen.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>

//class VariableLengthRecord

// public members
VariableLengthRecord::VariableLengthRecord()
{
	m_recordFields = 0;
	m_iFieldsCount = 0;
	m_iNextByte = 0;
	m_iRecordSize = 0;
	pRecord = 0;
}
void VariableLengthRecord::init(int iFieldsCount)
{
	m_iFieldsCount = iFieldsCount;
	m_recordFields = new Field[m_iFieldsCount];
}

void VariableLengthRecord::AddField(int index, char szType, char delimiter) // D
{
	m_recordFields[index].szFieldRepresentation = szType;
	m_recordFields[index].delimiter = delimiter;
}
void VariableLengthRecord::AddField(int index, char szType, int length)  // L , F
{
	m_recordFields[index].szFieldRepresentation = szType;
	m_recordFields[index].length = length;
}

// Write Header
bool VariableLengthRecord::WriteHeader(ostream& stream) const
{
	stream.write((char*)&m_iFieldsCount, 1);  // 2
	if (stream.fail())
		return false;

	for (int i = 0; i < m_iFieldsCount; i++)
	{
		stream.write(&m_recordFields[i].szFieldRepresentation, 1);
		if (stream.fail())
			return false;

		if (m_recordFields[i].szFieldRepresentation == 'F' || m_recordFields[i].szFieldRepresentation == 'L')
			stream.write(&m_recordFields[i].length, 1);
		else if (m_recordFields[i].szFieldRepresentation == 'D')
			stream.write(&m_recordFields[i].delimiter, 1);

		if (stream.fail())
			return false;
	}

	return true;
}
// read the header and check for consistency
bool VariableLengthRecord::ReadHeader(istream& stream)
{
	stream.read((char*)&m_iFieldsCount, 1);
	if (stream.fail())
		return false;

	m_recordFields = new Field[m_iFieldsCount];

	for (int i = 0; i < m_iFieldsCount; i++)
	{
		stream.read(&m_recordFields[i].szFieldRepresentation, 1);
		if (stream.fail())
			return false;

		if (m_recordFields[i].szFieldRepresentation == 'F' || m_recordFields[i].szFieldRepresentation == 'L')
			stream.read(&m_recordFields[i].length, 1);
		else if (m_recordFields[i].szFieldRepresentation == 'D')
			stream.read(&m_recordFields[i].delimiter, 1);

		if (stream.fail())
			return false;
	}
	return true;
}

void VariableLengthRecord::Clear(int recordSize)//= -1 // 
{
	m_iNextByte = 0;
	m_iRecordSize = 0;

	if (pRecord != 0)
		delete pRecord;

	if (recordSize != -1)
		pRecord = new char[recordSize];
	else
		pRecord = 0;
}


bool VariableLengthRecord::PackFixLen(void* lpData, int dataLength, int fieldLength)
{
	memset(pRecord + m_iNextByte, 0, fieldLength);

	if (dataLength > fieldLength)
		dataLength = fieldLength;

	memcpy(&pRecord[m_iNextByte], lpData, dataLength);

	m_iNextByte += fieldLength;
	m_iRecordSize = m_iNextByte;

	return true;
}
bool VariableLengthRecord::PackDelimeted(void* lpData, int length, char delimiter)
{
	memcpy(&pRecord[m_iNextByte], lpData, length);
	pRecord[m_iNextByte + length] = delimiter; // add delimeter

	m_iNextByte += length + 1;
	m_iRecordSize = m_iNextByte;

	return true;
}
bool VariableLengthRecord::PackLength(void* lpData, short length, char lengthIndicatorSize)
{
	memcpy(&pRecord[m_iNextByte], &length, lengthIndicatorSize);

	memcpy(&pRecord[m_iNextByte + lengthIndicatorSize], lpData, length);

	m_iNextByte += lengthIndicatorSize + length;
	m_iRecordSize = m_iNextByte;

	return true;
}


bool VariableLengthRecord::Pack(int index, void* lpData, int dataLength)
{
	if (m_recordFields[index].szFieldRepresentation == 'F')
		return PackFixLen(lpData, dataLength, m_recordFields[index].length);

	if (m_recordFields[index].szFieldRepresentation == 'D')
		return PackDelimeted(lpData, dataLength, m_recordFields[index].delimiter);

	return PackLength(lpData, dataLength, m_recordFields[index].length);
}


bool VariableLengthRecord::UnpackFixLen(char* lpData, int fieldLength)
{
	memcpy(lpData, pRecord + m_iNextByte, fieldLength);
	m_iNextByte += fieldLength;
	return true;
}
bool VariableLengthRecord::UnpackDelimeted(char* lpData, char delimiter, bool bIsText/* /= false / */)
{
	int len = -1; // length of unpacked string

	for (int i = m_iNextByte; i < m_iRecordSize; i++)
	{
		if (pRecord[i] == delimiter)
		{
			len = i - m_iNextByte;
			break;
		}
	}

	if (len == -1)
		return false; // delimeter not found

	memcpy(lpData, pRecord + m_iNextByte, len);

	if (bIsText)
		lpData[len] = 0; // zero termination for string 

	m_iNextByte += len + 1;

	return true;
}
bool VariableLengthRecord::UnpackLength(char* lpData, char lengthIndicatorSize, bool bIsText) //= false // )
{
	short length;

	memcpy(&length, pRecord + m_iNextByte, lengthIndicatorSize);

	memcpy(lpData, pRecord + m_iNextByte + lengthIndicatorSize, length);
	if (bIsText)
		lpData[length] = 0;

	m_iNextByte += length + lengthIndicatorSize;
	return true;
}
bool VariableLengthRecord::Unpack(int index, char* lpData, bool bIsText /*/= false / */)
{
	if (m_recordFields[index].szFieldRepresentation == 'F')
		return UnpackFixLen(lpData, m_recordFields[index].length);

	if (m_recordFields[index].szFieldRepresentation == 'D')
		return UnpackDelimeted(lpData, m_recordFields[index].delimiter, bIsText);

	return UnpackLength(lpData, m_recordFields[index].length, bIsText);
}

bool VariableLengthRecord::Read(istream& stream)
{
	Clear();
	stream.read((char*)&m_iRecordSize, sizeof(m_iRecordSize));
	if (stream.fail())
		return false;

	pRecord = new char[m_iRecordSize];
	stream.read(pRecord, m_iRecordSize);
	return !stream.fail();
}

bool VariableLengthRecord::Write(ostream& stream) const
// write the length and buffer into the stream
{
	stream.write((char*)&m_iRecordSize, sizeof(m_iRecordSize)); //write delimiter
	if (stream.fail())
		return false;

	stream.write(pRecord, m_iRecordSize);
	return !stream.fail();
}