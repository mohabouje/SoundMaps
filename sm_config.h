#ifndef CONFIG_H
#define CONFIG_H

#include "util/singletone.h"
#include "util/sm_util.h"

#define PACKAGE_NAME "com.mohabouje.soundmaps"
#define PACKAGE_VERSION_MAJOR   1
#define PACKAGE_VERSION_MINOR   0

#define ENVIRONEMENT_FORMAT   ".envi"
#define ENVIRONEMENT_FILENAME "environement" ENVIRONEMENT_FORMAT


#define SM_PIMPL_PTR(Class) \
    Class##Private* d_ptr;

#define SM_DECL_SINGLETON(Class)  static Class* createInstance() { return new Class(); }
#define SM_STATIC_SINGLETON(Class) Singleton<Class>::instance(Class::createInstance)


#endif // CONFIG_H
