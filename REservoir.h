#pragma once
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include<algorithm>

#include "String.h"

using namespace std;

enum class ReservoirType
{
	OCEAN, SEA, RIVER, LAKE, POND, PUDDLE, UNDEFINE =-1
};

const char* getReservoirType(ReservoirType type)
{
	switch (type)
	{
	case ReservoirType::OCEAN:  return "Ocean";
	case ReservoirType::SEA:    return "Sea";
	case ReservoirType::RIVER:  return "River";
	case ReservoirType::LAKE:   return "Lake";
	case ReservoirType::POND:   return "Pond";
	case ReservoirType::PUDDLE: return "Puddle";
	default:            		return "Undefined";
	}
}

class Reservoir
{
	ReservoirType type;
	String name;
	double width;
	double length;
	double depth;

public:
	Reservoir(ReservoirType type, String name, double width, double length, double depth)
	{
		this->type = type;
		this->name = name;
		this->width = width;
		this->length = length;
		this->depth = depth;
	}

	void printRes() const
	{
		cout << "Type: " << getReservoirType(type) << endl;
		cout << "Name:"  << name.get() << endl;
		cout << "width:" << width << endl;
		cout << "length:" << length << endl;
		cout << "depth:" << depth << endl;
	
	}


	//
	void setName(const String& newName)
	{ 
		name = newName; 
	}
	String getName() const 
	{
		return name; 
	}

	void setDimensions(double newWidth, double newLength, double newDepth)
	{
		width = newWidth;
		length = newLength;
		depth = newDepth;
	}

	void getDimensions(double& outWidth, double& outLength, double& outDepth) const
	{
		outWidth = width;
		outLength = length;
		outDepth = depth;
	}

	void setType(ReservoirType newType) 
	{ 
		type = newType; 
	}
	ReservoirType getType() const 
	{ 
		return type; 
	}



//////////////////

	double VolumeVodichki() const
	{
		return width * length * depth;
	}

	double calcSurfaceArea() const
	{
		return width * length;
	}

	bool isType(const Reservoir& other) const
	{
		return this->type == other.type;
	}

	bool compareSurfaceArea(const Reservoir& other) const
	{
		return this->calcSurfaceArea() > other.calcSurfaceArea();
	}


	void saveToTextik(ofstream& out) const
	{
		out << getReservoirType(type) << " " << name.get() << " "
			<< width << " " << length << " " << depth << endl;
	}

	void saveToBinarTextit  (ofstream& out) const
	{
		out.write((char*)&type, sizeof(type));
		int nameLength = name.length();
		out.write((char*)&nameLength, sizeof(nameLength));
		out.write(name.get(), nameLength);
		out.write((char*)&width, sizeof(width));
		out.write((char*)&length, sizeof(length));
		out.write((char*)&depth, sizeof(depth));
	}
	///////////
	void loadFromText(ifstream& in)
	{
		string typeStr;
		char nameBuffer[256];
		in >> typeStr >> nameBuffer >> width >> length >> depth;
		type = static_cast<ReservoirType>(distance(begin(typeStr), find(begin(typeStr), end(typeStr), typeStr)));
		name.set(nameBuffer);
	}

	////////
	
	
	//////
	Reservoir& operator=(const Reservoir& other)
	{
		if (this != &other)
		{
			type = other.type;
			name = other.name;
			width = other.width;
			length = other.length;
			depth = other.depth;
		}
		return *this;
	}
};