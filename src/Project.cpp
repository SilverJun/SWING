#include "Project.h"

#include <fstream>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/allocators.h"
#include "rapidjson/stringbuffer.h"
#include "Lexer.h"
#include "Error.h"

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
			baseFile.close();

			_sourceList.push_back(new Source(_projPath + "/main.swing"));

			rapidjson::Value sourceList(rapidjson::kArrayType);

			sourceList.PushBack(rapidjson::Value(_sourceList.back()->_fullPath.c_str(), allocator), allocator);

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
		_sourceFilePath = Root["SourceFilePath"].GetString();

		if (Root["SourceList"].Empty() && !Root["SourceList"].IsArray()) { return; }

		auto sourceList = Root["SourceList"].GetArray();

		for (rapidjson::Value::ValueIterator iter = sourceList.Begin(); iter != sourceList.End(); ++iter)
		{
			_sourceList.push_back(new Source((*iter).GetString()));
		}
	}

	Project::~Project()
	{
	}

	bool Project::isValid()
	{
		///TODO : valid구현.
		return true;
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

	void Project::SetSourceSavePath(std::string path)
	{
		_sourceFilePath = path;
		auto Root = _projJson.GetObject();

		if (Root.HasMember("SourceFilePath"))
		{
			Root["SourceFilePath"] = rapidjson::Value(_sourceFilePath.c_str(), _projJson.GetAllocator());
		}
	}

	void Project::AddSourceFile(std::string fullPath)
	{
		auto Root = _projJson.GetObject();
		if (std::find_if(_sourceList.begin(), _sourceList.end(), [&fullPath](Source* src){ return src->_fullPath == fullPath; }) == _sourceList.end())
		{
			_sourceList.push_back(new Source(fullPath));
			Root["SourceList"].GetArray().PushBack(rapidjson::Value(fullPath.c_str(), _projJson.GetAllocator()), _projJson.GetAllocator());
		}
	}

	void Project::RemoveSourceFile(std::string name)
	{
		std::remove_if(_sourceList.begin(), _sourceList.end(), [name](Source* src){ return src->_name == name; });
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

	void Project::CompileProject(int optLevel, std::string outputFormat)
	{
		/// Generate LLVM IR.
		Lexer lex;
		try
		{
			for (auto source : _sourceList)
				lex.LexSource(source);
			for (auto source : _sourceList)
				source->Parse();
			for (auto source : _sourceList)
				source->CodeGen();
		}
		catch(LexicalError& e)
		{
			std::cout << e.what() << std::endl;
			exit(-1);
		}
		catch (ParsingError& e)
		{
			std::cout << e.what() << std::endl;
			for (;;);
			exit(-1);
		}
		catch (...)
		{
			std::cout << "Undefined Error." << std::endl;
			exit(-1);
		}

		if (outputFormat == ".ll")
			return;

		/// LLVM IR to Bitcode.
		int retVal = 0;
		std::string cmd;
		for (auto source : _sourceList)
		{
			cmd = "llvm-as";
			cmd += ' ';
			cmd += "-o=";
			cmd += _binOutputPath;
			cmd += "/";
			cmd += source->_name + ".bc";
			cmd += ' ';
			cmd += source->_name + ".ll";
			retVal = system(cmd.c_str());
			if (retVal != 0)
			{
				std::cout << "SWING Compile Failed, llvm-as return " << retVal << std::endl;
				exit(-1);
			}
		}

		if (outputFormat == ".bc")
			return;

		/// Do llvm opt each bitcode file
		///TODO : LLVM Opt Implement.

		/// Link all source file to one project source
		cmd = "llvm-link";
		cmd += ' ';
		cmd += "-o=";
		cmd += _binOutputPath;
		cmd += "/";
		cmd += _binFileName;
		cmd += ".bc";
		cmd += ' ';
		for (auto source : _sourceList)
		{
			cmd += _binOutputPath;
			cmd += source->_name;
			cmd += ".bc";
			cmd += ' ';
		}
		system(cmd.c_str());

		/// project bitcode file to object file.
		cmd = "llc -filetype=obj";
		cmd += ' ';
		cmd += "-o=";
		cmd += _binOutputPath;
		cmd += "/";
		cmd += _binFileName;
		cmd += ".o";
		cmd += ' ';
		cmd += _binOutputPath;
		cmd += "/";
		cmd += _binFileName;
		cmd += ".bc";
		
		system(cmd.c_str());

		std::cout << "SWING Compile Successfully." << std::endl;
	}

	void Project::LinkProject()
	{
		/// Link libswing
		std::string cmd;
		cmd = "clang-cl";
		cmd += ' ';
		cmd += "-o=" + _binOutputPath + "/" + _binFileName;
#ifdef _WINDOWS
		cmd += ".exe";
#else
		cmd += ".out";
#endif
		cmd += ' ';
		cmd += "libswing.lib";
		cmd += ' ';
		cmd += _binOutputPath + "/" + _binFileName;
		cmd += ".o";

		int retVal = system(cmd.c_str());
		if (retVal == 0)
			std::cout << "SWING Link Successfully." << std::endl;
		else 
			std::cout << "SWING Link Failed, clang-cl return " << retVal << std::endl;
	}
}
