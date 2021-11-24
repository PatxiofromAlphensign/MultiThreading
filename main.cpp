#include<stdlib.h>
#include<iostream>
#include <thread>
#include <vector>
#include <numeric>

#include "utility.h"

const int no_of_threads = 5;
const int no_of_elems = 500 * 500 * 500;
const int step = no_of_elems / no_of_threads;
std::vector<uint64_t> partial_sums(no_of_threads);


std::thread **create_threads(int count) {
	std::thread **thrd = (std::thread**)malloc(sizeof(std::thread**)*count);
	for(int i=0;i<count;i++) {
    		std::thread  *t=  new std::thread(AccumulateRange, std::ref(partial_sums[1]), step, no_of_threads * step);
		thrd[i] = t;
	}
	return thrd;
} 

std::vector<int> *join_thread_n_get_sizes(std::thread **thrd) {
	int size;
	std::vector<int> *v = new std::vector<int>;	
	for(int i=0;thrd[i]!=NULL;i++) {(*(thrd[i])).join();size=i;(*v).push_back(size);}
	return v;

}

int main()
{
    std::thread t1(AccumulateRange, std::ref(partial_sums[0]), 0, step);
    std::thread t2(AccumulateRange, std::ref(partial_sums[1]), step, no_of_threads * step);
    std::thread t3;

    std::thread **thrd = create_threads(3);
    t1.join();
    t2.join();
    std::vector<int> *vec = join_thread_n_get_sizes(thrd);
    uint64_t acc  = std::accumulate((*vec).begin(), (*vec).end(), uint64_t(0));
    uint64_t total = std::accumulate(partial_sums.begin(), partial_sums.end(), uint64_t(0));
    PrintVector(partial_sums);
    std::cout << " Total: " << total << std::endl;
    std::cout << "\n\n\n" << " mine :): " << acc << std::endl;
}

