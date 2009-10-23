/*!
 * \file
 * Defines a key/value pair and some helpful methods for exploring them.
 */
#include <functional>
using std::binary_function;
#include <utility>
using std::pair;

/*!
 * A key/value pair of arbitrary types.
 */
template <typename KeyType, typename DataType>
class KeyValuePair : public pair<KeyType, DataType>
{
public:
	/*!
	 * Assigns the pair as expected.
	 * \param key is remembered as key().
	 * \param value is remembered as value().
	 */
	inline KeyValuePair (const KeyType key, const DataType& value)
	: pair<KeyType, DataType>(key, value)
		{	}
	
	/*!
	 * Retrieves the value mapped at this key.
	 * \return a copy of the value.
	 */
	inline DataType value()
		{ return this->second; }
	
	/*!
	 * Retrieves the value mapped at this key.
	 * \return an immutable copy of the value.
	 */
	inline const DataType& value() const
		{ return this->second;	}
	
	/*!
	 * The fully-qualified key at this mapping.
	 * \return the key mapping this entry.
	 */
	inline const KeyType key() const
		{ return this->first;	}
	
	/*!
	 * A unary function object which identifies key/value pairs with matching keys.
	 *
	 * This could be used as a parameter to stl algorithms as below:
	 * \code
	 *  find_if(list.begin(), list.end(), std::bind1st(typename KeyValuePair::match_by_key(), key))
	 * \endcode
	 */
	struct match_by_key : binary_function<KeyType, KeyValuePair, bool>
	{
		/*!
		 * Compares the keys of two key/value pairs.
		 *
		 * \param left is the left side of the comparison.
		 * \param right is the right side of the comparison.
		 * \return true if the keys of left and right are equal, false otherwise.
		 */
		inline bool operator() (KeyType key, KeyValuePair pair) const
			{	return pair.key() == key;	}
	};
};