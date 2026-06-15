#ifndef PLUGINLOADER_SHAREDOBJECT_H
#define PLUGINLOADER_SHAREDOBJECT_H

#include "ImportExport.h"

class CODEINJECTION_EXPORT SharedObject
{
public:
	SharedObject();
	SharedObject(const char* path);
	SharedObject(const wchar_t* path);
	SharedObject(void* libHandle);
	~SharedObject();
	
	bool load(const char* path);
	bool loadWide(const wchar_t* path);
	void* swapHandle(void* libHandle);
	bool loaded() const;
	bool unload();
	void* leak();
	
	void* getSymbol(const char* name) const;
	
	static const char* DefaultExtension;

private:
	void* handle;
};

#endif
