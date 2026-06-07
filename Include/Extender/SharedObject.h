#ifndef PLUGINLOADER_SHAREDOBJECT_H
#define PLUGINLOADER_SHAREDOBJECT_H

#include "ImportExport.h"

class CODEINJECTION_EXPORT SharedObject
{
public:
	SharedObject();
	SharedObject(const char *path);
	~SharedObject();
	
	bool load(const char *path);
	bool loaded() const;
	bool unload();
	
	void *getSymbol(const char *name) const;
	
	static const char *DefaultExtension;

private:
	void *handle;
};

#endif
