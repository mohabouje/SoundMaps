#ifndef SM_UTIL_H
#define SM_UTIL_H


#include <QObject>
#include <qqmlengine.h>
#include <type_traits>
#include <cmath>

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

    template <typename T, typename R,
              typename = std::enable_if<std::is_arithmetic<T>::value && std::is_arithmetic<R>::value>>
    constexpr bool float_compare(const T rhs, const R lhs) {
        return std::abs(lhs - rhs) < std::numeric_limits<double>::epsilon();
    }

}

#endif // SM_UTIL_H
