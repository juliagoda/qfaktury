#include <memory>

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T, typename Deleter = std::default_delete<T>>
using UPtr = std::unique_ptr<T, Deleter>;

template <typename T>
using WPtr = std::weak_ptr<T>;
