#pragma once

#include "CAFAna/Prediction/IPrediction.h"

#include "CAFAna/Prediction/PredictionNoExtrap.h"

#include "CAFAna/Core/Loaders.h"

namespace ana
{
  /// TODO comment
  class PredictionSBNExtrap: public IPrediction
  {
  public:
    PredictionSBNExtrap(Loaders& loadersND,
                        Loaders& loadersFD,
                        const HistAxis& axis,
                        const Cut& cut,
                        const SystShifts& shift = kNoShift,
                        const Var& wei = kUnweighted);
    virtual ~PredictionSBNExtrap();

    virtual Spectrum Predict(osc::IOscCalculator* calc) const override;

    virtual Spectrum PredictComponent(osc::IOscCalculator* calc,
                                      Flavors::Flavors_t flav,
                                      Current::Current_t curr,
                                      Sign::Sign_t sign) const override;

    OscillatableSpectrum ComponentCC(int from, int to) const override;
    //    Spectrum ComponentNC() const override;

    virtual void SaveTo(TDirectory* dir) const override;
    static std::unique_ptr<PredictionSBNExtrap> LoadFrom(TDirectory* dir);

    PredictionSBNExtrap() = delete;

  protected:
    PredictionSBNExtrap(const PredictionNoExtrap& pn,
                        const PredictionNoExtrap& pf,
                        const Spectrum& d)
      : fPredND(pn), fPredFD(pf), fDataND(d)
    {
    }

    PredictionNoExtrap fPredND, fPredFD;
    Spectrum fDataND;
  };
}