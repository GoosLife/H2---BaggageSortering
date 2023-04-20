#include "Spawner.h"
#include "Airport.h"
#include "Baggage.h"
#include "CheckInDesk.h"
#include "Flight.h"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

int main()
{
    srand((unsigned)time(NULL));

    Spawner<Baggage> baggageSpawner;
    Spawner<Flight> flightSpawner;

    // Create a number of check in desks and start loading in baggage
    CheckInDesk* checkInDesks[Airport::NumberOfCheckInDesks];

    for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
        checkInDesks[i] = new CheckInDesk();
    }

    std::thread checkInThreads[Airport::NumberOfCheckInDesks];

    for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
        int index = i; // Create a copy of i to pass to the thread
        checkInThreads[index] = std::thread([index, &checkInDesks, &baggageSpawner] {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937_64 rng(rd()); // seed the generator
            std::uniform_int_distribution<int> uni(500, 2000); // define the range

            while (true) {
                // Spawn a new passenger every 0.5 - 2 seconds as long as the check in desk buffer is not full
                if (checkInDesks[index]->IsFull()) {
                    break;
                }
                else {
                    Baggage baggage = baggageSpawner.Spawn();
                    checkInDesks[index]->CheckInBaggage(baggage);
                }
                int sleepFor = uni(rng);
                std::cout << "Thread " << index << " is sleeping for " << sleepFor << " ms\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));
            }
            });
    }



    while (true) {
        system("CLS");
        
        for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
            std::cout << "Desk " << i << " has " << checkInDesks[i]->GetBaggageCount() << " baggage in queue\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    // Join threads
    for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
        checkInThreads[i].join();
    }

    char c;
    std::cin >> c;
}