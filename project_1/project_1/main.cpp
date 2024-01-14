#include "City.h"
#include "History.h"
#include <iostream>
using namespace std;

int main()
{
    for (int nTries = 0; nTries < 200; nTries++)
    {
        City ct(2, 3);
        ct.addPlayer(1, 2);
        ct.addTooter(2, 1);
        ct.addTooter(2, 3);

        ct.preachToTootersAroundPlayer();
        // If (2,1) was converted or (2,3) was not, try again.
        if (ct.nTootersAt(2, 1) == 0  ||  ct.nTootersAt(2, 3) != 0)
            continue;

        ct.preachToTootersAroundPlayer();
        if (ct.nTootersAt(2, 1) != 0)
        {
            // At this point, we know (2,3) was converted immediately
            // and (2,1) was unconverted twice.  The probability of
            // reaching this point on a given try is 7.4%.
            ct.history().display();
            break;
        }

        // At this point, we did not reach the call to display, so try
        // the test again.  There's a 99.99998% probability that in 200
        // tries, we'll have a test where the call to display will be
        // reached.
    }
    cout << "===" << endl;
    }
