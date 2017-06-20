#ifndef _SWING_PROJECT_H_
#define _SWING_PROJECT_H_
#include <string>
#include <list>
#include <experimental/filesystem>
#include "rapidjson/document.h"

namespace swing
{
	struct Project
	{
		std::string _projName;		/// ProjectName
		std::string _projPath;		/// folder where project is.

		std::string _binFileName;	/// executive file name
		std::string _binOutputPath;

		std::string _sourceFilePath;
		std::list<std::string> _sourceList;		/// source Paths

		rapidjson::Document _projJson;

		Project() = delete;
		/// Generate new project.
		Project(std::string projName, std::string projFolderPath);
		/// Load project from 
		Project(std::string projFile);
		~Project();

		bool isValid();

		void SetProjectName(std::string name);
		void SetProjectPath(std::string path);
		
		void SetBinFileName(std::string name);
		void SetBinOutputPath(std::string path);

		void SetSourcePath(std::string path);
		void AddSourceFile(std::string name);
		void RemoveSourceFile(std::string name);

		void SaveProjectFile();
		void LoadProjectFile();
	};
}

#endif
