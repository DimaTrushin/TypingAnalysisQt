//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Approximation.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CSpeedDefinitions
//---------------------------------------------------------------------------

double CSpeedDefinitions::getDeviation(double mean) const {
  return std::sqrt(mean) * kDeviationCoefficient;
}
//---------------------------------------------------------------------------

CSpeedDefinitions::CDoublePair
CSpeedDefinitions::getChunkOfValues(double argument,
                                    double chunk) const {
  if (!(argument > 0.0))
    return CDoublePair(0.0, 0.0);
  double chunkNumber = std::floor(directRescale(argument) / chunk);
  double minimalBound = reverseRescale(chunkNumber * chunk);
  double maximalBound = reverseRescale((chunkNumber + 1.0) * chunk);
  return CDoublePair(minimalBound, maximalBound);
}
//---------------------------------------------------------------------------

double CSpeedDefinitions::directRescale(double argument) const {
  return kDeviationCoefficient * std::sqrt(argument);
}
//---------------------------------------------------------------------------

double CSpeedDefinitions::reverseRescale(double argument) const {
  return  (argument / kDeviationCoefficient) *
          (argument / kDeviationCoefficient);
}
//---------------------------------------------------------------------------
// Global Functions
//---------------------------------------------------------------------------

double StandardDistribution(double argument) {
  double result = argument * argument;
  result /= -2.0;
  result = std::exp(result);
  result /= std::sqrt(2.0 * M_PI);
  return result;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
