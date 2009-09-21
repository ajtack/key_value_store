/*!
 * \file
 * Implements the KeyValueStore templote.
 *
 * This file is not a compilation unit, though it will not fail to build if separately compiled.
 *
 * \author Andres Jaan Tack (tack@cs.wisc.edu)
 */
#include <cstdlib>


template <typename KeyType, typename DataType, std::size_t KeyRange>
KeyValueStore<KeyType, DataType, KeyRange>::KeyValueStore ()
{	}


template <typename KeyType, typename DataType, std::size_t KeyRange>
KeyValueStore<KeyType, DataType, KeyRange>::~KeyValueStore ()
{	}


template <typename KeyType, typename DataType, std::size_t KeyRange>
void KeyValueStore<KeyType, DataType, KeyRange>::put (const KeyType key, const DataType& value)
{	}


template <typename KeyType, typename DataType, std::size_t KeyRange>
DataType KeyValueStore<KeyType, DataType, KeyRange>::get (const KeyType key)
{	}


template <typename KeyType, typename DataType, std::size_t KeyRange>
bool KeyValueStore<KeyType, DataType, KeyRange>::hasValueFor (const KeyType key)
{	}


template <typename KeyType, typename DataType, std::size_t KeyRange>
void KeyValueStore<KeyType, DataType, KeyRange>::unmap (const KeyType key)
{	}
