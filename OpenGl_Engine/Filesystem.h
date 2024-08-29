#pragma once
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <cstdlib>
#include <string>




class Filesystem
{
	public:
		static std::string get_Path(const std::string& path);

	private:
		typedef std::string (*Builder) (const std::string& path); // Function pointer

		static std::string const & getRoot(); // Get the root path #

		static Builder getPathBuilder(); // Get the path builder
		static std::string buildPath(const std::string& path); // Build the path
		static std::string binaryPath(const std::string& path); // Build the binary path 

};
#endif // !FILESYSTEM_H
