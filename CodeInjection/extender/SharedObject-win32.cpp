#include <Extender/SharedObject.h>
#include <Windows.h>

const char* SharedObject::DefaultExtension = ".dll";

SharedObject::SharedObject()
	: handle(NULL)
{
}

SharedObject::SharedObject(const char *path)
	: handle(NULL)
{
	load(path);
}

SharedObject::SharedObject(const wchar_t* path)
	: handle(NULL)
{
	loadWide(path);
}

SharedObject::SharedObject(void* libHandle)
{
	handle = libHandle;
}

SharedObject::~SharedObject()
{
	unload();
}

bool SharedObject::load(const char *path)
{
	unload();
	handle = LoadLibraryA(path);
	return (handle != NULL);
}

bool SharedObject::loadWide(const wchar_t *path)
{
	unload();
	handle = LoadLibraryW(path);
	return (handle != NULL);
}

void* SharedObject::swapHandle(void* libHandle)
{
	void* oldHandle = handle;
	handle = libHandle;
	return oldHandle;
}

bool SharedObject::loaded() const
{
	return (handle != NULL);
}

bool SharedObject::unload()
{
	if (handle && FreeLibrary(static_cast<HMODULE>(handle)) != 0)
	{
		handle = NULL;
		return true;
	}
	return false;
}

void* SharedObject::leak()
{
	void* libHandle = handle;
	handle = NULL;
	return libHandle;
}

void *SharedObject::getSymbol(const char *name) const
{
	if (handle)
		return GetProcAddress(static_cast<HMODULE>(handle), name);
	return NULL;
}
