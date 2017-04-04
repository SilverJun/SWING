#include "Project.h"

#include <fstream>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/allocators.h"

namespace swing
{
	Project::Project(std::string projName, std::string projFolderPath) : _projName(projName), _projPath(projFolderPath)
	{
		_projJson.Clear();

		rapidjson::Value Root(rapidjson::kObjectType);

		rapidjson::Document::AllocatorType& allocator = _projJson.GetAllocator();

		Root.AddMember("ProjectName", rapidjson::Value(_projName.c_str(), allocator), allocator);
		Root.AddMember("ProjectPath", rapidjson::Value(_projPath.c_str(), allocator), allocator);

		/// add base main swing file automatically.

		std::fstream baseFile(_projPath + "/main.swing", std::ios::out);

		if (baseFile.is_open())
		{
			baseFile << "output(\"Hello Swing Language!\")";
			_sourcesPath.push_back(_projPath + "/main.swing");

			rapidjson::Value sourceList(rapidjson::kArrayType);

			sourceList.PushBack(rapidjson::Value(_sourcesPath.back().c_str(), allocator), allocator);

			/*for (auto iter = _sourcesPath.begin(); iter != _sourcesPath.end(); ++iter)
			{
				sourceList.PushBack(rapidjson::Value((*iter).c_str(), allocator), allocator);
			}*/

			Root.AddMember("SourcePath", sourceList, allocator);
		}

		_projJson.CopyFrom(Root, allocator);

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
