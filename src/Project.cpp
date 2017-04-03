#include "Project.h"

#include <fstream>
#include <iostream>

#include "rapidjson/istreamwrapper.h"

namespace swing
{
	Project::Project(std::string projName, std::string projFolderPath)
	{
	}

	Project::Project(std::string projFile)
	{
		std::ifstream projIfs(projFile);

		_projJson.ParseStream(projIfs);
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
}
