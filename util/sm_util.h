#ifndef SM_UTIL_H
#define SM_UTIL_H


#include <QObject>
#include <qqmlengine.h>

namespace sm {


    template <typename Container, typename Data>
    constexpr void append(Container& container, const Data& data) {
        container.append(data);
    }

    template <typename Container, typename DataPtr>
    constexpr void append(Container& container, DataPtr* data) {
        container.append(data);
    }

    template <typename Container>
    constexpr auto size(const Container& container) {
        return container.size();
    }


    template <class Object>
    inline Object * single_tone(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr) {
        return qobject_cast<Object*>(Object::qmlSingleton(engine, scriptEngine));
    }


}

#endif // SM_UTIL_H
