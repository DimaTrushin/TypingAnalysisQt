#ifndef CSMOOTHFUNCTION_H
#define CSMOOTHFUNCTION_H
//---------------------------------------------------------------------------
// Define
//---------------------------------------------------------------------------

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <cmath>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// TO DO
// reimplement this in Qt Creator
//
// Rad Studio is unable to specialize template parameters correctly
// in AuxiliaryPower function template.
// Therefore I have to use them explicitly

template<int Number>
class ResidueMod2 {
public:
  static const int Result = Number % 2;
};
//---------------------------------------------------------------------------

template<int Number, int ResidueMod2 = ResidueMod2<Number>::Result>
class AuxiliaryPower {
public:
  inline static double evaluate(double base, double semiResult) {
    return semiResult;
  }
};
//---------------------------------------------------------------------------

template<int Number>
class AuxiliaryPower<Number, 0> {
public:
  inline static double evaluate(double base, double semiResult) {
    return AuxiliaryPower<Number / 2,
           ResidueMod2<Number / 2>::Result>
           ::evaluate(base * base, semiResult);
  }
};
//---------------------------------------------------------------------------

template<int Number>
class AuxiliaryPower<Number, 1> {
public:
  inline static double evaluate(double base, double semiResult) {
    return AuxiliaryPower<Number - 1,
           ResidueMod2<Number - 1>::Result>
           ::evaluate(base, base * semiResult);
  }
};
//---------------------------------------------------------------------------

template<int Number>
class AuxiliaryPower<Number, -1> {
public:
  inline static double evaluate(double base, double semiResult) {
    return AuxiliaryPower<Number + 1,
           ResidueMod2<Number + 1>::Result>
           ::evaluate(base, semiResult / base);
  }
};
//---------------------------------------------------------------------------

template<>
class AuxiliaryPower<0, 0> {
public:
  inline static double evaluate(double, double semiResult) {
    return semiResult;
  }
};
//---------------------------------------------------------------------------
// Fast Power Rising function (including negative ones)

template<int Number>
class Power {
public:
  inline static double evaluate(double argument) {
    return AuxiliaryPower<Number>::evaluate(argument, 1.0);
  }
};
//---------------------------------------------------------------------------
// Declaration of EFunctionType
//---------------------------------------------------------------------------
// Function marker is needed for correct computation of a derivative

enum class EFunctionType : unsigned char {
  Argument, Constant, Minus, Power, Exp, Log, Sin, Cos, Sqrt,
  Sum, Difference, Product, Quotient, Composition
};
//---------------------------------------------------------------------------
// Basic Smooth Functions
//---------------------------------------------------------------------------
// Smooth function is a class with two members:
// static constant FunctionType, which is a marker of the function
// static method ::evaluate(argument), which computes the function

// Smooth functions are divided into two groups: (1) Basic (2) Operations

// Basic Functions:
// CTArg::evaluate(x) = x
// CTConstant::evaluate(x) = CTConstant::Constant
// <- is a compilation time constant
// CTZero::evaluate(x) = 0
// CTOne::evaluate(x) = 1
// CTPower<n>::evaluate(x) = x^n
// CTExponent::evaluate(x) = e^x
// CTLogarithm::evaluate(x) = ln(x)
// CTSinus::evaluate(x) = sin(x)
// CTCosinus::evaluate(x) = cos(x)
// CTSqrt::evaluate(x) = sqrt(x)
// CTPi::evaluate(x) = \pi
// CTStandardNormalDensity::evaluate(x) = e^(-(x^2)/2) / sqrt(2 * M_PI)

// Operations allow construction any smooth functions from basic primitives
// Example, e^sin(x) is given by
// using Function = CTComposition<CTExponent, CTSinus>;
// Then, Function::evaluate(x) = e^sin(x)

class CTArg {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Argument;

  inline static double evaluate(double argument) {
    return argument;
  }
};
//---------------------------------------------------------------------------

template<int constant>
class CTConstant {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Constant;

  inline static double evaluate(double argument) {
    return static_cast<double>(constant);
  }
};
//---------------------------------------------------------------------------

using CTZero = CTConstant<0>;
//---------------------------------------------------------------------------

using CTOne = CTConstant<1>;
//---------------------------------------------------------------------------

class CTPi {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Constant;

  inline static double evaluate(double) {
    return M_PI;
  }
};
//---------------------------------------------------------------------------

template<int power>
class CTPower {
public:
  static constexpr int _Power = power;
  static constexpr EFunctionType FunctionType = EFunctionType::Power;

  inline static double evaluate(double argument) {
    return Power<power>::evaluate(argument);
  }
};
//---------------------------------------------------------------------------

class CTExponent {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Exp;

  inline static double evaluate(double argument) {
    return std::exp(argument);
  }
};
//---------------------------------------------------------------------------

class CTLogarithm {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Log;

  inline static double evaluate(double argument) {
    return std::log(argument);
  }
};
//---------------------------------------------------------------------------

class CTSinus {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Sin;

  inline static double evaluate(double argument) {
    return std::sin(argument);
  }
};
//---------------------------------------------------------------------------

class CTCosinus {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Cos;

  inline static double evaluate(double argument) {
    return std::cos(argument);
  }
};
//---------------------------------------------------------------------------

class CTSqrt {
public:
  static constexpr EFunctionType FunctionType = EFunctionType::Sqrt;

  inline static double evaluate(double argument) {
    return std::sqrt(argument);
  }
};
//---------------------------------------------------------------------------
// Smooth Function Operators
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Binary
//---------------------------------------------------------------------------

template<class F, class S>
class CTSum {
public:
  using First = F;
  using Second = S;

  static constexpr EFunctionType FunctionType = EFunctionType::Sum;

  inline static double evaluate(double argument) {
    return First::evaluate(argument) + Second::evaluate(argument);
  }
};
//---------------------------------------------------------------------------

template<class F, class S>
class CTDifference {
public:
  using First = F;
  using Second = S;

  static constexpr EFunctionType FunctionType = EFunctionType::Difference;

  inline static double evaluate(double argument) {
    return First::evaluate(argument) - Second::evaluate(argument);
  }
};
//---------------------------------------------------------------------------

template<class F, class S>
class CTProduct {
public:
  using First = F;
  using Second = S;

  static constexpr EFunctionType FunctionType = EFunctionType::Product;

  inline static double evaluate(double argument) {
    return First::evaluate(argument) * Second::evaluate(argument);
  }
};
//---------------------------------------------------------------------------

template<class F, class S>
class CTQuotient {
public:
  using First = F;
  using Second = S;

  static constexpr EFunctionType FunctionType = EFunctionType::Quotient;

  inline static double evaluate(double argument) {
    return First::evaluate(argument) / Second::evaluate(argument);
  }
};
//---------------------------------------------------------------------------

template<class F, class S>
class CTComposition {
public:
  using First = F;
  using Second = S;

  static constexpr EFunctionType FunctionType = EFunctionType::Composition;

  inline static double evaluate(double argument) {
    return First::evaluate(Second::evaluate(argument));
  }
};
//---------------------------------------------------------------------------
// Unary
//---------------------------------------------------------------------------

template<class F>
class CTMinus {
public:
  using First = F;

  static constexpr EFunctionType FunctionType = EFunctionType::Minus;

  inline static double evaluate(double argument) {
    return -First::evaluate(argument);
  }
};
//---------------------------------------------------------------------------

using CTTangent = CTQuotient<CTSinus, CTCosinus>;
//---------------------------------------------------------------------------

using CTCotangent = CTQuotient<CTCosinus, CTSinus>;
//---------------------------------------------------------------------------

// The namespace is required to construct standard normal distribution
namespace NSSmoothFunctionTemplate {
using TWO = CTConstant<2>;
using Numerator = CTProduct<CTArg, CTArg>;            // x^2
using Fraction = CTQuotient<Numerator, TWO>;          // (x^2)/2
using ExpArg = CTMinus<Fraction>;                     // -(x^2)/2
using Exponent = CTComposition<CTExponent, ExpArg>;   // e^(-(x^2)/2)
using TwoPi = CTProduct<TWO, CTPi>;                   // 2 * M_PI
using SqrtTwoPi = CTComposition<CTSqrt, TwoPi>;       // sqrt(2 * M_PI)
using StandardNormalDensity = CTQuotient< Exponent,
      SqrtTwoPi>; // e^(-(x^2)/2) / sqrt(2 * M_PI)
}
//---------------------------------------------------------------------------

using CTStandardNormalDensity =
  NSSmoothFunctionTemplate::StandardNormalDensity;
//---------------------------------------------------------------------------
// Derivative of Smooth Function
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// General Template
//---------------------------------------------------------------------------

template<class F, EFunctionType Type = F::FunctionType>
class CTDerivative {
};
//---------------------------------------------------------------------------
// Derivative of Basic Function
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Constant> {
public:
  using Result = CTZero;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Argument> {
public:
  using Result = CTOne;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Exp> {
public:
  using Result = CTExponent;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Log> {
public:
  using Result = CTComposition<CTPower<-1>, CTArg>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Sin> {
public:
  using Result = CTCosinus;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Cos> {
public:
  using Result = CTMinus<CTSinus>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Sqrt> {
  using TWO = CTConstant<2>;
  using Denominator = CTProduct<TWO, CTSqrt>;
public:
  using Result = CTQuotient<CTOne, Denominator>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Power> {
public:
  using Result = CTProduct< CTConstant<F::_Power>,
        CTPower<F::_Power - 1>>;
};
//---------------------------------------------------------------------------
// Derivative of Operation
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Minus> {
public:
  using Result = CTMinus<typename CTDerivative<typename F::First>::Result>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Sum> {
  using FirstDerivative =
    typename CTDerivative<typename F::First>::Result;
  using SecondDerivative =
    typename CTDerivative<typename F::Second>::Result;
public:
  using Result = CTSum<FirstDerivative, SecondDerivative>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Difference> {
  using FirstDerivative =
    typename CTDerivative<typename F::First>::Result;
  using SecondDerivative =
    typename CTDerivative<typename F::Second>::Result;
public:
  using Result = CTDifference<FirstDerivative, SecondDerivative>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Product> {
  using FirstDerivative =
    typename CTDerivative<typename F::First>::Result;
  using SecondDerivative =
    typename CTDerivative<typename F::Second>::Result;

  using FirstSummand =
    CTProduct<FirstDerivative, typename F::Second>;
  using SecondSummand =
    CTProduct<typename F::First, SecondDerivative>;
public:
  using Result = CTSum<FirstSummand, SecondSummand>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Quotient> {
  using Numerator = typename F::First;
  using Denominator = typename F::Second;
  using NumeratorDerivative =
    typename CTDerivative<Numerator>::Result;
  using DenominatorDerivative =
    typename CTDerivative<Denominator>::Result;

  using FirstNumeratorSummand =
    CTProduct<NumeratorDerivative, Denominator>;
  using SecondNumeratorSummand =
    CTProduct<Numerator, DenominatorDerivative>;
  using newNumerator =
    CTDifference< FirstNumeratorSummand, SecondNumeratorSummand>;
  using newDenominator = CTProduct<Denominator, Denominator>;
public:
  using Result = CTQuotient<newNumerator, newDenominator>;
};
//---------------------------------------------------------------------------

template<class F>
class CTDerivative<F, EFunctionType::Composition> {
  using OuterFunction = typename F::First;
  using InnerFunction = typename F::Second;
  using OuterDerivative =
    typename CTDerivative<OuterFunction>::Result;
  using InnerDerivative =
    typename CTDerivative<InnerFunction>::Result;

  using FirstMultiple =
    CTComposition<OuterDerivative, InnerFunction>;
public:
  using Result = CTProduct<FirstMultiple, InnerDerivative>;
};
//---------------------------------------------------------------------------
// Successive derivative of Basic Function
//---------------------------------------------------------------------------

namespace NSSuccessiveDerivative {
template<class F, unsigned int derivative>
class CTSuccessiveDerivative {
public:
  using Result =
    typename CTDerivative<
    typename CTSuccessiveDerivative<F, derivative - 1>::Result
    >::Result;
};
//---------------------------------------------------------------------------

template<class F>
class CTSuccessiveDerivative<F, 0> {
public:
  using Result = F;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
// CTSuccessiveDerivative
//---------------------------------------------------------------------------

template<class F, unsigned int derivative>
using CTSuccessiveDerivative =
  typename NSSuccessiveDerivative::
  CTSuccessiveDerivative<F, derivative>::Result;
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif // CSMOOTHFUNCTION_H
