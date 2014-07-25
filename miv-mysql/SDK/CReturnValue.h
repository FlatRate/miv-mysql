#pragma once

#include <string>
#include "ScriptArgument.h"
#include "Entity.h"

class CReturnValue : public SDK::ScriptArgument
{
private:
	eType type;
	void* data;
	double d;
	std::string str;
	SDK::ScriptArguments* args;

public:
	CReturnValue()
	{
		type = NIL;
		data = NULL;
		args = NULL;
	}

	CReturnValue(SDK::ScriptArgument* argument)
	{
		type = argument->GetType();
		data = NULL;
		args = NULL;

		switch (type)
		{
		case BOOL:
			data = (void*)argument->ToBool();
			break;
		case INTEGER:
			data = (void*)argument->ToInteger();
			break;
		case FLOAT:
			d = argument->ToFloat();
			break;
		case STRING:
			str = argument->ToString();
			break;
		case TABLE:
			args = argument->ToTable();
			break;
		case ARRAY:
			args = argument->ToArray();
			break;
		case CLASS:
			data = (void*)argument->ToClass();
			break;
		case INSTANCE:
			data = (void*)argument->ToInstance();
			break;
		case FUNCTION:
			data = (void*)argument->ToFunction();
			break;
		}
	}

	CReturnValue(SDK::ScriptClass* classdef)
	{
		type = CLASS;
		data = (void*)classdef;
		args = NULL;
	}

	CReturnValue(SDK::ScriptInstance* instance)
	{
		type = INSTANCE;
		data = (void*)instance;
		args = NULL;
	}

	CReturnValue(const char* c)
	{
		if(c == NULL)
			CReturnValue();
		else
		{
			type = STRING;
			str = c;
		}

		args = NULL;
	}

	CReturnValue(std::string str)
	{
		type = STRING;
		this->str = str;
		args = NULL;
	}

	CReturnValue(int i)
	{
		type = INTEGER;
		data = (void*)i;
		args = NULL;
	}

	CReturnValue(unsigned int ui)
	{
		type = INTEGER;
		data = (void*)ui;
		args = NULL;
	}

	CReturnValue(long l)
	{
		type = INTEGER;
		data = (void*)l;
		args = NULL;
	}

	CReturnValue(unsigned long ul)
	{
		type = INTEGER;
		data = (void*)ul;
		args = NULL;
	}

	CReturnValue(double d)
	{
		type = FLOAT;
		this->d = d;
		args = NULL;
	}

	CReturnValue(bool b)
	{
		type = BOOL;
		data = (void*)(b != 0);
		args = NULL;
	}

	CReturnValue(SDK::ScriptArguments* args, bool isarray = false)
	{
		type = (isarray ? ARRAY : TABLE);
		this->args = args;
	}

	~CReturnValue()
	{
		if (args)
			delete args;
	}

	SDK::ScriptArgument* Clone()
	{
		return new CReturnValue(this);
	}

	eType GetType() {
		return type;
	}

	bool ToBool()
	{
		if (type == BOOL)
			return ((int)data != 0);

		throw "not a boolean";
	}

	short ToShort()
	{
		int i = ToInteger();

		if ((unsigned short)i > 65535)
			throw "not a short";

		return (short)i;
	}

	int ToInteger()
	{
		if(type == INTEGER)
			return (int) data;

		throw "not an integer";
	}

	float ToFloat() {
		return (float)ToDouble();
	}

	double ToDouble()
	{
		if(type == FLOAT)
			return d;

		if(type == INTEGER)
			return (int)data;

		throw "not a float";
	}

	const char* ToString()
	{
		if (type == STRING)
			return str.c_str();

		throw "not a string";
	}

	SDK::ScriptArguments* ToTable()
	{
		if (type == TABLE)
			return args;

		throw "not a table";
	}

	SDK::ScriptArguments* ToArray()
	{
		if (type == ARRAY)
			return args;

		throw "not an array";
	}

	SDK::ScriptClass* ToClass()
	{
		if (type == CLASS)
			return (SDK::ScriptClass*)data;

		throw "not a class";
	}

	SDK::ScriptInstance* ToInstance()
	{
		if (type == INSTANCE)
			return (SDK::ScriptInstance*)data;

		throw "not an instance";
	}

	void* ToFunction() {
		return 0;
	}
};

// TODO: MOVE ME
//{
	// helper class
	class ScriptTable
	{
	private:
		SDK::ScriptArguments* m_pTable;

	public:
		ScriptTable() { m_pTable = new SDK::ScriptArguments; }

		SDK::ScriptArguments* GetTable() { return m_pTable; }

		void Add(SDK::ScriptArgument* pIndex, SDK::ScriptArgument* pValue)
		{
			SDK::ScriptArguments* pEntry = new SDK::ScriptArguments;
			pEntry->Add(pIndex);
			pEntry->Add(pValue);
			m_pTable->Add(new CReturnValue(pEntry, true));
		}
	};

	// helper class
	class ScriptArray
	{
	private:
		SDK::ScriptArguments* m_pArray;

	public:
		ScriptArray() { m_pArray = new SDK::ScriptArguments; }

		SDK::ScriptArguments* GetArray() { return m_pArray; }

		void Add(SDK::ScriptArgument* pValue) { m_pArray->Add(pValue); }
	};
//}
