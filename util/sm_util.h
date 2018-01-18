#ifndef SM_UTIL_H
#define SM_UTIL_H


#include <QObject>
#include <qqmlengine.h>
#include <type_traits>

namespace sm {

    template <typename Holder, typename Element>
    constexpr void append(Holder& container, const Element& data) {
        container.append(data);
    }

    template <class Holder, class ...Ts>
    constexpr void append(Holder* container, Ts... args) {
        container->append(args...);
    }

    template <typename Container>
    constexpr auto size(const Container& container) {
        return container.size();
    }

    template <class Object, typename = std::enable_if<std::is_base_of<Object, QObject>::value>>
    inline Object * single_tone(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr) {
        return qobject_cast<Object*>(Object::qmlSingleton(engine, scriptEngine));
    }

}

#endif // SM_UTIL_H
