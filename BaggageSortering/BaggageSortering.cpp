#include "Airport.h"
#include "Baggage.h"
#include "BaggageSplitter.h"
#include "CheckInDesk.h"
#include "Flight.h"
#include "Spawner.h"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

int main()
{
    srand((unsigned)time(NULL));

    Spawner<Baggage> baggageSpawner;

    // Create a number of check in desks
    CheckInDesk* checkInDesks[Airport::NumberOfCheckInDesks];

    for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
        CheckInDesk* checkInDeskInstance = new CheckInDesk();
        checkInDesks[i] = checkInDeskInstance;
    }

    // Create a number of terminals
    Terminal* terminals[Airport::NumberOfTerminals];

    for (int i = 0; i < Airport::NumberOfTerminals; i++)
    {
        terminals[i] = new Terminal(i);
    }

    // Start the check in desks
    std::thread checkInThreads[Airport::NumberOfCheckInDesks];

    for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
        int index = i; // Create a copy of i to pass to the thread
        checkInThreads[index] = std::thread([index, &checkInDesks, &baggageSpawner] {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937_64 rng(rd()); // seed the generator
            std::uniform_int_distribution<int> uni(500, 2000); // define the range

            std::this_thread::sleep_for(std::chrono::seconds(index));

            while (true) {
                // Spawn a new passenger every 0.5 - 2 seconds as long as the check in desk buffer is not full
                if (checkInDesks[index]->IsFull()) {
                    break;
                }
                else {
                    std::unique_lock ul(*CheckInDesk::GetMutex(), std::defer_lock);
                    CheckInDesk::GetConditionVariable()->wait(ul, [index, &checkInDesks, &baggageSpawner]
                        {
                            if (CheckInDesk::GetMutex()->try_lock())
                            {
                                // std::cout << "Thread " << index << " is spawning baggage\n"; // DEBUG

                                Baggage* baggage = baggageSpawner.Spawn();

                                // TODO: Check if bagge destination terminal is full
                                // TODO: If full, baggage is turned down (we can't sell more tickets than we have available storage space for)

                                // std::cout << "Spawned baggage with id " << baggage->GetID() << " and destination " << baggage->GetDestination() << "\n";
                                checkInDesks[index]->CheckInBaggage(baggage);

                                CheckInDesk::GetMutex()->unlock();
                            }

                            return true;
                        });
                    // std::cout << "Thread " << index << " is notifying\n";  // DEBUG
                    CheckInDesk::GetConditionVariable()->notify_one();
                }
                int sleepFor = uni(rng);
                // std::cout << "Thread " << index << " is sleeping for " << sleepFor << " ms\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));
            }
            });
    }

    // Start the baggage splitter
    BaggageSplitter baggageSplitter(checkInDesks, terminals);

    std::thread baggageSplitterThread([&baggageSplitter]
        {
            while (true)
            {
                baggageSplitter.Run();
            }
        });

    // Start the terminal threads
    std::thread terminalThreads[Airport::NumberOfTerminals];

    for (int i = 0; i < Airport::NumberOfTerminals; i++) {
        {
            int index = i; // Create a copy of i to pass to the thread
            terminalThreads[index] = std::thread([index, &terminals]
                {
                    while (true) {
                        terminals[index]->Run();
                    }
                });
        }
    }


    while (true) {
        system("CLS");
        
        for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
            std::cout << "Desk " << i << " has " << checkInDesks[i]->GetBaggageCount() << " baggage in queue\n";
        }

        for (int i = 0; i < Airport::NumberOfTerminals; i++) {
            std::cout << "Terminal " << i << " has " << terminals[i]->GetBaggageCount() << " baggage in queue\n";
        }

        for (int i = 0; i < Airport::NumberOfTerminals; i++) {
            std::cout << "Terminal " << i << " next flight: " << terminals[i]->GetFlight()->GetID() << " to  " << terminals[i]->GetFlight()->GetDestination() << " | Loaded baggage: " << terminals[i]->GetFlight()->GetBaggageCount() << "\n";
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