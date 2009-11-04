/*!
 * \file
 * A program which sets up a Key/Value Store and evaluates performance over different
 * get/put operation ratios. The given options support mapping of the key/value store
 * over any file, whether it be stored in a RAM Disk (or a related filesystem designed
 * to simulate increased latency of PCM) or a traditional backstorage. The suggested
 * purpose of this workload analysis, then, is to evaluate the effects of different
 * key/value store implementations and hardware backstores on startup time, average
 * query time, and the differences caused by GET versus PUT requests.
 *
 * \author Andres Jaan Tack (tack@cs.wisc.edu)
 */
#include "experiment_interval.hxx"
#include <boost/timer.hpp>
using boost::timer;
#include <iostream>


int main (int argc, char const *argv[])
{
	// Determine the ratio of PUTs to GETs
	const unsigned int PutRequestProbability = 0.3;
	const unsigned int GetRequestProbability = 1.0 - PutRequestProbability;
	
	// Determine the size of the experiment and the number of intervals into
	// which it is divided.
	const unsigned int TotalRequestsInExperiment = 10;
	const unsigned int IntervalsInExperiment = 10;
	
	// Delete the file containing the hash table, if prompted by the "clean" option.
	
	// Map the file that contains the hash table.
		// Map a _new_ hash table if prompted by the "clean" option.
		// Recover an _initialized_ hash table if prompted by "not clean"
	
	// Start timer for whole experiment
	timer wholeExperiment;

	// Run NumberOfRequests requests, applying the given probability that the
	// request is a GET or PUT.
	ExperimentInterval* thisInterval = NULL;
	unsigned int thisIntervalId = 1;
	for (int currentRequest = 0; currentRequest < TotalRequestsInExperiment; ++currentRequest)
	{
		// Start timer for every p% intervals.
		if (thisInterval == NULL)
			thisInterval = new ExperimentInterval;
			
		// Run Request
		sleep(1);
		
		// Report elapsed time
		if (currentRequest >= static_cast<double>(TotalRequestsInExperiment) / IntervalsInExperiment)
		{
			std::cout << "Interval " << thisIntervalId << ": " << thisInterval->elapsed() << "s" << std::endl;
			delete thisInterval;
			thisInterval = NULL;
			++thisIntervalId;
		}
	}
	
	std::cout << "Whole Experiment: " << wholeExperiment.elapsed() << "s" << std::endl;
	
	return 0;
}