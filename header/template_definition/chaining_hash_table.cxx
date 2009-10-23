/*!
 * \file
 * Implements the ChainingHashtable templote.
 *
 * This file is not a compilation unit; it will fail to build if separately compiled.
 *
 * \author Andres Jaan Tack (tack@cs.wisc.edu)
 */
#include <algorithm>
#include <cstddef>
#include <functional>
using std::bind1st;


template <typename KeyType, typename DataType, size_t KeyRange>
void ChainingHashtable<KeyType, DataType, KeyRange>::put (const KeyType key, const DataType& value)
{
	size_t hash_index = hash(key);
	itsEntries[hash_index].map(key, value);
}


template <typename KeyType, typename DataType, size_t KeyRange>
DataType ChainingHashtable<KeyType, DataType, KeyRange>::get (const KeyType key) const
{
	size_t hash_index = hash(key);
	const typename Chain::KeyValuePair* const mapped_pair = itsEntries[hash_index].find(key);
	
	if (mapped_pair == NULL)
		throw typename KeyValueStore<KeyType, DataType>::ValueNotFound(key);
	else
		return mapped_pair->value();
}


template <typename KeyType, typename DataType, size_t KeyRange>
bool ChainingHashtable<KeyType, DataType, KeyRange>::hasValueFor (const KeyType key) const
{
	size_t hash_index = hash(key);
	return itsEntries[hash_index].hasMatchingEntry(key);
}


template <typename KeyType, typename DataType, size_t KeyRange>
void ChainingHashtable<KeyType, DataType, KeyRange>::unmap (const KeyType key)
{
	size_t hash_index = hash(key);
	itsEntries[hash_index].unmap(key);
}


template <typename KeyType, typename DataType, size_t KeyRange>
size_t ChainingHashtable<KeyType, DataType, KeyRange>::hash (const KeyType key)
{
	return key % KeyRange;
}


template <typename KeyType, typename DataType, size_t KeyRange>
const KeyValuePair<KeyType, DataType>* const
      ChainingHashtable<KeyType, DataType, KeyRange>::Chain::find (const KeyType key) const
{
	Link mapping = match(key);
	if (mapping != itsEntries.end())
		return &(*mapping);
	else
		return NULL;		
}


template <typename KeyType, typename DataType, size_t KeyRange>
bool ChainingHashtable<KeyType, DataType, KeyRange>::Chain::hasMatchingEntry(const KeyType key) const
{
	return match(key) != itsEntries.end();
}


template <typename KeyType, typename DataType, size_t KeyRange>
void ChainingHashtable<KeyType, DataType, KeyRange>::Chain::map (const KeyType key, const DataType& value)
{
	KeyValuePair newMapping(key, value);
	Link oldMapping = match(key);
	
	if (oldMapping != itsEntries.end())
		itsEntries.erase(oldMapping);
	itsEntries.push_front(newMapping);
}


template <typename KeyType, typename DataType, size_t KeyRange>
const typename ChainingHashtable<KeyType, DataType, KeyRange>::Chain::Link
      ChainingHashtable<KeyType, DataType, KeyRange>::Chain::match (const KeyType key) const
{
	using std::find_if;
	
	// find_if is not nominally const, but here we know our matcher treats values constantly.
	list<KeyValuePair>& entries = const_cast<list<KeyValuePair>&>(itsEntries);
	return find_if(entries.begin(), entries.end(), bind1st(typename KeyValuePair::match_by_key(), key));
}


template <typename KeyType, typename DataType, size_t KeyRange>
void ChainingHashtable<KeyType, DataType, KeyRange>::Chain::unmap (const KeyType key)
{
	itsEntries.remove_if(bind1st(typename KeyValuePair::match_by_key(), key));
}
