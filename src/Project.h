#ifndef _SWING_PROJECT_H_
#define _SWING_PROJECT_H_
#include <string>
#include <list>
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"

namespace swing
{
	class Project
	{
		std::string _projName;		/// ProjectName
		std::string _projPath;		/// folder where project is.
		std::string _binFileName;	/// executive file name
		std::list<std::string> _sourcesPath;		/// source Paths

		rapidjson::Document _projJson;

	public:
		Project() = delete;
		Project(std::string projName, std::string projFolderPath); /// Generate new project.
		Project(std::string projFile);		/// Load project from 
		~Project();

		void SetProjectName(std::string name);
		void SetProjectPath(std::string path);
		void SetBinFileName(std::string name);

		void SaveProjectFile();
		void LoadProjectFile();
	};
}

#endif
