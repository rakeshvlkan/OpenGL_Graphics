#ifndef FILECLASS_H
#define FILECLASS_H

#include <string>
#include <cstdlib>

typedef std::string(*Builder) (const std::string& path);
class FileClass
{

public:
	FileClass();
	~FileClass();
	static std::string getPath(const std::string& path);
	static std::string const & getRoot();
	static Builder getPathBuilder();
	static std::string getPathRelativeRoot(const std::string& path);
	static std::string getPathRelativeBinary(const std::string& path);
};

#endif;

