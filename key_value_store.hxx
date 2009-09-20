/*!
 * \file
 * Describes the interface to the hash table which we are implementing.
 *
 * \author Andres Jaan Tack (tack@cs.wisc.edu)
 */
#ifndef KEY_VALUE_STORE_HXX_E9THO8M5
#define KEY_VALUE_STORE_HXX_E9THO8M5

/*!
 * \class KeyValueStore
 *
 * A storage container where each unique key is mapped to zero or one independent
 * value. The interface suggests, without reservation, a hash table implementation,
 * but the implementation may be otherwise.
 * 
 * \author Andres Jaan Tack (tack@cs.wisc.edu)
 */
template <KeyType, DataType>
class KeyValueStore : public std::tr1::unordered_map
{
public:
	
	/*!
	 * Build an empty key-value store.
	 */
	KeyValueStore ();
	
	/*!
	 * Destroy the keystore and all values contained therein.
	 */
	virtual ~KeyValueStore ();
	
	/*!
	 * Assign a value at the given key.
	 * \param key may be used to retrieve the stored value subsequently.
	 * \value will replace any existing value stored at key.
	 */
	virtual void put (const KeyType& key, const DataType& value);
	
	/*
	 * Retrieve the value stored at key.
	 * \exception InvalidEntry raised when 
	 */
	virtual DataType get (const KeyType& key);
	
	/*
	 * Determines whether a value exists at the given key.
	 * \param key identifies a possible entry in the store.
	 * \return true if key maps to a value, false if no value is stored at key.
	 */
	virtual bool hasEntry (const KeyType& key);

	/*
	 * Deletes any entry at key. It is safe to delete for a key with no value.
	 * \param key identifies the value to be deleted.
	 */
	virtual void delete (const KeyType& key);
	
	/*
	 * \class ValueNotFound
	 * Defines an exceptional case for KeyValueStore::get, in which the key given has
	 * no corresponding value.
	 */
	class ValueNotFound : public std::exception
	{
	public:
		/*!
		 * Identifies a ValueNotFound error when retrieving the given key.
		 * \param key the key at which no value was found when it was expected.
		 */
		inline ValueNotFound (const KeyType& key)
		: itsKey(key)
			{	}
			
		inline virtual ~ValueNotFound () throw()
			{	}
		
		/*!
		 * Identifies the key whose lookup engendered the exception.
		 * \return a copy of the key used.
		 */
		inline KeyType key () throw()
			{ return itsKey; }

	private:
		const KeyType itsKey;  /*!< The key whose lookup caused the exception. */
	};

private:
	/* Data. */
};

#endif /* end of include guard: KEY_VALUE_STORE_HXX_E9THO8M5 */
