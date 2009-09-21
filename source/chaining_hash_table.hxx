/*!
 * \file
 * Implements a chaining hash table per the interface of KeyValueStore.
 *
 * \author Andres Jaan Tack (tack@cs.wisc.edu)
 */
#ifndef CHAINING_HASH_TABLE_HXX_VWNU2QA1
#define CHAINING_HASH_TABLE_HXX_VWNU2QA1

#include "key_value_store.hxx"
#include "utility/key_value_pair.hxx"
#include <cstddef>
using std::size_t;
#include <list>
using std::list;

template <typename KeyType, typename DataType, std::size_t KeyRange = 1024>
class ChainingHashtable : public KeyValueStore<KeyType, DataType>
{
public:
	/*!
	 * Instantiates the full range of keys as a hash table with KeyRange entries.
	 * Each of these entries is a chain (essentially a linked list) and is
	 * initialized at length zero.
	 */
	ChainingHashtable ()
		{	}
	
	/*!
	 * Assign a value at the hash of the given key. Any update will cause a new
	 * memory allocation of length (sizeof(key) + sizeof(value)).
	 *
	 * The key range of the table are defined as a template parameter. If the hashes
	 * of two independent keys conflict, they will be chained with the most recent
	 * insertion at the top of the chain.
	 *
	 * \param key may be used to retrieve the stored value subsequently.
	 * \value will replace any existing value stored at key.
	 */
	void put (const KeyType key, const DataType& value);
	
	/*!
	 * Retrieve the value stored at key by iterating through the hash chain mapped
	 * at hash(key).
	 *
	 * \exception InvalidEntry raised when 
	 */
	DataType get (const KeyType key) const;
	
	/*!
	 * Determines whether a key/value pair exists with the given key by iterating
	 * through the hash chain.
	 *
	 * \param key identifies a possible entry in the store.
	 * \return true if key maps to a value, false if no value is stored at key.
	 */
	bool hasValueFor (const KeyType key) const;

	/*!
	 * Deletes any entry at key, removing it from the hash chain. It is safe to
	 * delete for a key with no value.
	 *
	 * \param key identifies the value to be deleted.
	 */
	void unmap (const KeyType key);
	
	/*!
	 * Exposes the behavior of the underlying hash function.
	 *
	 * \param key will be put through the hash function of this table.
	 * \return the hash entry for the given key.
	 */
	static size_t hash (const KeyType key);

private:
	/*!
	 * A chain of values mapped at a particular key hash. Each entry in the chain
	 * _must_ maintain the key with which it was stored, because this allows
	 * entries which collide in the full table to be distinguished within the chain.
	 */
	class Chain
	{
	public:
		typedef KeyValuePair<KeyType, DataType> KeyValuePair;
		
		/*!
		 * Maps a key/value pair. If the key is already mapped in the hash chain,
		 * then this method creates a new chain link with the new key and value
		 * and atomically replaces the new link with the old.
		 *
		 * \param key is the key to be mapped within the chain, compared with all
		 *   other keys within the chain.
		 * \param value will be associated with key after the operation.
		 */
		void map (const KeyType key, const DataType& value);
		
		/*!
		 * Searches through the hash chain to locate the given key.
		 * \key is the key being sought.
		 * \return a pointer to the link which is found as a result of the search.
		 */
		const KeyValuePair* const find(const KeyType key) const;
		
		/*!
		 * An object for comparison which identifies a nonexistent result of search.
		 */
		static const KeyValuePair* const aNonexistentEntry;
		
		/*!
		 * Searches the chain for a key/value pair with a matching key.
		 *
		 * \param key is the key being sought out.
		 * \return true if key is found in a key/value pair in the chain.
		 */
		void hasMatchingEntry (const KeyType key) const
			{	return find(key) != NULL; }

	protected:
		list<KeyValuePair> itsEntries;
	};
	
	/*!
	 * The hash table underlying the key store. Each entry in the array is a chain of
	 * hash entries; the key range is fixed.
	 */
	Chain itsEntries[KeyRange];
};

#include "chaining_hash_table.cxx"

#endif /* end of include guard: CHAINING_HASH_TABLE_HXX_VWNU2QA1 */
