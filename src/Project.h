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
		std::string _projPath;		/// folder where project is in.
		std::string _binFileName;
		std::list<std::string> _sources;

		rapidjson::Document _projJson;

	public:
		Project() = delete;
		Project(std::string projName, std::string projFolderPath); /// Generate new project.
		Project(std::string projFile);		/// Load project from 
		~Project();

		void SetProjectName(std::string name);
		void SetProjectPath(std::string path);
		void SetBinFileName(std::string name);


	};
}

#endif
