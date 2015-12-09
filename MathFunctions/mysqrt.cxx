#include <stdio.h>
#include <math.h>
#include "MathFunctions.h"
#include "TutorialConfig.h"
#include "Table.h"

// a hack square root calculation using simple operations
double mysqrt(double x)
{
  if (x <= 0)
    {
    return 0;
    }

  double result;
  double delta;  

  result = x;

  // use the table to help find an initial value
  if (x > 0 and x < 10)
    {
    result = sqrtTable[static_cast<int>(x)];
    }

  // do ten iterations
  int i;
  for (i = 0; i < 10; ++i)
    {
    if (result <= 0)
      {
      result = 0.1;
      }
    delta = x - (result*result);
    result = result + 0.5*delta/result;
    fprintf(stdout,"Computing sqrt of %g to be %g\n",x,result);
    }

  return result;
}