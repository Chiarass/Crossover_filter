#include "TGraphErrors.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMarker.h"
#include "TMath.h"
#include "TLegend.h"
#include <Fit/FitResult.h>

void fitCrossover()
{
    TGraphErrors *dataWoofer = new TGraphErrors("datiLab2/SweepAmpiezzaLargoWoofer.txt", "%lg %lg %lg");
    TGraphErrors *dataTweeter = new TGraphErrors("datiLab2/SweepAmpiezzaLargoTweeter.txt", "%lg %lg %lg");

    // Fit woofer: [0] = V0, [1] = R, [2] = L
    TF1 *fitWoofer = new TF1("fW", "[0]*[1]/sqrt([1]^2 + (2*TMath::Pi()*x)^2 * [2]^2)");
    fitWoofer->SetParameters(1., 559.9, 10.2e-3);
    fitWoofer->SetParLimits(0, 0., 1.);
    fitWoofer->SetParLimits(1, 540., 600.);
    fitWoofer->SetParLimits(2, 9.7e-3, 11.e-3);
    dataWoofer->Fit("fW", "Q");

    // Fit tweeter: [0] = V0, [1] = R, [2] = C
    TF1 *fitTweeter = new TF1("fT", "[0]*[1]/sqrt([1]^2 + 1/((2*TMath::Pi()*x)^2 * [2]^2))");
    fitTweeter->SetParameters(1., 560., 26.10e-9);
    fitTweeter->SetParLimits(0, 0., 1.);
    fitTweeter->SetParLimits(1, 560., 600.);
    fitTweeter->SetParLimits(2, 23.e-9, 29e-9);
    dataTweeter->Fit("fT", "Q");

    // try to calculate intersection of the two curves
    // auto parT = fitTweeter->GetParameters();
    TF1 *diff = new TF1("diff", "fT - fW", 2000, 18000);
    diff->SetLineColor(kBlue);
    // does not work

    dataWoofer->Draw("A, P");
    dataWoofer->SetTitle("Crossover woofer-tweeter");
    dataWoofer->GetYaxis()->SetRangeUser(0., 0.5);
    dataWoofer->GetYaxis()->SetTitle("V_{out} [V]");
    dataWoofer->GetXaxis()->SetTitle("frequenza [Hz]");
    dataTweeter->Draw("same");
    dataWoofer->GetFunction("fW");

    /* auto legend = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend->SetHeader(" ", "C"); // option "C" allows to center the header
    legend->AddEntry(dataWoofer, "Woofer", "f");
    legend->AddEntry(dataTweeter, "Tweeter", "f");
    legend->Draw(); */
    // fix legend

    std::cout
        << "Woofer fit:" << '\n';
    std::cout << "V0 = " << fitWoofer->GetParameter(0) << " +/- " << fitWoofer->GetParError(0) << " Volt" << '\n';
    std::cout << "R = " << fitWoofer->GetParameter(1) << " +/- " << fitWoofer->GetParError(1) << " Ohm" << '\n';
    std::cout << "L = " << fitWoofer->GetParameter(2) << " +/- " << fitWoofer->GetParError(2) << " Henry" << '\n';
    std::cout << "reduced chi-square = " << fitWoofer->GetChisquare() / fitWoofer->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "Tweeter fit:" << '\n';
    std::cout << "V0 = " << fitTweeter->GetParameter(0) << " +/- " << fitTweeter->GetParError(0) << " Volt" << '\n';
    std::cout << "R = " << fitTweeter->GetParameter(1) << " +/- " << fitTweeter->GetParError(1) << " Ohm" << '\n';
    std::cout << "C = " << fitTweeter->GetParameter(2) << " +/- " << fitTweeter->GetParError(2) << " Farad" << '\n';
    std::cout << "reduced chi-square = " << fitTweeter->GetChisquare() / fitTweeter->GetNDF() << '\n';
    std::cout << "**********************************\n";
    // std::cout << diff->GetMinimum() << '\n';
}
