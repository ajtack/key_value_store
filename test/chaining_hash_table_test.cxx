/*!
 * \file
 * Basic functionality tests for the ChainingHashtable class template.
 *
 * \author Andres Jaan Tack (tack@cs.wisc.edu)
 */
#include <UnitTest++/UnitTest++.h>
#include <chaining_hash_table.hxx>

typedef ChainingHashtable<unsigned int, unsigned int> UnsignedIntStore;

SUITE(ChainingHashtable)
{
	struct PopulatedStore
	{
		PopulatedStore()
		{
			theStore.put(10, 20);
			theStore.put(30, 40);
		}
		
		UnsignedIntStore theStore;
	};
	
	TEST_FIXTURE(PopulatedStore, SeesThatMappedValuesExist)
	{
		CHECK(theStore.hasValueFor(10));
		CHECK(theStore.hasValueFor(30));
	}
	
	TEST_FIXTURE(PopulatedStore, AllowsRetrievalOfStoredValues)
	{
		CHECK(theStore.get(10) == 20);
		CHECK(theStore.get(30) == 40);
	}
	
	TEST_FIXTURE(PopulatedStore, ThrowsExceptionWhenGettingNonexistentKey)
	{
		CHECK_THROW(theStore.get(50), UnsignedIntStore::ValueNotFound);
	}
	
	TEST_FIXTURE(PopulatedStore, DoesNotSeeUnmappedKeys)
	{
		theStore.unmap(10);
		CHECK(theStore.hasValueFor(10) == false);
	}
	
	TEST_FIXTURE(PopulatedStore, ThrowsExceptionWhenGettingDeletedKey)
	{
		theStore.unmap(10);
		CHECK_THROW(theStore.get(10), UnsignedIntStore::ValueNotFound);
	}
}
