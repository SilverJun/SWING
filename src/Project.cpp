#include "Project.h"

#include <fstream>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

namespace swing
{
	Project::Project(std::string projName, std::string projFolderPath) : _projName(projName), _projPath(projFolderPath)
	{

		SaveProjectFile();
	}

	Project::Project(std::string projFile)
	{
		std::ifstream projIfs(projFile);

		_projJson.ParseStream(projIfs);

		_projName = _projJson["ProjectName"].GetString();
		_projPath = _projJson["ProjectPath"].GetString();
		_binFileName = _projJson["BinaryFileName"].GetString();

		if (!_projJson["SourceList"].Empty() && _projJson["SourceList"].IsArray()) { return; }

		auto sourceList = _projJson["SourceList"].GetArray();

		for (rapidjson::Value::ValueIterator iter = sourceList.Begin(); iter != sourceList.End(); ++iter)
		{
			_sourcesPath.push_back((*iter).GetString());
		}
	}

	Project::~Project()
	{
	}

	void Project::SetProjectName(std::string name)
	{
	}

	void Project::SetProjectPath(std::string path)
	{
	}

	void Project::SetBinFileName(std::string name)
	{
	}

	void Project::SaveProjectFile()
	{
		std::ofstream ofs(_projPath + "/" + _projName + ".swingproj", std::ios::binary | std::ios::out);

		rapidjson::PrettyWriter<std::ofstream> prettyWriter(ofs);

		_projJson.Accept(prettyWriter);
	}

	void Project::LoadProjectFile()
	{
		std::ifstream ofs(_projPath + "/" + _projName + ".swingproj", std::ios::binary | std::ios::in);

		if (!ofs.is_open())
		{
			std::cout << "File open Error, " << _projPath + "/" + _projName + ".swingproj" << std::endl;
			exit(1);
		}

		_projJson.ParseStream(ofs);
	}
}
