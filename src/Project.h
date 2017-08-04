#ifndef _SWING_PROJECT_H_
#define _SWING_PROJECT_H_
#include <string>
#include <list>
#include <experimental/filesystem>
#include "rapidjson/document.h"
#include "Source.h"

namespace swing
{
	struct Project
	{
		/// ProjectName
		std::string _projName;
		/// folder where project is.
		std::string _projPath;	
		/// executive file name
		std::string _binFileName;
		/// executive file output path
		std::string _binOutputPath;
		/// source location
		std::string _sourceFilePath;
		/// instance of source class list
		SourceList _sourceList;

		rapidjson::Document _projJson;
		Project() = delete;
		/// Generate new project.
		Project(std::string projName, std::string projFolderPath);
		/// Load project from 
		Project(std::string projFile);
		~Project();

		/// ProjectFile.
		bool isValid();
		void SetProjectName(std::string name);
		void SetProjectPath(std::string path);
		void SetBinFileName(std::string name);
		void SetBinOutputPath(std::string path);
		void SetSourceSavePath(std::string path);
		void AddSourceFile(std::string fullPath);
		void RemoveSourceFile(std::string name);
		void SaveProjectFile();
		void LoadProjectFile();

		/// Project Compile
		void CompileProject(int optLevel, std::string outputFormat);
		void LinkProject();
	};
}

#endif
