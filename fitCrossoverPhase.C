#include "TGraphErrors.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"

void fitCrossoverPhase()
{
    TGraphErrors *dataWoofer = new TGraphErrors("datiLab2/SweepFaseWoofer.txt", "%lg %lg %lg");
    TGraphErrors *dataTweeter = new TGraphErrors("datiLab2/SweepFaseTweeter.txt", "%lg %lg %lg");

    // Fit woofer: [0] = L, [1] = R
    TF1 *fitWoofer = new TF1("fW", "360/(2 * TMath::Pi()) * -TMath::ATan(2*TMath::Pi()*x*[0]/[1])", 8000, 12000);
    // fitWoofer->Draw();
    fitWoofer->SetParameters(10.2e-3, 559.9);
    fitWoofer->SetParLimits(0, 9.e-3, 11.e-3);
    fitWoofer->SetParLimits(1, 550., 570.);
    dataWoofer->Fit("fW", "Q");

    // Fit tweeter: [0] = C, [1] = R
    TF1 *fitTweeter = new TF1("fT", "360/(2 * TMath::Pi()) * TMath::ATan(1/(2*TMath::Pi()*x*[0]*[1]))", 8000, 12000);
    fitTweeter->SetParameters(26.1e-9, 560.);
    fitTweeter->SetParLimits(0, 10.e-9, 40e-9);
    fitWoofer->SetParLimits(1, 500., 600.);
    dataTweeter->Fit("fT", "Q");

    dataWoofer->Draw();
    dataWoofer->GetYaxis()->SetRangeUser(-80, 80);
    dataTweeter->Draw("same");
    // fitWoofer->Draw("SAME");
    // fitTweeter->Draw("SAME");

    std::cout << "Woofer phase fit:" << '\n';
    std::cout << "L = " << fitWoofer->GetParameter(0) << " +/- " << fitWoofer->GetParError(0) << " Henry" << '\n';
    std::cout << "R = " << fitWoofer->GetParameter(1) << " +/- " << fitWoofer->GetParError(1) << " Ohm" << '\n';
    std::cout << "reduced chi-square = " << fitWoofer->GetChisquare() / fitWoofer->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "Tweeter phase fit:" << '\n';
    std::cout << "C = " << fitTweeter->GetParameter(0) << " +/- " << fitTweeter->GetParError(0) << " Farad" << '\n';
    std::cout << "R = " << fitTweeter->GetParameter(1) << " +/- " << fitTweeter->GetParError(1) << " Ohm" << '\n';
    std::cout << "reduced chi-square = " << fitTweeter->GetChisquare() / fitTweeter->GetNDF() << '\n';
}