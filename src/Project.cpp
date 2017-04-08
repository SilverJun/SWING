#include "Project.h"

#include <fstream>
#include <iostream>
#include <algorithm>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/allocators.h"
#include "rapidjson/stringbuffer.h"

namespace swing
{
	Project::Project(std::string projName, std::string projFolderPath) : _projName(projName), _projPath(projFolderPath), _binFileName(projName), _binOutputPath(projFolderPath), _sourceFilePath(projFolderPath)
	{
		rapidjson::Value Root(rapidjson::kObjectType);

		rapidjson::Document::AllocatorType& allocator = _projJson.GetAllocator();

		/// add Basic Project Properties.
		Root.AddMember("ProjectName", rapidjson::Value(_projName.c_str(), allocator), allocator);
		Root.AddMember("ProjectPath", rapidjson::Value(_projPath.c_str(), allocator), allocator);
		Root.AddMember("BinaryFileName", rapidjson::Value(_binFileName.c_str(), allocator), allocator);
		Root.AddMember("BinaryOutputPath", rapidjson::Value(_projPath.c_str(), allocator), allocator);
		Root.AddMember("SourceFilePath", rapidjson::Value(_projPath.c_str(), allocator), allocator);

		/// add base main swing file automatically.

		std::fstream baseFile(_projPath + "/main.swing", std::ios::out);

		if (baseFile.is_open())
		{
			baseFile << "output(\"Hello Swing Language!\")";
			_sourceList.push_back(_projPath + "/main.swing");

			rapidjson::Value sourceList(rapidjson::kArrayType);

			sourceList.PushBack(rapidjson::Value(_sourceList.back().c_str(), allocator), allocator);

			/*for (auto iter = _sourcesPath.begin(); iter != _sourcesPath.end(); ++iter)
			{
				sourceList.PushBack(rapidjson::Value((*iter).c_str(), allocator), allocator);
			}*/

			Root.AddMember("SourceList", sourceList, allocator);
		}

		_projJson.CopyFrom(Root, allocator);

		SaveProjectFile();
	}

	Project::Project(std::string projFile)
	{
		std::ifstream projIfs(projFile);

		if (!projIfs.is_open())
		{
			std::cout << "File open Error, " << projFile << std::endl;
			system("pause");
			exit(1);
		}

		_projJson.Parse(std::string(std::istreambuf_iterator<char>(projIfs),
			std::istreambuf_iterator<char>()).c_str());

		auto Root = _projJson.GetObject();

		_projName = Root["ProjectName"].GetString();
		_projPath = Root["ProjectPath"].GetString();
		_binFileName = Root["BinaryFileName"].GetString();

		if (!Root["SourceList"].Empty() && Root["SourceList"].IsArray()) { return; }

		auto sourceList = Root["SourceList"].GetArray();

		for (rapidjson::Value::ValueIterator iter = sourceList.Begin(); iter != sourceList.End(); ++iter)
		{
			_sourceList.push_back((*iter).GetString());
		}
	}

	Project::~Project()
	{
	}

	void Project::SetProjectName(std::string name)
	{
		_projName = name;
		auto Root = _projJson.GetObject();

		if (Root.HasMember("ProjectName"))
		{
			Root["ProjectName"] = rapidjson::Value(_projName.c_str(), _projJson.GetAllocator());
		}
	}

	void Project::SetProjectPath(std::string path)
	{
		_projPath = path;
		auto Root = _projJson.GetObject();

		if (Root.HasMember("ProjectPath"))
		{
			Root["ProjectPath"] = rapidjson::Value(_projPath.c_str(), _projJson.GetAllocator());
		}
	}

	void Project::SetBinFileName(std::string name)
	{
		_binFileName = name;
		auto Root = _projJson.GetObject();

		if (Root.HasMember("BinaryFileName"))
		{
			Root["BinaryFileName"] = rapidjson::Value(_binFileName.c_str(), _projJson.GetAllocator());
		}
	}

	void Project::SetBinOutputPath(std::string path)
	{
		_binOutputPath = path;
		auto Root = _projJson.GetObject();

		if (Root.HasMember("BinaryOutputPath"))
		{
			Root["BinaryOutputPath"] = rapidjson::Value(_binOutputPath.c_str(), _projJson.GetAllocator());
		}
	}

	void Project::SetSourcePath(std::string path)
	{
		_sourceFilePath = path;
		auto Root = _projJson.GetObject();

		if (Root.HasMember("SourceFilePath"))
		{
			Root["SourceFilePath"] = rapidjson::Value(_sourceFilePath.c_str(), _projJson.GetAllocator());
		}
	}

	void Project::AddSourceFile(std::string name)
	{
		if (find(_sourceList.begin(), _sourceList.end(), name) == _sourceList.end())
		{
			_sourceList.push_back(name);
		}
	}

	void Project::RemoveSourceFile(std::string name)
	{
		_sourceList.remove(name);
	}

	void Project::SaveProjectFile()
	{
		std::ofstream ofs(_projPath + "/" + _projName + ".swingproj");

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> prettyWriter(buffer);
		_projJson.Accept(prettyWriter);

		ofs << buffer.GetString();
	}

	void Project::LoadProjectFile()
	{
		std::ifstream ifs(_projPath + "/" + _projName + ".swingproj");
		
		if (!ifs.is_open())
		{
			std::cout << "File open Error, " << _projPath + "/" + _projName + ".swingproj" << std::endl;
			system("pause");
			exit(1);
		}

		_projJson.Parse(std::string(std::istreambuf_iterator<char>(ifs),
			std::istreambuf_iterator<char>()).c_str());
	}
}
