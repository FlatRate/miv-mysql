#pragma once

#ifndef NULL
	#define NULL 0
#endif

#include <vector>
#include <string>

#define TYPE_STR(t) case t: return #t

namespace SDK
{
	class ScriptArgument;
	class ScriptArguments;
	class ScriptClass;
	class ScriptInstance;

	class ScriptArgument
	{
	public:
		enum eType
		{
			ANY,
			NIL,
			BOOL,
			INTEGER,
			FLOAT,
			STRING,
			TABLE,
			ARRAY,
			CLASS,
			INSTANCE,
			FUNCTION
		};

		virtual ~ScriptArgument() {}

		virtual ScriptArgument* Clone() = 0;

		virtual eType GetType() = 0;

		virtual const char* GetTypeString()
		{
			switch (GetType())
			{
			TYPE_STR(NIL);
			TYPE_STR(BOOL);
			TYPE_STR(INTEGER);
			TYPE_STR(FLOAT);
			TYPE_STR(STRING);
			TYPE_STR(TABLE);
			TYPE_STR(ARRAY);
			TYPE_STR(CLASS);
			TYPE_STR(INSTANCE);
			TYPE_STR(FUNCTION);
			}

			return "UNKNOWN";
		}

		virtual bool             ToBool() = 0;
		virtual short            ToShort() = 0;
		virtual int              ToInteger() = 0;
		virtual float            ToFloat() = 0;
		virtual double           ToDouble() = 0;
		virtual const char*      ToString() = 0;
		virtual ScriptArguments* ToTable() = 0;
		virtual ScriptArguments* ToArray() = 0;
		virtual ScriptClass*     ToClass() = 0;
		virtual ScriptInstance*  ToInstance() = 0;
		virtual void*            ToFunction() = 0;
	};

	inline const char* GetTypeString( ScriptArgument::eType type )
	{
		switch ( type )
		{
			TYPE_STR( ScriptArgument::NIL );
			TYPE_STR( ScriptArgument::BOOL );
			TYPE_STR( ScriptArgument::INTEGER );
			TYPE_STR( ScriptArgument::FLOAT );
			TYPE_STR( ScriptArgument::STRING );
			TYPE_STR( ScriptArgument::TABLE );
			TYPE_STR( ScriptArgument::ARRAY );
			TYPE_STR( ScriptArgument::CLASS );
			TYPE_STR( ScriptArgument::INSTANCE );
			TYPE_STR( ScriptArgument::FUNCTION );
		}

		return "UNKNOWN";
	}
}
