/**
* Example
* SafeSequence.cpp
*
*/

#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>          // std::mutex

using std::cout;
using std::endl;
using std::vector;
using std::thread;
using std::mutex;
using std::for_each;


class SafeSequence {
private:
	int value;
	mutex mtx;  // To ensure serialized access to value

public:
	SafeSequence()
		:value(0)
	{ }

	/**
	 * Returns next value in sequence.
	 */
	int getNext() {
		mtx.lock();
		int tmp = value++;  // Increment under mutex protection
		mtx.unlock();
		return tmp;
	}
};


class SequenceThreadFunctor {
private:
	SafeSequence &iSeq; // Reference to shared UnsafeSequence
	vector<int> iVec; // Reference to shared vector for number storage
	const int iLimit;
	mutex &mutexRef;  // To ensure serialized access to value

public:
	SequenceThreadFunctor(SafeSequence &seq, vector<int> &vec, int limit, mutex &mtx)
		:iSeq(seq), iVec(vec), iLimit(limit), mutexRef(mtx)
	{ }

	void operator()() {
		int n = 0;
		// Get numbers and add them to the shared Vector
		while (true) {
			//mutexRef.lock();
			n = iSeq.getNext();
			if (n <= iLimit) {
				iVec.push_back(n); // Synchronize push_backs
				//mutexRef.unlock();
			}
			else {
				//mutexRef.unlock();
				break;
			}
		}
	}
};



class SafeSequenceTest {

private:
	const int MAX;  // Sequence upper limit
	const int THREADS; // # threads

	// The threads
	vector<thread> threads;

	// A vector for the produced numbers, shared among the threads
	vector<int> values;

	// The source of the sequence 0,1,2...
	SafeSequence safe;  // Shared among the threads

	// mutex to prevent concurrent access to vector::push_back()
	mutex mtx;

public:
	SafeSequenceTest(int limit, int nThreads)
		:MAX(limit), THREADS(nThreads)
	{
		// Create the wanted number of sequence threads
		for (int i = 0; i < THREADS; ++i)
			threads.push_back(thread());  // default construct for deferred start, does not yet represent a thread of execution

		// Start the threads
		for (int i = 0; i < THREADS; ++i) {
			threads[i] = thread(SequenceThreadFunctor(safe, values, MAX, mtx)); // Start the thread
		}

		// Wait for the threads to finish
		for (int i = 0; i < THREADS; ++i)
			threads[i].join();

		// Check for errors

		bool errorsFound{ false };
		int prevValue{ values[0] };
		int nErrors{ 0 };

		for (int i = 1; i < values.size(); ++i) {
			if (values[i] <= prevValue) {
				errorsFound = true;
				break;
			}
			prevValue = values[i];
		}

		if (errorsFound) {
			for (int i = 0; i < values.size(); ++i)
				if (i != values[i]) {
					cout << "Expected " << i << " got " << values[i] << endl;
					++nErrors;
				}
			cout << "\n" << nErrors << " numbers were reordered\n" << endl;
		}
		else
			cout << "Success!\nAll values were stored in correct increasing order.\n" << endl;
	}
};


int main()
{
	SafeSequenceTest sst(20000, 4);
	return 0;
}

