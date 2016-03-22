﻿#ifndef CONFIG_HXX
#define CONFIG_HXX


#include <utility>

#include <QColor>
#include <QMap>
#include <QString>

#include "math/numerictypes.hxx"


namespace Config
{
  namespace Gui
  {
    namespace Defaults
    {
      constexpr double Alpha = 1.;
      constexpr double Beta = 1.;
      constexpr double Gamma = 1.;
      constexpr double Delta = 1.;
      constexpr double Epsilon = 1.;
      constexpr double Mu = 1.;

      constexpr double A = -10.;
      constexpr double B = 10.;
      constexpr double C = -5.;
      constexpr double D = 5.;

      constexpr int N = 10;
      constexpr int DeltaExponent = -2;
      constexpr double IntegrParam_A = -1.;
      constexpr double IntegrParam_B = 1.;

      constexpr bool LiveUpdateEnabled = false;
    }


    namespace InputLimits
    {
      constexpr double ABCD_Min = -100.;
      constexpr double ABCD_Max = 100.;

      constexpr double Step = .5;
    }


    namespace PlotParams
    {
      constexpr int ResolutionMultiplier = 1;

      constexpr double Margins = .25;

      constexpr double SelectedPenWidth = 2.;

      constexpr int FontSize = 9;
    }


    const QMap<QString, QColor> Colors {
      std::make_pair<QString, QColor> (QStringLiteral ("Red"), QColor (244, 67, 54)),
      std::make_pair<QString, QColor> (QStringLiteral ("Pink"), QColor (233, 30, 99)),
      std::make_pair<QString, QColor> (QStringLiteral ("Purple"), QColor (156, 39, 176)),
      std::make_pair<QString, QColor> (QStringLiteral ("DeepPurple"), QColor (103, 58, 183)),
      std::make_pair<QString, QColor> (QStringLiteral ("Indigo"), QColor (63, 81, 181)),
      std::make_pair<QString, QColor> (QStringLiteral ("Blue"), QColor (33, 150, 243)),
      std::make_pair<QString, QColor> (QStringLiteral ("LightBlue"), QColor (3, 169, 244)),
      std::make_pair<QString, QColor> (QStringLiteral ("Cyan"), QColor (0, 188, 212)),
      std::make_pair<QString, QColor> (QStringLiteral ("Teal"), QColor (0, 150, 136)),
      std::make_pair<QString, QColor> (QStringLiteral ("Green"), QColor (76, 175, 80)),
      std::make_pair<QString, QColor> (QStringLiteral ("LightGreen"), QColor (139, 195, 74)),
      std::make_pair<QString, QColor> (QStringLiteral ("Lime"), QColor (205, 220, 57)),
      std::make_pair<QString, QColor> (QStringLiteral ("Yellow"), QColor (255, 235, 59)),
      std::make_pair<QString, QColor> (QStringLiteral ("Amber"), QColor (255, 193, 7)),
      std::make_pair<QString, QColor> (QStringLiteral ("Orange"), QColor (255, 152, 0)),
      std::make_pair<QString, QColor> (QStringLiteral ("DeepOrange"), QColor (255, 87, 34)),
      std::make_pair<QString, QColor> (QStringLiteral ("Brown"), QColor (121, 85, 72)),
      std::make_pair<QString, QColor> (QStringLiteral ("Grey"), QColor (158, 158, 158)),
      std::make_pair<QString, QColor> (QStringLiteral ("BlueGrey"), QColor (96, 125, 139))
    };
  }


  namespace MathConstants
  {
//    constexpr Math::Float32 Epsilon = 1E-5F;
//    constexpr Math::Float64 Epsilon = 1E-14;
    constexpr Math::Float80 Epsilon = 1E-17L;
//    constexpr Math::Float128 Epsilon = 1E-32Q;
  }
}


#endif // CONFIG_HXX
