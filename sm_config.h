#ifndef CONFIG_H
#define CONFIG_H

#include "util/singletone.h"
#include "util/sm_util.h"

#define SM_PACKAGE_NAME "com.mohabouje.soundmaps"
#define SM_PACKAGE_VERSION_MAJOR   1
#define SM_PACKAGE_VERSION_MINOR   0

#define SM_ENV_FORMAT   ".envi"
#define SM_ENV_FILE(X) X ## SM_ENV_FORMAT
#define SM_ENV_DEFAULT_FILENAME "environement" SM_ENV_FORMAT


#define SM_DECL_PIMPL(Class) \
    Class##Private* d_ptr;

#define SM_DECL_SINGLETON(Class)  static Class* createInstance() { return new Class(); }
#define SM_STATIC_SINGLETON(Class) Singleton<Class>::instance(Class::createInstance)




#endif // CONFIG_H
