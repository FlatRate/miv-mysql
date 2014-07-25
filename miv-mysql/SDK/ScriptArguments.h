#pragma once

#define IS_EVENT_CANCELLED(arguments) arguments.ContainsValue(false)
#define IS_EVENT_HANDLED(arguments) arguments.ContainsValue(true)

#include "ScriptArgument.h"
#include <vector>

namespace SDK
{
	struct ParameterCheck
	{
		int iMinimumParameters; // min amount of params (min 0)
		int iMaximumParameters; // max amount of params (-1 for unlimited)
		std::vector<SDK::ScriptArgument::eType> typeList; // parameter types
	};

	class ScriptArguments
	{
	private:
		void*                        m_pScriptPointer;
		std::vector<ScriptArgument*> m_vecArguments;

	public:
		ScriptArguments() { m_pScriptPointer = NULL; }
		ScriptArguments(void* pScriptPointer) { m_pScriptPointer = pScriptPointer; }

		ScriptArguments::ScriptArguments(const ScriptArguments& other)
		{
			m_pScriptPointer = other.m_pScriptPointer;

			for (SDK::ScriptArgument* pArgument : other.m_vecArguments)
				m_vecArguments.push_back(pArgument->Clone());
		}

		~ScriptArguments()
		{
			for (ScriptArgument* pArgument : m_vecArguments)
				delete pArgument;

			m_vecArguments.clear();
		}

		void* GetScriptPointer() { return m_pScriptPointer; }
		int Count() { return (int)m_vecArguments.size(); }

		ScriptArgument* Get(unsigned int index) { return ((index < m_vecArguments.size()) ? m_vecArguments.at(index) : NULL); }
		ScriptArgument* operator[](unsigned int index) { return ((index < m_vecArguments.size()) ? m_vecArguments.at(index) : NULL); }

#define ARGS_GET_TEMPLATE(type, func) type Get##func(unsigned int index) { return Get(index)->To##func(); } \
										type GetOpt##func(unsigned int index, type opt) { return (m_vecArguments.size() > index ? Get(index)->To##func() : opt); }

		ARGS_GET_TEMPLATE(bool, Bool);
		ARGS_GET_TEMPLATE(short, Short);
		ARGS_GET_TEMPLATE(int, Integer);
		ARGS_GET_TEMPLATE(float, Float);
		ARGS_GET_TEMPLATE(double, Double);
		ARGS_GET_TEMPLATE(const char*, String);
		ARGS_GET_TEMPLATE(ScriptArguments*, Table);
		ARGS_GET_TEMPLATE(ScriptArguments*, Array);
		ARGS_GET_TEMPLATE(ScriptClass*, Class);
		ARGS_GET_TEMPLATE(ScriptInstance*, Instance);
		ARGS_GET_TEMPLATE(void*, Function);

		void AddFirst(ScriptArgument* pArgument) { m_vecArguments.insert(m_vecArguments.begin(), pArgument); }
		void Add(ScriptArgument* pArgument) { m_vecArguments.push_back(pArgument); }

		void AddFirst(ScriptArguments* pArguments)
		{
			for (ScriptArgument* pArgument : pArguments->m_vecArguments)
				m_vecArguments.insert(m_vecArguments.begin(), pArgument->Clone());
		}

		void Add(ScriptArguments* pArguments)
		{
			for (ScriptArgument* pArgument : pArguments->m_vecArguments)
				m_vecArguments.push_back(pArgument->Clone());
		}

		void Check(ParameterCheck* pParameterCheck)
		{
			// Ensure we have enough parameters
			if (Count() < pParameterCheck->iMinimumParameters)
			{
				//CLogFile::Printf("Call to function %s with not enough parameters (Expected %d+, Got %d)", strName.Get(), pParameterCheck->iMinimumParameters, iTop);
				throw "not enough parameters";
			}

			// Ensure we don't have too many parameters
			if (pParameterCheck->iMaximumParameters != -1 && Count() > pParameterCheck->iMaximumParameters)
			{
				//CLogFile::Printf("Call to function %s with too many parameters (Expected %d, Got %d)", strName.Get(), pParameterCheck->iMaximumParameters, iTop);
				throw "too many parameters";
			}

			// Ensure we don't have any invalid types
			int iParam = 0;

			for (std::vector<SDK::ScriptArgument::eType>::iterator iter = pParameterCheck->typeList.begin(); iter != pParameterCheck->typeList.end(); iter++)
			{
				if (iParam >= Count())
					break;

				if ((*iter) != SDK::ScriptArgument::ANY && Get(iParam)->GetType() != (*iter))
				{
					//CLogFile::Printf("Invalid type for function %s, parameter %d (Expected %d, Got %d)", strName.Get(), iParam, *iter, type);
					char szErrorMessage[512] = {0};
					sprintf_s(szErrorMessage, "Invalid type for function parameter %d (Expected %s, Got %s)", iParam, Get(iParam)->GetTypeString(), GetTypeString(*iter));
					throw szErrorMessage;
				}

				iParam++;
			}
		}

		// TODO: ScriptArguments::ContainsValue for every type (that way if you wanna check if an event had any func return true you would just do returnValues.HasValue(true)
		// TODO: ReturnValues class which contains a ScriptArguments value and special copy operators and these functions?

		bool HasValueType(SDK::ScriptArgument::eType type)
		{
			for (SDK::ScriptArgument* pArgument : m_vecArguments)
			{
				if (pArgument->GetType() == type)
					return true;
			}

			return false;
		}

		SDK::ScriptArgument* GetValueType(SDK::ScriptArgument::eType type)
		{
			for (SDK::ScriptArgument* pArgument : m_vecArguments)
			{
				if (pArgument->GetType() == type)
					return pArgument;
			}

			return NULL;
		}

		bool ContainsValue(bool bValue)
		{
			for (SDK::ScriptArgument* pArgument : m_vecArguments)
			{
				if (pArgument->GetType() == SDK::ScriptArgument::BOOL && pArgument->ToBool() == bValue)
					return true;
			}

			return false;
		}
	};
}
