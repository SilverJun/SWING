#include "ProtocolType.h"
#include "SwingCompiler.h"

namespace swing
{
	void ProtocolType::CreateProtocolType()
	{

	}

	void ProtocolType::ConformCheck(StructType* structType)
	{
		bool cantFind = true;
		for (auto value : _requirePropertys)
		{
			for (auto structProperty : structType->_value)
				if (value._name == structProperty._name)
					if (value._type == structProperty._type)
						cantFind = false;
			
			if (cantFind)
				throw Error("Protocol Conform Check Error! " + value._name + " type is not same");
			cantFind = true;
		}

		cantFind = true;
		for (auto method : _requireMethods)
		{
			for (auto structMethod : structType->_method)
			{
				if (method.first == structMethod.first)
				{
					if (method.second._returnType == structMethod.second._returnType && method.second._funcName == structMethod.second._funcName)
					{
						if (method.second._args.size() == 0 && structMethod.second._args.size() == 0)
						{
							cantFind = false;
							break;
						}

						for (auto arg : method.second._args)
						{
							for (auto structArg : structMethod.second._args)
							{
								if (arg->_typeName == structArg->_typeName && arg->_name == structArg->_name)
								{
									cantFind = false;
								}
							}
						}
					}
				}
			}
			
			if (cantFind)
				throw Error("Protocol Conform Check Error! " + method.first + " function is not same");
			cantFind = true;
		}
	}
}
