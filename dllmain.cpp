// dllmain.cpp : Defines the entry point for the DLL application.
#include "GlovesFinalDLL.h"
#include "pch.h"
#include "Manus.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "conio.h"

extern "C" {
	double moveValue() {
		manus_session_t session;
		manus_ret_t status = ManusInit(&session);
		manus_hand_t lhand;

		manus_ret_t left = ManusGetHand(session, GLOVE_LEFT, &lhand);
		/*void sleep(unsigned milliseconds);
		{
			Sleep(50);
		}*/
		double temp = left == MANUS_SUCCESS ? lhand.raw.imu[0] : 0.0f;
		double newTemp = temp * 10;
		/*if (newTemp > 1)
		{
			printf("You are turning in a positive direction: [%f]\n", newTemp);
		}
		else if (newTemp < -1) {
			printf("You are turning in a negative direction: [%f]\n", newTemp);
		}
		else {
			printf("You are at resting position: [%f]\n", newTemp);
		}*/
		return newTemp;
	}

	// Handle a manus error return code.
	bool Error(manus_ret_t status, int& retval)
	{
		printf("Error %d: %s\n", status, ManusErrorString(status));
		printf("Press q to exit, or r to resume.\n");

		char c = 0;

		while (c != 'q')
		{
			// Get keyboard input.
			if (_kbhit())
			{
				c = _getch();
			}

			// Resume.
			if (c == 'r')
			{
				return true;
			}
		}

		retval = EXIT_FAILURE;
		return false;
	}
}
