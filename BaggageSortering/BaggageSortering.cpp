#include "Airport.h"
#include "Baggage.h"
#include "BaggageSplitter.h"
#include "CheckInDesk.h"
#include "Flight.h"
#include "Spawner.h"
#include "Timer.h"

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
        checkInThreads[index] = std::thread([index, &checkInDesks, &terminals, &baggageSpawner] {
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
                    CheckInDesk::GetConditionVariable()->wait(ul, [index, &checkInDesks, &terminals, &baggageSpawner]
                        {
                            if (CheckInDesk::GetMutex()->try_lock())
                            {
                                Baggage* baggage = baggageSpawner.Spawn(); 

                                // If there is place in the terminal, check in the baggage, otherwise refuse it

                                // TODO: It would be better if full terminals weren't available to be spawned to in the first place, because then we could avoid this check
                                // and it would also be more realistic (passengers would ideally not be able to book a flight to a full terminal)
                                // Right now, it is like a customer shows up at the airport, with tickets and everything, only to be told that the terminal is full when they get try to check in their baggage
                                // Alternatively, it would also have been nicer to do the check in the terminal when we add the baggage (because then we would be doing standard array indexing operations error handling,
                                // instead of checking in main if a something is full in an entirely different class........ but yeah)
                                // 
                                // Just to show that I am aware of this, but have chosen to prioritize differently with the goal of finishing the project in time :)
                                // 
                                // But this works for now, and I need to create a GUI for this project, so I'll put this on the back burner and implement it if I have time

                                if (terminals[baggage->GetDestinationTerminal()]->GetBaggageCount() < Terminal::GetMaxBaggage())
                                {
                                    checkInDesks[index]->CheckInBaggage(baggage);
                                }
                                else
                                {
                                    delete(baggage); // Refuse baggage, we can't take in more baggage than we have storage space for in the terminals
                                }
                                CheckInDesk::GetMutex()->unlock();
                            }

                            return true;
                        });
                    CheckInDesk::GetConditionVariable()->notify_one();
                }

                int sleepFor = uni(rng);
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

    // Create clock
    Timer* t = new Timer(23, 59, 30);

    std::thread timerThread([t] {
        t->Run();
        });

    while (true) {
        system("CLS");
        
        for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
            std::cout << "Desk " << i << " has " << checkInDesks[i]->GetBaggageCount() << " baggage in queue\n";
        }

        for (int i = 0; i < Airport::NumberOfTerminals; i++) {
            std::cout << "Terminal " << i << " has " << terminals[i]->GetBaggageCount() << "/" << Terminal::GetMaxBaggage() << " baggage in queue\n";
        }

        for (int i = 0; i < Airport::NumberOfTerminals; i++) {
            std::cout << "Terminal " << i << " next flight: " << terminals[i]->GetFlight()->GetID() << " to  " << terminals[i]->GetFlight()->GetDestination() << " | Loaded baggage: " << terminals[i]->GetFlight()->GetBaggageCount() << "/" << terminals[i]->GetFlight()->GetMaxBaggage() << "\t| Departure time: " << terminals[i]->GetFlight()->GetDepartureTime() << " | Global time: " << Timer::GetGlobalTime() << " Departure time: " << terminals[i]->GetFlight()->GetFlightTime() << " | Time to departure: " << terminals[i]->GetFlight()->GetFlightTime() - Timer::GetGlobalTime() << "s\n";
        }

        t->DisplayClock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    // Join threads
    for (int i = 0; i < Airport::NumberOfCheckInDesks; i++) {
        checkInThreads[i].join();
    }

    char c;
    std::cin >> c;
}