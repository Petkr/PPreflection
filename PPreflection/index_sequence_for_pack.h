#pragma once
#include <type_traits>
#include "type_pack.h"
#include "apply_pack.h"
#include "value_t.h"

template <typename... T>
struct index_sequence_for_pack : value_t<std::index_sequence_for<T...>{}> {};
