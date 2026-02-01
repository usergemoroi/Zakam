#pragma once

#include "il2cpp/il2cpp.h"

template < typename TKey , typename TValue >
struct Dictionary : public il2cpp_ray :: dictionary < TKey , TValue > {
	typename il2cpp_ray :: dictionary < TKey , TValue > :: entry * begin() const {
		return this -> entries -> m_items;
	}
	typename il2cpp_ray :: dictionary < TKey , TValue > :: entry * end() const {
		return this -> entries -> m_items + this -> count;
	}
};
