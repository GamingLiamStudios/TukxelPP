#pragma once
#ifndef DllHandleH
#define DllHandleH
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#include <tchar.h>
#define DLL HMODULE
#define MODULE
#define ERR DWORD
#else
#include <dirent.h>
#include <dlfcn.h>
#define DLL void*
#define NULL 0
#define ERR char*
#endif
#include <iostream>
#include <cstddef>
#include <vector>
#include <filesystem>

class DllHandle {
public:
	static DLL loadDll(const char* path, ERR &err) {
		DLL dll;
		err = NULL;
#ifdef MODULE
		dll = LoadLibraryA(path);
		if (dll == NULL) err = GetLastError();
#else
		dll = dlopen(path, RTLD_LOCAL | RTLD_LAZY);
		if (dll == NULL) err = dlerror();
#endif
		return dll;
	}

	static std::vector<DLL> loadDir(const char* dir, ERR &err) {
		std::vector<DLL> dlls = std::vector<DLL>();
		DLL dll;
		const std::filesystem::path pathToShow{ dir };
		for (const auto& entry : std::filesystem::directory_iterator(pathToShow)) {
			const auto path = entry.path().string();
			if (entry.is_directory())
				std::cout << "Found Directory" << entry.path().filename().string() << " but will not search for dlls"
				<< std::endl; //Generic Error Message
			else if (entry.is_regular_file()) {
				if (strcmp(entry.path().extension().string().c_str(), ".dll") == 0) {
					dll = loadDll(path.c_str(), err);
					if (err != NULL)
						break;
					dlls.push_back(dll);
				}
			} else
				std::cout << "Uhhh, What is this? Why is there a non-regular file?" << std::endl; //Da Faq is this?
		}
		dll = NULL;
		dlls.shrink_to_fit();
		return dlls;
	}

	static void* getFunc(DLL dll, const char* funcName) {
#ifdef MODULE
		return (void*)GetProcAddress(dll, funcName);
#else
		return dlsym(dll, funcName);
#endif
	}

	static ERR freeDll(DLL &dll) {
#ifdef MODULE
		if (!FreeLibrary(dll))
			return GetLastError();
#else
		if (dlclose(dll) != NULL)
			return dlerror();
#endif
		dll = NULL;
		return NULL;
	}

	static ERR freeDlls(std::vector<DLL> &dlls) {
		for (auto dll : dlls)
#ifdef MODULE
			if(!FreeLibrary(dll))
				return GetLastError();
#else
			if(dlclose(dll) != NULL)
				return dlerror();
#endif
		dlls.clear();
		return NULL;
	}
};

#endif