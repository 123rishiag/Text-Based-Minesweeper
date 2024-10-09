#pragma once
#include <chrono>

namespace Time {
	/*
		// The TimeService class helps keep track of time in game and calculate delta time.
		// Utilizes the <chrono> library to calculate delta time.
	*/
	class TimeService
	{
	private:

		// A point in time which indicates the starting time of previous frame.
		std::chrono::time_point<std::chrono::steady_clock> previous_time;
		// No need to worry about the syntax of this variable too much right now
		// It'll be explained in detail at a later time.

		float delta_time; //to store the delta time

		void updateDeltaTime(); // method to update time
		float calculateDeltaTime() const; //calculate time by subtracting the previous time from the current time
		void updatePreviousTime(); // finally update the current time to be previous time

	public:

		//lifecycle methods
		void initialize();
		void update();

		//getter
		float getDeltaTime() const;
	};
}