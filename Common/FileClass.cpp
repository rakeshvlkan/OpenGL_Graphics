#include "FileClass.h"


const char * logl_root = "../";
FileClass::FileClass()
{
}


FileClass::~FileClass()
{
}

std::string FileClass::getPath(const std::string & path)
{
	static std::string(*pathBuilder)(std::string const &) = getPathBuilder();
	return (*pathBuilder)(path);
}

std::string const & FileClass::getRoot()
{
	static char const * envRoot = getenv("LOGL_ROOT_PATH");
	static char const * givenRoot = (envRoot != nullptr ? envRoot : logl_root);
	static std::string root = (givenRoot != nullptr ? givenRoot : "");
	return root;
}

Builder FileClass::getPathBuilder()
{
	if (getRoot() != "")
		return &FileClass::getPathRelativeRoot;
	else
		return &FileClass::getPathRelativeBinary;
}

std::string FileClass::getPathRelativeRoot(const std::string & path)
{
	return getRoot() + std::string("/") + path;
}

std::string FileClass::getPathRelativeBinary(const std::string & path)
{
	return "../../../" + path;
}
